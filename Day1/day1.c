// Day 1
// Q1: Find the elf carrying the most calories, and enter his total sum.
// Q2: Find the top three elves with the most calories, and enter their total sum.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 64
#define LEADERBOARD_LENGTH 3

void SortLeaderboard(int leaderboard[LEADERBOARD_LENGTH])
{
    int tmp;

    for(int i = 0; i < LEADERBOARD_LENGTH-1; i++)
    {
        if( leaderboard[i] > leaderboard[i+1])
        {
            tmp = leaderboard[i+1];
            leaderboard[i+1] = leaderboard[i];
            leaderboard[i] = tmp;
        }
    }
}

void PrintLeaderboard(int leaderboard[LEADERBOARD_LENGTH])
{
    int leaderboard_sum = 0;
    // The way I am monitoring the leaderboard requires this print or the alg to iterate in reverse.
    int index;
    printf("= Leaderboard =\n");

    for(int i = LEADERBOARD_LENGTH; i > 0; i--)
    {
        index = -1*i + LEADERBOARD_LENGTH;
        leaderboard_sum += leaderboard[index];
        printf("%d. %d calorie sum.\n", index + 1, leaderboard[index]);
    }
    printf("Total sum: %d\n", leaderboard_sum);
}

int main (int argc, char* argv[])
{
    clock_t timer = clock();
    double time_elapsed;
    FILE* fptr;
    char line[MAX_LINE_LENGTH];

    int leaderboard[LEADERBOARD_LENGTH] = {0};
    int leaderboard_sum = 0;

    int line_len;
    int calories;
    int calorie_sum;


    fptr = fopen(argv[1], "r");

    if( !fptr )
    {
        perror("File failed to open. Make sure input file is first arg.");
        exit(EXIT_FAILURE);
    }

    while( fgets(line, MAX_LINE_LENGTH, fptr) )
    {
        line_len = strlen(line) - 1;

        // New elf encountered
        if( !line_len )
        {
            if( calorie_sum > leaderboard[0] )
            {
                leaderboard[0] = calorie_sum;
                SortLeaderboard(leaderboard);
            }
            calorie_sum = 0;
            continue;
        }
        line[line_len] = '\0';
        calories = atoi(line);

        if( !calories )
        {
            perror("Failed to parse calorie entry. Goodbye.\n");
            exit(EXIT_FAILURE);
        }

        calorie_sum += calories;
    }

    PrintLeaderboard(leaderboard);
    
    timer = clock() - timer;
    time_elapsed =  (double)timer / CLOCKS_PER_SEC;
    printf("\nProgram took %fs.\n", time_elapsed);

    return EXIT_SUCCESS;
}
