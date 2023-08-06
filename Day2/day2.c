// Day 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 64
#define LINE_FORMAT_LEN 4

enum result { Loss, Tie = 3, Win = 6 };
enum item { Rock = 1, Paper, Scissors };


// Part 1
// Opponent key (left column):
//  A = Rock, B = Paper, C = Scissors
// My key (right key):
//  X = Rock, Y = Paper, Z = Scissors
int GetHand(char hand)
{
    if( hand == 'A' || hand == 'X' )
    {
        return Rock;
    }
    else if ( hand == 'B' || hand == 'Y' )
    {
        return Paper;
    }
    else if ( hand == 'C' || hand == 'Z' )
    {
        return Scissors;
    }
    else
    {
        perror("INVALID KEY");
        exit(EXIT_FAILURE);
    }
}

// Part 2
// Opponent key (left column):
//  A = Rock, B = Paper, C = Scissors
// My key (right key):
//  X = Lose, Y = Tie, Z = Win
int FindHand(char game_result, int opponent)
{
    if( game_result == 'X')
    {
        if( opponent == Scissors)
            return Paper;
        else if( opponent == Rock )
            return Scissors;
        else
            return Rock;
    }
    else if( game_result == 'Y' )
    {
        return opponent;
    }
    else
    {
        if( opponent == Scissors)
            return Rock;
        else if( opponent == Rock )
            return Paper;
        else
            return Scissors;
    }
}

int GamePoints(char line[MAX_LINE_LENGTH])
{
    int score = 0;
    int opponent;
    int my_hand;

    opponent = GetHand(line[0]);
    // Part 1
    // my_hand = GetHand(line[2]);
    // Part 2
    my_hand = FindHand(line[2], opponent);

    if( opponent == Rock && my_hand == Scissors ||
        opponent == Scissors && my_hand == Paper ||
        opponent == Paper && my_hand == Rock )
    {
        score = Loss + my_hand;
    }
    else if( opponent == Rock && my_hand == Paper ||
        opponent == Scissors && my_hand == Rock ||
        opponent == Paper && my_hand == Scissors )
    {
        score = Win + my_hand;
    }
    else
    {
        score = Tie + my_hand;
    }

    return score;
}

int main(int argc, char* argv[])
{
    clock_t timer = clock();
    double time_elapsed;
    FILE* fptr;

    char line[MAX_LINE_LENGTH];
    int line_len;

    int points = 0;

    fptr = fopen(argv[1], "r");

    if( !fptr )
    {
        perror("File failed to open. Make sure input file is first arg.");
        exit(EXIT_FAILURE);
    }

    while( fgets(line, MAX_LINE_LENGTH, fptr) )
    {
        line_len = strlen(line);

        if( line_len != LINE_FORMAT_LEN )
        {
            perror("Encounterd invalid entry.");
            exit(EXIT_FAILURE);
        }

        points += GamePoints(line);
    }

    printf("Points: %d\n", points);

    fclose(fptr);

    timer = clock() - timer;
    time_elapsed =  (double)timer / CLOCKS_PER_SEC;
    printf("\nProgram took %fs.\n", time_elapsed);

    return EXIT_SUCCESS;
}