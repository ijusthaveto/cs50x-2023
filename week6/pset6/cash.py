from cs50 import get_float


def main():
    cents = get_cents()

    quarters = calc_quarters(cents)
    cents = cents - quarters * 25

    dimes = calc_dimes(cents)
    cents = cents - dimes * 10

    nickels = calc_nickels(cents)
    cents = cents - nickels * 5

    pennies = calc_pennies(cents)
    cents = cents - pennies * 1

    coins = quarters + dimes + nickels + pennies

    print(f"{coins}")


def get_cents():
    cents = 0.0
    while True:
        cents = get_float("Change owed: ")
        if cents > 0.0:
            break
    return int(cents * 100)


def calc_quarters(cents):
    return int(cents / 25)


def calc_dimes(cents):
    return int(cents / 10)


def calc_nickels(cents):
    return int(cents / 5)


def calc_pennies(cents):
    return int(cents / 1)


if __name__ == "__main__":
    main()
