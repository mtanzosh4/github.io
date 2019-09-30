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
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
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
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
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
            if (i != j)
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                    pair_count++;
                }
                else if (preferences[j][i] > preferences[i][j])
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                    pair_count++;
                }
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    typedef struct
    {
        int winner;
        int loser;
        int strength;
    }
    win;

    // calculate strength
    win wins[pair_count];

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            wins[i].strength = preferences[i][j] - preferences[j][i];
            wins[i].winner = i;
            wins[i].loser = j;
        }
    }


    // sort wins array largest to smallest
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - 1; j++)
        {
            if (wins[j].strength < wins[j + 1].strength)
            {
                win temp = wins[j];
                wins[j] = wins[j + 1];
                wins[j + 1] = temp;
            }
        }
    }

    int position = 0;
    // sort pairs array
    for (int i = 0; i < pair_count; i++)
    {

        for (int j = 0; j < pair_count; j++)
        {
            // search for each candidate and swap to proper position
            if (wins[i].winner == pairs[j].winner)
            {
                // swap
                pair temp = pairs[j];
                pairs[j] = pairs[position];
                pairs[position] = temp;
                position++;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // check for cycle
        // if all other candidates appear as a loser,
        bool loosers[MAX] = { false };
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = 0; k < candidate_count; k++)
            {
                if (i != j)
                {
                    if (locked[k][j])
                    {
                        loosers[j] = true;
                    }
                }
            }
        }

        for (int j = 0; j < candidate_count; j++)
        {
            if (i != j)
            {
                if (!loosers[j])
                {
                     // no cycle so lock pair
                    locked[pairs[i].winner][pairs[i].loser] = true;
                    // return;
                }
            }
        }

    }


    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("%s", locked[i][j] ? "true" : "false");
    //     }
    //     printf("\n");
    // }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool win = false;
        for (int j = 0; j < candidate_count; j++)
        {
            win = win || locked[j][i];
        }
        if (!win)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

