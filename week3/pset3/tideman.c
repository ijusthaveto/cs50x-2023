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
} pair;

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
bool is_cycle(int winner, int loser, bool visited[]);
void quick_sort_pairs(int left, int right);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            pair new_pair;
            if (preferences[i][j] > preferences[j][i])
            {
                new_pair.winner = i;
                new_pair.loser = j;
                pairs[pair_count++] = new_pair;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                new_pair.winner = j;
                new_pair.loser = i;
                pairs[pair_count++] = new_pair;
            }
        }
    }
    return;
}

void quick_sort_pairs(int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int i = left - 1, j = right + 1, middle = (left + right) >> 1;
    int pivot = preferences[pairs[middle].winner][pairs[middle].loser];

    while (i < j)
    {
        do i++; while (preferences[pairs[i].winner][pairs[i].loser] > pivot);
        do j--; while (preferences[pairs[j].winner][pairs[j].loser] < pivot);
        if (i < j)
        {
            pair tmp = pairs[i];
            pairs[i] = pairs[j];
            pairs[j] = tmp;
        }
    }
    quick_sort_pairs(left, j);
    quick_sort_pairs(j + 1, right);

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    quick_sort_pairs(0, pair_count - 1);
}

// Determinate whether creating an edge creates a cycle
bool is_cycle(int winner, int loser, bool visited[])
{
    if (visited[loser])
    {
        return false;
    }

    visited[loser] = true;

    if (winner == loser)
    {
        visited[loser] = false;
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && is_cycle(winner, i, visited))
        {
            return true;
        }
    }

    visited[loser] = false;
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    bool is_processed[MAX][MAX] = {false};

    for (int i = 0; i < pair_count; i++)
    {
        if (!is_cycle(pairs[i].winner, pairs[i].loser, is_processed[pairs[i].winner]))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            is_processed[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    bool is_locked[MAX] = {false};

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                is_locked[i] = true;
                break;
            }
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (!is_locked[i])
        {
            printf("%s\n", candidates[i]);
        }
    }
}