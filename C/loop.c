#include <cs50.h>
#include <stdio.h>

int main(void){

    //infinite loop
    while (true)
    {
        printf("Hello, World.\n");
    }

    //finite loop, 50 iterations
    int i = 0;
    while (i < 50)
    {
        printf("Hello, World.\n");
        i++;
    }


    //finite loop, for
    for (int j = 0; j < 50; j++)
    {
        printf("Hello, World.\n"); 
    }

}