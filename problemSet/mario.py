

def main():

    # get input from user
    pyramidHeight = getPyramidHeight()

    # construct pyramid
    for i in range(pyramidHeight):

        # indents the pyramid according to height
        printSpaces(pyramidHeight, i)

        # prints hashes and separator
        printHashes(i)
        print("  ", end="")
        printHashes(i)

        # newline
        print("")


def getPyramidHeight():
    print("please provide a pyramid height between 1 and 8, inclusive. ")

    while True:
        try:
            pyramidHeight = input("Pyramid Height: ")
            pyramidHeight = int(pyramidHeight)
            if pyramidHeight >= 1 and pyramidHeight <= 8:
                break
        except ValueError:
            print("This is not an integer.")

    return pyramidHeight


def printSpaces(height, i):

    print(" " * (height - i - 1), end="")


def printHashes(i):

    print("#" * (i + 1), end="")


if __name__ == '__main__':
    main()