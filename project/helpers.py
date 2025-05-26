import requests
from datetime import date, datetime, timedelta
from flask import redirect, render_template, session
from functools import wraps
import smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from apscheduler.schedulers.background import BackgroundScheduler
from pytz import timezone
import os


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        for old, new in [
            ("-", "--"),
            (" ", "-"),
            ("_", "__"),
            ("?", "~q"),
            ("%", "~p"),
            ("#", "~h"),
            ("/", "~s"),
            ('"', "''"),
        ]:
            s = s.replace(old, new)
        return s

    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """Decorator to require login."""
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def usd(value):
    """Format value as USD."""
    return f"${value:,.2f}"


def days_until_birthday(birthday_day, birthday_month):
    today = date.today()
    this_year = today.year
    birthday_date = date(this_year, birthday_month, birthday_day)
    if birthday_date < today:
        birthday_date = date(this_year + 1, birthday_month, birthday_day)
    delta = birthday_date - today
    return delta.days
