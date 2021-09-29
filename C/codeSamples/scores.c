#include <stdio.h>
#include <cs50.h>

const int  TOTAL = 3;

int main(void)
{
    // when you declare an array, you use the total number of values
    //int total = get_int("Total number of scores: ");
    int scores[TOTAL];

    // however indexing starts at 0
    for (int i = 0; i < TOTAL; i++)
    {

        scores[i] = get_int("Score: ");

    }

    printf("Average: %f\n", average(TOTAL, scores));

}

float average(int length, int array[])
{
    int sum = 0;

    for (int i = 0; i < length; i++)
    {

        sum += array[i];

    }

    return sum / (float) length;

}

