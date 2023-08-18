// Day 3

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 64
// Priority maps a-z to 1-26, and A-Z to 27-52
// Based of ASCII chart we take the offset relative to the desired key space
#define UPPER_OFFSET 38
#define LOWER_OFFSET 96
#define MAX_GROUP_SIZE 3


int GetPriority(char match)
{

    if(isupper(match))
    {
        return (int) match - UPPER_OFFSET;
    }
    else if(islower(match))
    {
        return (int) match - LOWER_OFFSET;
    }
    else
    {
        perror("Match does not map to a priority.");
        exit(EXIT_FAILURE);
    }
}

char FindMatch(char* line)
{
    // Compartment size is 1/2 the line.
    // Let integer division truncate, to account for start at 0th index.
    int compartmentSize = strlen(line)/2;

    // Iterate over compartment 1 with x.
    for(int x = 0; x < compartmentSize; x++)
    {
        // Iterate over compartment 2 with y.
        for(int y = compartmentSize; y <= compartmentSize*2; y++)
        {
            if (line[x] == line[y])
                return line[x];
        }
    }

    return '\0';
}

char FindBadge(char** lines)
{
    int found = 0;
    // Iterate over the first elf's items
    for(int x = 0; x < strlen(lines[0]); x++)
    {
        // Iterate through the remaining elves rucksack
        for(int y = 1; y < MAX_GROUP_SIZE; y++)
        {
            // Iterate over their items
            for(int z = 0; z < strlen(lines[y]); z++)
            {
                if (lines[0][x] == lines[y][z])
                {
                    found++;
                    break;
                }
            }
        }
        if (found == 2)
            return lines[0][x];
        else
            found = 0;
    }

    return '\0';
}

int main(int argc, char* argv[])
{
    clock_t timer = clock();
    double time_elapsed;
    FILE* fptr;

    int lineLength;
    char line[MAX_LINE_LENGTH];
    char match;

    // Used for Part 2
    char* lines[MAX_GROUP_SIZE];
    int groupSize = 0;

    int prioritySum = 0;

    fptr = fopen(argv[1], "r");

    if( !fptr )
    {
        perror("File failed to open. Make sure input file is first arg.");
        exit(EXIT_FAILURE);
    }

    while ( fgets(line, MAX_LINE_LENGTH, fptr) )
    {
        // Part One
        // match = FindMatch(line);

        // Part Two

        // allocate enough memory to store the line.
        lines[groupSize] = malloc(strlen(line));

        // copy data into the allocated buffer. Exclude the copied \n
        memcpy(lines[groupSize], line, strlen(line) - 1);

        // NULL terminate the buffer, and increment group size
        lines[groupSize++][strlen(line) - 1] = '\0';

        if (groupSize < MAX_GROUP_SIZE)
        {
            continue;
        }

        groupSize = 0;

        match = FindBadge(lines);

        // Need to free the allocated buffers after we find a match.
        free(lines[0]);
        free(lines[1]);
        free(lines[2]);

        if (match == '\0')
        {
            perror("Invalid puzzle input. Could not find a match.");
            return EXIT_FAILURE;
        }

        // printf("Aquired match. %c.\n", match);

        prioritySum += GetPriority(match);
    }

    printf("Total Priority Sum: %d\n", prioritySum);

    fclose(fptr);

    timer = clock() - timer;
    time_elapsed =  (double)timer / CLOCKS_PER_SEC;
    printf("\nProgram took %fs.\n", time_elapsed);

    return EXIT_SUCCESS;
}