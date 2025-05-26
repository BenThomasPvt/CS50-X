#include <cs50.h>
#include <stdio.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // ... (unchanged code)

    // Continue with the rest of your main function

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until a winner exists
    while (true)
    {
        tabulate();
        bool won = print_winner();
        if (won)
        {
            break;
        }

        int min = find_min();
        bool tie = is_tie(min);

        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min);

        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0;
}

bool vote(int voter, int rank, string name)
{
    // Iterate through candidates to find a match for the provided name
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // If the candidate is not eliminated, record the preference
            if (!candidates[i].eliminated)
            {
                preferences[voter][rank] = i;
                return true;
            }
        }
    }
    // Return false if the name is not found or the candidate is eliminated
    return false;
}

void tabulate(void)
{
    // Iterate through each voter's preferences
    for (int i = 0; i < voter_count; i++)
    {
        // Iterate through each voter's ranked preferences
        for (int j = 0; j < candidate_count; j++)
        {
            int candidate_index = preferences[i][j];

            // If the candidate is not eliminated, add a vote and break
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break;
            }
        }
    }
}

bool print_winner(void)
{
    // Iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If a candidate has more than half of the total votes, print the
        // winner
        if (candidates[i].votes > voter_count / 2)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // No winner found
    return false;
}

int find_min(void)
{
    int min_votes = voter_count; // Initialize to a large value

    // Iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate is not eliminated and has fewer votes than the
        // current minimum, update the minimum
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    // Return the minimum votes
    return min_votes;
}

bool is_tie(int min)
{
    // Iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate is not eliminated and has a different number of
        // votes than the minimum, return false
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    // All non-eliminated candidates have the same number of votes, indicating a
    // tie
    return true;
}

void eliminate(int min)
{
    // Iterate through candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If the candidate has the minimum number of votes, eliminate them
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
