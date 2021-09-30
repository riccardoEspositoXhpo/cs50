#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int compute_score(string text);
void count_elements(string text, int *letters, int *words, int *sentences);

int main(void)
{

    // prompt user for text
    string s = get_string("Text: ");

    // compute score
    int score = compute_score(s);

    if (score < 1)
    {

        printf("Before Grade 1\n");

    }
    else if (score >= 1 && score < 17)
    {

        printf("Grade %i\n", score);

    }
    else
    {

        printf("Grade 16+\n");

    }

}

int compute_score(string text)
{

    float score = 0;

    int letters, words, sentences;

    /*  returning multiple elements from a function learned from the below:
        https://www.geeksforgeeks.org/how-to-return-multiple-values-from-a-function-in-c-or-cpp/
    */
    count_elements(text, &letters, &words, &sentences);

    // letter per 100 words
    float adjusted_letters = letters * (100 / (float) words);

    // sentences per 100 words
    float adjusted_sentences = sentences * (100 / (float) words);

    // run the Coleman-Liau index
    score = (0.0588 * adjusted_letters) - (0.296 * adjusted_sentences) - 15.8;

    // round and cast to integer
    score = round(score);
    score = (int) score;

    return score;

}

void count_elements(string text, int *letters, int *words, int *sentences)
{

    /* for efficiency I decided to loop the string only once
       instead of looping each time to find letters, words and sentences.
       I chose to use pointers to return multiple values from the function.
    */

    letters[0] = 0;
    words[0] = 0;
    sentences[0] = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            // identify a letter by using ascii
            letters[0]++;

        }
        else if (text[i] == ' ')
        {
            // each space identifies a word
            words[0]++;

        }
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            // certain punctuations define the end of a sentence
            sentences[0]++;

        }

    }
    /* the last word of a sentence doesn't have a space to identify
       so we increment by 1
    */
    words[0]++;

}


