#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string s = get_string("Before: ");
    printf("After:  ");

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // if (s[i] >= 'a' && s[i] <= 'z')
        // {
        //     // this is a litle trick
        //     // in ascii (which is how it is stored) capital letters and lower are separated by 32
        //     printf("%c", s[i] - 32);
        // }
        // else
        // {
        //     printf("%c", s[i]);
        // }


        // type has islower function, upper function
        printf("%c", toupper(s[i]));
    }
    printf("\n");


}s