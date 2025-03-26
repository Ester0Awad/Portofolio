from cs50 import get_float


def main():
    total_coins = 0
    while True:
        try:
            change = get_float("Change owed:")
            if (change) > 0:
                cents = int(change * 100)

                quarters = cents // 25
                cents = cents % 25
                total_coins += quarters

                dimes = cents // 10
                cents = cents % 10
                total_coins += dimes

                nickels = cents // 5
                cents = cents % 5
                total_coins += nickels

                pennies = cents // 1
                total_coins += pennies

                coins = total_coins

                print(coins)

                break
        except ValueError:
            continue


main()
