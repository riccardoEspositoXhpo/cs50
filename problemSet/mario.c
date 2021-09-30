#include <stdio.h>
#include <cs50.h>

int get_pyramid_height(void);
void print_spaces(int pyramid_height, int i);
void print_hashes(int i);

int main(void)
{

    int pyramid_height = get_pyramid_height();

    for (int i = 0; i < pyramid_height; i++)
    {
        // dynamically print the correct number of spaces and hashes depending on the pyramid level
        print_spaces(pyramid_height, i);
        print_hashes(i);

        // add the separator in the center
        printf("%s", "  ");

        // complete the right side of the pyramid. No spaces are required
        print_hashes(i);

        printf("\n");

    }


}

int get_pyramid_height(void)
{
    int pyramid_height;
    printf("Please provide a pyramid height between 1 and 8, inclusive.\n");

    do
    {
        pyramid_height = get_int("Pyramid Height: ");
    }
    while (pyramid_height < 1 || pyramid_height > 8);

    return pyramid_height;
}

void print_spaces(int pyramid_height, int i)
{
    // the loop counts downwards as the number of spaces decreases as we move down the pyramid
    for (int j = pyramid_height - ( i + 1 ); j > 0; j--)
    {

        printf("%c", ' ');

    }
}

void print_hashes(int i)
{
    // each pyramid line has i + 1 hashes to populate
    for (int j = 0; j < i + 1; j++)
    {

        printf("%c", '#');

    }

}
