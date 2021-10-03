#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    FILE *file = fopen("phonebook.csv","a");
    // opened in append mode, also supports read or write

    if (file == NULL)
    {
        return 1;
    }

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    fprintf(file, "%s,%s\n", name, number);

    fclose(file);

}
