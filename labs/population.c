#include <stdio.h>
#include <cs50.h>

int get_start_size(void);
int get_end_size(int start_size);


int main(void)
{
    // ask user for population inputs
    int start_size = get_start_size();
    int end_size = get_end_size(start_size);

    // initializing variables for population counting
    int current_size = start_size;
    int births;
    int deaths;
    int year_counter = 0;

    // run until the population reaches the final size
    while (current_size < end_size)
    {
        births = current_size / 3;
        deaths = current_size / 4;

        // increase the current population and mark the passing of a year
        current_size += (births - deaths);
        year_counter++;

    }

    printf("Years: %i\n", year_counter);
}

int get_start_size(void)
{
    int start_size;

    printf("Please provide a positive integer greater than 9.\n");

    do
    {
        start_size = get_int("Population Start Size: ");
    }

    // force the input to be greater than 9
    while (start_size < 9);

    return start_size;

}


int get_end_size(int start_size)
{
    int end_size;

    printf("Please provide a positive integer greater than or equal to Start Size.\n");

    do
    {
        end_size = get_int("Population End Size: ");
    }

    // force the input to be greater than or equal to Start Size
    while (end_size < start_size);

    return end_size;

}