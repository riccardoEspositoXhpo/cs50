#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{

    string s =   get_string("Input:  ");
    printf("Output: ");

    // the string is stored in memory with an additional character /0 to signal its end
    // we can leverage this to find the length of a string!

    for (int i = 0; s[i] !='\0'; i++)
    {
        printf("%c", s[i]);
    }


    // we can use the function strlen to find the length of string
    // we initialize it at the start of the loop in order to save time
    // you don't want to keep asking the length of s every single time you run the loop
    for (int j = 0, n = strlen(s); j < n; j++)
    {
        printf("%c", s[j]);
    }
    printf("\n")

}