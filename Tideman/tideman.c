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
    
    for(int i = 0; i < candidate_count; i++)
    {
        if(strcmp(name, candidates[i]) == 0)
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
    
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    
    for (int i = 0;i < candidate_count - 1; i++)
    {
        if (preferences[i][i+1] > preferences[i+1][i])
        {
            pairs[i].winner = i;
            pairs[i].loser = i + 1;


        }
        else if (preferences[i][i+1] < preferences[i+1][i])
        {
            pairs[i].winner = i + 1;
            pairs[i].loser = i;
        }
    }
    if (preferences[candidate_count - 1][0] > preferences[0][candidate_count - 1])
    {
        pairs[candidate_count - 1].winner = candidate_count - 1;
        pairs[candidate_count - 1].loser = 0;
    }
    else if (preferences[candidate_count - 1][0] < preferences[0][candidate_count - 1])
    {
        pairs[candidate_count - 1].winner = 0;
        pairs[candidate_count - 1].loser = candidate_count - 1;
    }




    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    
    int size = candidate_count * (candidate_count - 1) / 2;
    pair guardar;
    for(int i = 0; i < size - 1; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            guardar.winner = pairs[i + 1].winner;
            guardar.loser = pairs[i + 1].loser;

            pairs[i + 1].winner = pairs[i].winner;
            pairs[i + 1].loser = pairs[i].loser;

            pairs[i].winner = guardar.winner;
            pairs[i].loser = guardar.loser;

        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    
    int size = candidate_count * (candidate_count - 1) / 2;
    for (int i = 0; i < size; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    
    int size = candidate_count * (candidate_count - 1) / 2;
    int loses = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if(locked[j][i] == true)
            {
                loses += 1;
            }
        }

        if (loses == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
        else
        {
            loses = 0;
        }
    }
    return;
}