#include <stdio.h>
#include <cs50 .h>

int get_positive_int(void);

int main(void) {

    int i = get_positinve_int();
    printf("%i\n", i);

}

// Prompt user for positive integer
int get_positive_int(void) {
    int n;
    // the do loop executes a command before checking a condition
    // in this case we keep asking for an int while it's lower than 1

    do {
        n = get_int("Positive Integer: ");
    } while (n < 1);
    return n;
}