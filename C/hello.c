#include <stdio.h>
#include <cs50.h>

int main(void){

    string answer = get_string("Come ti chiami?\n");
    printf("hello %s\n", answer);

}