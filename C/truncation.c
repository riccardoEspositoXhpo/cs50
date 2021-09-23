#include <cs50.h>
#include <stdio.h>

int main(void){

    // get numbers from user
    int x = get_int("x: ");
    int y = get_int("y: ");

    // convert int to float
    // if you don't "type cast", the answer of math on two integers will be an integer
    float z = (float)x / (float)y;

    printf("%f\n", z);
}