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
void show_preferences(void);
void show_pairs();
bool is_cycle(int source, int target);

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

    // Get the number of voters
    pair_count = 0;
    int voter_count = get_int("Number of voters: ");


    // For each voter get their "ballot" i.e: the ranked voting of the candidates
    // where each candidate is identified by an index (j)
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is the ith-voter's preferences
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

    show_preferences();

    add_pairs();

    show_pairs();

    sort_pairs();

    printf("AFTER SORT\n");

    show_pairs();

    lock_pairs();

    print_winner();

    return 0;
}

void show_pairs()
{
    for (int i = 0; i < pair_count; i++)
    {
        printf("Pair #%d => winner: %s (%d votes), loser: %s (%d votes)\n", i, candidates[pairs[i].winner],
               preferences[pairs[i].winner][pairs[i].loser], candidates[pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
    }
}

void show_preferences()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j)
            {
                continue;
            }
            printf("%s vs %s was preferred: %d times\n", candidates[i], candidates[j], preferences[i][j]);
        }
    }
}



// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Compare name provided by voter with name of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Update ranks array with voter ranks (i = candidate)
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // This represents the winnners over the rest
    for (int i = 0; i < candidate_count; i++)
    {
        // Don't need to check from 0 because it should have
        // already been handled by the previous outside loop (i)
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Make head-to-head matchup between candidates and choose winers and losers
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Don't compare same candidate with themselves
            if (i == j)
            {
                continue;
            }

            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = pair_count - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            if ((preferences[pairs[j].winner][pairs[j].loser]) < (preferences[pairs[j + 1].winner][pairs[j + 1].loser]))
            {
                pair temp = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = temp;
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
        pair p = pairs[i];
        if (!is_cycle(p.loser, p.winner))
        {
            printf("Lock pair => winner: %s, loser: %s\n", candidates[p.winner], candidates[p.loser]);
            locked[p.winner][p.loser] = true;
        }
        else
        {
            printf("Skipping pair due to cycle =>  winner: %s, loser: %s\n", candidates[p.winner], candidates[p.loser]);
        }
    }
    return;
}


bool is_cycle(int source, int target)
{
    // Base cases:
    // Case 1: When there is a cycle -> source == target
    if (source == target)
    {
        return true;
    }

    // For this source, recurse to all other pairs in which this source is over someone else,
    // and if it returns a cycle then return True
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[source][i] == true)
        {
            if (is_cycle(i, target))
            {
                return true;
            }
        }
    }
    // No other pairs from this source or perhaps there were but there were no cycles, then return False
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // The winner is the node that is the source of the graph (no edges pointing to it)
    // The node with no edges pointing to it is represented by the id of the column with only false in the locked array

    int winner = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        int i;
        for (i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == true)
            {
                break;
            }
        }
        if (i == candidate_count)
        {
            winner = j;
            break;
        }
    }
    printf("%s\n", candidates[winner]);
}