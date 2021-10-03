#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    // adding the pair strength - please note the automated check does not allow for this method
    //int strength;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;
int locked_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool find_cycle(int end, int start);
void lock_pairs(void);
void print_winner(void);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{

    bool is_candidate_found = false;

    // find if name is valid
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // mark candidate as found and store in ranks
            is_candidate_found = true;
            ranks[rank] = i;

        }
    }

    return is_candidate_found;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            /* ranks array represents order of preference,
               so we can stipulate that there is a preference between
               any lower and higher index of the array.
            */
            preferences[ranks[i]][ranks[j]] += 1;


        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {

            /*  for each preference pair, we evaluate if one has more votes
                than the other and if so, record a new pair.
                In the case where the struct includes strength, we can store that as well
            */
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                //pairs[pair_count].strength = preferences[i][j]; //- preferences[j][i];
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                //pairs[pair_count].strength = preferences[j][i]; //- preferences[i][j];
                pair_count++;
            }
        }
    }
    // do nothing if strength is equal
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // performing selection sort as max number of pairs is [MAX * (MAX - 1) / 2]
    int max;
    pair swap[1];

    for (int i = 0; i < pair_count; i++)
    {
        max = i;
        for (int j = i + 1; j < pair_count; j++)
        {

            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[max].winner][pairs[max].loser])
            {
                max = j;

            }
            /* by using strength in the struct, we could code like below
              if (pairs[i] .strength> pairs[max].strength)
              {
                 max = j;

              }
            */
        }
        // store in a temporary pair and perform swap
        swap[0] = pairs[i];
        pairs[i] = pairs[max];
        pairs[max] = swap[0];

    }

    return;
}


// we call this function recursively in orderto traverse the tree
bool find_cycle(int end, int start)
{
    // base case - when start is equal to end we exit
    if (end == start)
    {
        return true;
    }
    else // recursive case
    {
        for (int i = 0; i < candidate_count; i++)
        {
            // traverse the tree in the opposite direction
            if (locked[end][i])
            {
                if (find_cycle(i, start))
                {
                    return true;

                }
            }
        }
    }
    // if no locked pairs are found, we conclude there is no cycle
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    /*  only add an arrow if it does not create a cycle.
        one way to find a cycle is to attempt to navigate the tree,
        recursively, in the opposite direction.
    */

    for (int i = 0; i < pair_count; i++)
    {
        if (!find_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    /*  the winner is the player in the graph of locked pairs with degree 0.
        We need to find the player that has no arrows going into them,
        meaning if there is an index i, there is no index with locked[j][i]
    */
    bool winner = true;

    for (int i = 0; i < candidate_count; i++)
    {
        int count_wins = 0;
        // check each i for winner status. A winner has no subarray where they are the loser set to true
        for (int j = 0; j < candidate_count; j++)
        {
            // we check every combination of player where i is the "loser"
            if (!locked[j][i])
            {
                // i can be the winner only if there exist exactly 0 instances in which they lose in a locked pair
                // this means every locked pair must be false
                count_wins++;
            }
        }
        // i wins when each locked pair where i is the loser is false
        if (count_wins == candidate_count)
        {
            printf("%s\n", candidates[i]);
            // once the winner is found we can stop the program
            break;
        }

    }

    return;
}

