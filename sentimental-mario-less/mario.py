import cs50


# i indicates to row
def main():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                for i in range(1, height + 1, 1):
                    for d in range(0, height - i, 1):
                        print(" ", end="")
                    # The number of hashes on each row is one more than the row number (since we're starting from 0).
                    for j in range(i):
                        # This code equall to this line of code `for j in range(0, i, 1):`
                        print("#", end="")
                    print()
                break

        except ValueError:
            continue


main()
