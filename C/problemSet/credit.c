#include <stdio.h>
#include <cs50.h>
#include <math.h>


long get_card_number(void);
int count_digits(long card_number);
bool is_digit_valid(int digits);
bool is_card_valid(long card_number, int digits);
string get_card_provider(long card_number, int digits);



int main(void)
{
    // prompt user for card number
    long card_number = get_card_number();

    // count and store the number of digits
    int digits = count_digits(card_number);

    // check if card has invalid number of digits
    if (!is_digit_valid(digits))
    {

        printf("INVALID\n");

    }
    else // only run the rest of the program if digit count is valid
    {
        // run Luhn's algorithm to check if the number is a valid credit card
        if (!is_card_valid(card_number, digits))
        {

            printf("INVALID\n");

        }
        else // only check card provider if credit card is valid
        {
            // find card provider
            string card_provider = get_card_provider(card_number, digits);

            // print result
            printf("%s\n", card_provider);

        }
    }

}


long get_card_number(void)
{
    long card_number = get_long("Number: ");

    return card_number;
}


int count_digits(long card_number)
{

    int digits = 0;
    long check_digits = card_number;

    while (check_digits != 0)
    {
        // dividing by 10 removes a digit from the number
        check_digits /= 10;
        digits++;

    }

    return digits;
}


bool is_digit_valid(int digits)
{

    if (digits == 13 || digits == 15 || digits == 16)
    {

        return true;

    }
    else
    {

        return false;

    }

}


bool is_card_valid(long card_number, int digits)
{

    int last_digit = 0;
    int sum = 0;
    int product = 0;
    int checksum = 0;
    long check_value = card_number;


    for (int i = 0; i < digits; i++)
    {
        // store and then remove the last digit
        last_digit = check_value % 10;
        check_value /= 10;

        // multiply all the odd digits by 2 and sum all their digits
        if (i % 2 == 1)
        {
            last_digit *= 2;

            if (last_digit < 10)
            {

                product += last_digit;

            }
            else
            {

                // the highest product is 18 with digit 9, it is sufficient to add 1
                product += (last_digit % 10) + 1;

            }

        }

        // sum of the even digits
        else if (i % 2 == 0)
        {

            sum += last_digit;

        }

    }

    //add the product to the sum and check if congruent to 0
    checksum = sum + product;

    if (checksum % 10 == 0)
    {

        return true;
    }
    else
    {

        return false;

    }

}


string get_card_provider(long card_number, int digits)
{

    // capture the first two digits as integer
    int first_two_digits = card_number / (pow(10, digits - 2));

    // find 15 digit cards tarting with 34 or 37
    if ((first_two_digits == 34 || first_two_digits == 37) && digits == 15)
    {

        return "AMEX";

    }
    // find 13 or 16 digit cards starting with 4
    else if ((first_two_digits >= 40 && first_two_digits < 50) && (digits == 13 || digits == 16))
    {

        return "VISA";

    }
    // find 16 digit cards starting with 51 through 55
    else if ((first_two_digits >= 51 && first_two_digits <= 55) && digits == 16)
    {

        return "MASTERCARD";

    }
    else
    {
        // captures a valid card from any other provider
        return "INVALID";   // can be set to "OTHER" to distinguish from invalid numbers

    }

}