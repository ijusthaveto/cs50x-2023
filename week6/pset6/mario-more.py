from cs50 import get_int


def main():
    height = 0

    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break

    for row in range(height):
        print(" " * (height - row - 1), end="")
        print("#" * (row + 1), end="  ")
        print("#" * (row + 1))


if __name__ == "__main__":
    main()