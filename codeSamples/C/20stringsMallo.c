#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    // char *t = get_string("t: ");

    // if (*s == *t)
    // {
    //     printf("Same\n");
    // }
    // else
    // {
    //     printf("Different\n");
    // }

    // since string are pointers, if I define char*t = s
    // i am literally getting both t and s pointing to the same location
    // I didn't copy anything.
    // to copy something, you do as below

    char *t = malloc(strlen(s) + 1);

    // you check for null in case the memory allocation goes wrong
    if (t == NULL)
    {
        return 1;
    }

    // you loop until <= to copy the null character,
    // or you define n as strlen(s) + 1, it's the same
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    // btw you can also just do strcpy(t,s);

    // careful, if the length is 0 you maybe don't want to capitalize
    if (strlen(t) >= 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);


    // once you are done with memory, YOU BETTER FREE IT
    // if not your pc will run out
    free(t);

}