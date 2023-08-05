// Day 1
// Q1: Find the elf carrying most calories
// Q2: 

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define NUM_ELVES_IN_LEADERBOARD 3

typedef struct _Elf
{
    unsigned int id;
    unsigned int total_cal;
} Elf;

typedef struct _Node
{
    Elf elf;
    struct _Node* next;
} Node;

Node* CreateNode ()
{
    // Allocate space for the node
    Node* node = malloc(sizeof(Node));
    // Init the next ptr to NULL
    node->next = NULL;

    // Init our elf members to 0
    node->elf.id = 0;
    node->elf.total_cal = 0;

    return node;
}

void AddElf ()
{
    return;
}

Node* PopulateElves(char* file_name)
{
    Node* elf_nodes;
    Node* current_elf;
    Node* new_elf;
    char line[MAX_LINE_LENGTH];
    int id = 1;
    int calories = 0;
    int str_len;

    FILE* fptr;
    
    fptr = fopen(file_name, "r");

    if( !fptr )
    {
        perror("Failed to open file.");
        exit(EXIT_FAILURE);
    }

    // Initialize first entry in list
    elf_nodes = CreateNode();
    elf_nodes->elf.id = id;
    current_elf = elf_nodes;

    while( fgets(line, MAX_LINE_LENGTH, fptr) )
    {
        // For stripping trailing \n
        str_len = strlen(line) - 1;
        
        // If we are just a newline, we make a new elf
        if( !str_len )
        {
            id++;
            new_elf = CreateNode();

            current_elf->next = new_elf;
            new_elf->next = NULL;

            new_elf->elf.id = id;
            new_elf->elf.total_cal = 0;

            current_elf = new_elf;
            
            continue;
        }
        // Remove trailing \n
        line[str_len] = '\0';

        calories = atoi(line);

        if( !calories )
        {
            perror("Invalid calorie input");
            exit(EXIT_FAILURE);
        }

        current_elf->elf.total_cal += calories;
    }

    return elf_nodes;
}

void PrintElves(Node** list_head)
{
    Node* node = *list_head;
    while (node->next)
    {
        printf("Elf %d: %d calories\n", node->elf.id, node->elf.total_cal);
        node = node->next;
    }
    printf("Elf %d: %d calories\n", node->elf.id, node->elf.total_cal);
}

int GetMaxCalorieElf(Node** list_head)
{
    Node* node = *list_head;
    int id = 0;
    int max_calorie = 0;

    while (node->next)
    {
        if( node->elf.total_cal > max_calorie )
        {
            id = node->elf.id;
            max_calorie = node->elf.total_cal;
        }
        node = node->next;
    }

    // Check the last elf!
    if( node->elf.total_cal > max_calorie )
    {
        id = node->elf.id;
        max_calorie = node->elf.total_cal;
    }

    printf("Elf %d takes the cake with %d calories!\n", id, max_calorie);
}

void SortAscending(int top_three[NUM_ELVES_IN_LEADERBOARD])
{
    int tmp;

    for(int x = 0; x < NUM_ELVES_IN_LEADERBOARD-1; x++)
    {
        if( top_three[x] > top_three[x+1])
        {
            tmp = top_three[x+1];
            top_three[x+1] = top_three[x];
            top_three[x] = tmp;
        }
    }
}

int GetTopThreeElfCalories(Node** list_head)
{
    Node* node = *list_head;
    int top_three[NUM_ELVES_IN_LEADERBOARD] = {0,0,0};
    int total = 0;

    while (node->next)
    {
        if( node->elf.total_cal > top_three[0] )
        {
            top_three[0] = node->elf.total_cal;
            SortAscending(top_three);
        }
        node = node->next;
    }

    if( node->elf.total_cal > top_three[0] )
    {
        top_three[0] = node->elf.total_cal;
    }

    for(int i = 0; i < (sizeof(top_three)/sizeof(int)); i++)
    {
        total += top_three[i];
    }

    printf("Top three %d\n", total);

    return total;

}

void DeallocElves(Node** list_head)
{
    Node* current = *list_head;
    Node* next = current->next;

    while ( next )
    {
        free(current);
        current = next;
        next = current->next;
    }

    free(current);
}

int main (int argc, char* argv[])
{
    Node* list_head;

    list_head = PopulateElves(argv[1]);
    // PrintElves(&list_head);
    GetTopThreeElfCalories(&list_head);
    // GetMaxCalorieElf(&list_head);
    DeallocElves(&list_head);

    list_head = NULL;

    return EXIT_SUCCESS;
}
