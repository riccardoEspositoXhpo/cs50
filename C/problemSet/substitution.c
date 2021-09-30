#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int error_handling(int argc, string argv[]);
string key_analysis(string argv[]);
string run_cipher(string argv[], string plain);


int main(int argc, string argv[])
{
    string plain;

    // capitalize the key if it exists
    if (argv[1])
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            argv[1][i] = toupper(argv[1][i]);
        }
    }

    // assess if key is valid
    int error_code = error_handling(argc, argv);

    if (error_code == 0)
    {
        // convert plain to cipher
        plain = get_string("plaintext:  ");
        printf("ciphertext: %s\n", run_cipher(argv, plain));
    }

    return error_code;
}

int error_handling(int argc, string argv[])
{
    int error_code = 1;

    // capture more or less than 1 key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
    }
    // capture 1 key but incorrect number of characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
    }
    else if (strcmp(key_analysis(argv), "invalid") == 0)
    {
        printf("Key must contain letters from the English alphabet.\n");
    }
    else if (strcmp(key_analysis(argv), "duplicate") == 0)
    {
        printf("Key must not contain duplicates.\n");
    }
    else
    {
        error_code = 0;
    }

    return error_code;
}



string run_cipher(string argv[], string s)
{
    // loop the string and perform substitution
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // case 1 - letter is lowercase. Take advantage of toupper returning the same value for any capital letter, space or symbol
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            // find position in key and return to lowercase
            s[i] = tolower(argv[1][(int)(s[i] - 97)]);

        }
        else // case 2 - it is a capital letter or symbol
        {
            // if it is a letter, lookup position in array, return converted letter
            if (s[i] >= 'A' && s[i] <= 'Z')
            {
                s[i] = argv[1][(int)(s[i] - 65)];

            }

            // if it is not a letter, we do not change s[i]
        }

    }

    return s;
}


string key_analysis(string argv[])
{
    // a key can have both invalid and duplicate characters, the program flags the first one it finds
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if ((argv[1][i] < 'A' || argv[1][i] > 'Z'))
        {
            return "invalid";
            break;
        }
        // the idea of looping the string twice to compare characters was discovered here
        // https://xiith.com/c-program-to-find-duplicate-characters-in-a-string/
        for (int j = i + 1; j < n; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                return "duplicate";
                break;
            }
        }
    }

    return "";

}

