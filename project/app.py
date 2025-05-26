import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, usd
from datetime import date, datetime, timedelta
# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///project.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    if request.method == "POST":
        user_id = session["user_id"]

        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if not name or not month or not day:
            return redirect("/")

        db.execute("INSERT INTO birthdays(user_id, name, month, day) VALUES (?, ?, ?, ?)",
                   user_id, name, month, day)

        return redirect("/")

    else:
        user_id = session["user_id"]
        birthdays = db.execute("SELECT name, month, day FROM birthdays WHERE user_id = ?", user_id)

        # Add days_until_birthday to each birthday entry
        today = datetime.now().date()
        for b in birthdays:
            birthday_date = datetime(today.year, b['month'], b['day']).date()
            if birthday_date < today:
                birthday_date = datetime(today.year + 1, b['month'], b['day']).date()
            b['days_until'] = (birthday_date - today).days
            b['is_today'] = (birthday_date == today)

        # Sort birthdays by days_until
        birthdays.sort(key=lambda b: b['days_until'])

        # Find the nearest birthday
        if birthdays:
            nearest_birthday = min(birthdays, key=lambda b: b['days_until'])
            this_year = datetime.now().year
            nearest_birthday_date = datetime(
                this_year, nearest_birthday['month'], nearest_birthday['day'])
            if nearest_birthday_date < datetime.now():
                nearest_birthday_date = datetime(
                    this_year + 1, nearest_birthday['month'], nearest_birthday['day'])
            nearest_birthday_date_iso = nearest_birthday_date.isoformat()
        else:
            nearest_birthday = None
            nearest_birthday_date_iso = None

        return render_template("index.html", birthdays=birthdays, nearest_birthday=nearest_birthday, nearest_birthday_date_iso=nearest_birthday_date_iso)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")

    else:
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("Must give username")
        if not password:
            return apology("Must give password")
        if not confirmation:
            return apology("Must give confirmation")
        if password != confirmation:
            return apology("Passwords don't match")

        hash = generate_password_hash(password)

        try:
            # Attempt to insert new user into the database
            new_user_id = db.execute(
                "INSERT INTO users(username, hash) VALUES (?, ?)", username, hash)
        except Exception as e:
            print(f"Database error: {e}")
            return apology("Username already exists")

        # Store the new user_id in the session
        session["user_id"] = new_user_id
        return redirect("/")
