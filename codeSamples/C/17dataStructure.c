#include <cs50.h>
#include <stdio.h>
#include <string.h>


typedef struct
{
    string name;
    string number;
}
person;

const int NUMBER = 10;

int main (void)
{

    person people[NUMBER];

    for (int = 0; i < NUMBER; i++)
    { 
        people[i].name = get_string("What's your name?");
        people[i].number = get_string("What's your number?");
    }
    // people[0].name = "Brian";
    // people[0].number = "335-8212218";

    // people[1].name = "Beily";
    // people[1].number = "339-7321961";

    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, "Beily") == 0)
        {
            printf("Found: %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not Found\n");
    return 1;
}