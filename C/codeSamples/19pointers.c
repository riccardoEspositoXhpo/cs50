#include <stdio.h>
//#include <cs50.h>

int main(void)
{
    // int n = 50;

    // p is the code for "address" in memory
    // p stands for pointer
    // a POINTER contains the address of a variable
    // &n means tell me the LOCATION of N in memory
    // *n says "go to that address"
    // you can undo the effects of & with *

    // int *p = &n;

    // printf("%i\n", *p);

    // a string s is technically a pointer to the first character and you can expose this
    //string s = "HI!";
    // printf("%p\n", s);
    // printf("%p\n", &s[1]);

    // the problem with C, is that string is not a datatype in C
    // technically it's defined as char *s = "HI!"
    // why? because it's the value of the pointer

    //typedef char* string;
    char *s = "HI!";
    // printf("%c\n", s[0]);
    // printf("%c\n", s[1]);
    // printf("%c\n", s[2]);

    // with pointer addresses, you can do pointer arithmetic
    printf("%c\n", *s);
    printf("%c\n", *(s + 1));
    printf("%c\n", *(s + 2));



}

