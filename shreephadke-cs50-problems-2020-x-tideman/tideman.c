#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

bool edge[MAX][MAX];

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
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;

            //printf("rank is: %d\n", rank);
            //printf("Ranks[0] is: %d\n", ranks[0]);
            //printf("Ranks[1] is: %d\n", ranks[1]);
            //printf("Ranks[2] is: %d\n", ranks[2]);
            //printf("Ranks[3] is: %d\n", ranks[3]);
            //printf("Ranks[4] is: %d\n", ranks[4]);

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
        if (i == candidate_count - 1)
        {
            break;
        }
        else
        {
            //int numPairs = candidate_count - (i + 1);
            for (int j = i + 1; j < candidate_count; j++)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
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
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[i].winner = i;
                pairs[j].loser = j;
                pair_count++;

            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[j].winner = j;
                pairs[i].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int i = 0; i < pair_count - 1; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j+1].winner][pairs[j+1].loser] > preferences[pairs[j].winner][pairs[j].loser])
            {
                pair p;
                p.winner = pairs[j].winner;
                p.loser = pairs[j].loser;
                pairs[j].winner = pairs[j + 1].winner;
                pairs[j].loser = pairs[j + 1].loser;
                pairs[j + 1].winner = p.winner;
                pairs[j + 1].loser = p.loser;

            }
        }
    }

    return;
}

void updateEdge(int lockwin, int lockloss)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (edge[i][lockwin])
            {
                edge[i][lockloss] = true;
            }
            if (edge[lockloss][j])
            {
                edge[lockwin][j] = true;
            }
            if ((edge[i][lockwin]) && (edge[lockloss][j]))
            {
                edge[i][j] = true;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int lockwin, lockloss;
    for (int i = 0; i < pair_count; i++)
    {
        lockwin = pairs[i].winner;
        lockloss = pairs[i].loser;

        if (edge[lockloss][lockwin] == false)
        {
            locked[lockwin][lockloss] = true;
            edge[lockwin][lockloss] = true;
            updateEdge(lockwin, lockloss);
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool T = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                T = false;
            }
        }

        if (T == true)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

