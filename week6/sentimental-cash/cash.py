import cs50


def get_cents():
    while True:
        try:
            cents = cs50.get_float("Change owed: ")
            if cents >= 0:
                return cents*100
        except ValueError:
            pass


def calculate_coins(cents, coin_value):
    num_coins = cents // coin_value
    remaining_cents = cents % coin_value
    return num_coins, remaining_cents


def main():
    cents = get_cents()

    quarters, cents = calculate_coins(cents, 25)

    dimes, cents = calculate_coins(cents, 10)

    nickels, cents = calculate_coins(cents, 5)

    pennies = cents  # Remaining cents are all pennies

    coins = quarters + dimes + nickels + pennies

    print(f"{int(coins)}")


main()
