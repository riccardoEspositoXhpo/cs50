
def main():

    # prompt user for card number
    cardNumber = getCardNumber()

    # count and store number of digits
    digits = len(cardNumber)

    # check if number is valid
    if isCardValid(cardNumber) == False:

        print("INVALID")

    else:

        # obtain card provider once proven that number is valid
        cardProvider = getCardProvider(cardNumber, digits)

        print(cardProvider)


def getCardNumber():

    while True:

        try:

            cardNumber = input("Number: ")

            if ((isinstance(int(cardNumber), int)) == True):

                break

        # capture letters in the card number
        except ValueError:

            print("INVALID")

    return cardNumber


def isCardValid(cardNumber):

    sums = product = 0
    length = len(cardNumber)

    # reverse card number so we can iterate over even and odd digits
    reversedCardNumber = cardNumber[::-1]

    # perform Luhn's algorithm
    for element in range(length):

        number = int(reversedCardNumber[element])

        if (element % 2) == 1:

            if (number * 2 < 10):

                product += (number * 2)

            else:
                # maximum product is 18 so we can afford to simply add a 1
                product += (number * 2) % 10 + 1

        elif (element % 2) == 0:

            sums += number

    checksum = sums + product

    if (checksum % 10) == 0:

        return True

    else:

        return False


def getCardProvider(cardNumber, digits):

    # capture the first two digits as integer
    firstDigits = cardNumber[0] + cardNumber[1]

    firstDigits = int(firstDigits)

    # find 15 digit cards tarting with 34 or 37
    if (firstDigits == 34 or firstDigits == 37) and digits == 15:

        return "AMEX"

    # find 13 or 16 digit cards starting with 4
    if (firstDigits >= 40 and firstDigits < 50) and (digits == 13 or digits == 16):

        return "VISA"

    # find 16 digit cards starting with 51 through 55
    if (firstDigits >= 51 and firstDigits <= 55) and digits == 16:

        return "MASTERCARD"

    else:

        return "INVALID"


if __name__ == '__main__':
    main()