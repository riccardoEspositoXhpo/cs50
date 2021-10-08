#include <stdio.h>


void swap(int *a, int *b);

int main(void)
{
    int x = 1;
    int y = 2;

    printf("x is %i, y is %i\n", x, y);

    swap(&x, &y);

    printf("x is %i, y is %i\n", x, y);
}

// so why doesn't this work
// x and y are not actually moved here
// they are just copied
// the solution is to use pointers!
// so you can go to the right location in memory and actually swap the values!

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}
