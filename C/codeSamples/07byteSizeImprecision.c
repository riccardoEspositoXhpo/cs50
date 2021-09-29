#include <stdio.h>
#include <cs50.h>

int main(void){

    // try to divide 1 by 10
    float x = get_float("x: ");
    float y = get_float("y: ");

    printf("%.50f\n", x / y);
}