#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

    bool is_candidate_found = false;

    // find if name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {

            candidates[i].votes++;
            is_candidate_found = true;
        }
    }
    return is_candidate_found;
}

// Print the winner (or winners) of the election
void print_winner(void)
{


    int max;
    candidate swap[1];

    /* find the index of candidate with most votes
       sort the array from highest to lowest using selection sort
       keep printing as long as number is identical
    */
    for (int i = 0; i < candidate_count; i++)
    {
        max = i;
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (candidates[j].votes > candidates[max].votes)
            {
                max = j;
            }

        }
        swap[0] = candidates[i];
        candidates[i] = candidates[max];
        candidates[max] = swap[0];
    }

    // print the winner
    printf("%s\n", candidates[0].name);

    // if the next best candidate has the same votes, print them as well
    for (int k = 0; k < candidate_count - 1; k++)
    {
        if (candidates[k].votes == candidates[k + 1].votes)
        {
            printf("%s\n", candidates[k + 1].name);
        }
    }

    return;
}

