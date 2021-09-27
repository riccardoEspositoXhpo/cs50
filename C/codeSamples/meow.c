#include <cs50.h>
#include <stdio.h>

// this is a prototype
// when you compile, it goes from top to bottom, this trick tells the compiler that there will exist a meow function.
void meow(int);

int main(void) {
    meow(3);
}


void meow(int n) {

    for (int i = 0; i < n; i++) {
        
        printf("meow\n");
    
    }
}