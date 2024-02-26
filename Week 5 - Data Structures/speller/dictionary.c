// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int Nsize = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int h = hash(word);
    node *temp = NULL;
    temp = table[h];
    while (temp != NULL)
    {
        int comp = strcasecmp(word, temp -> word);
        if (comp == 0)
        {
            return true;
        }
        temp = temp -> next;
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    switch (toupper(word[0]))
    {
        case 'A':
            return 0;
        case 'B':
            return 1;
        case 'C':
            return 2;
        case 'D':
            return 3;
        case 'E':
            return 4;
        case 'F':
            return 5;
        case 'G':
            return 6;
        case 'H':
            return 7;
        case 'I':
            return 8;
        case 'J':
            return 9;
        case 'K':
            return 10;
        case 'L':
            return 11;
        case 'M':
            return 12;
        case 'N':
            return 13;
        case 'O':
            return 14;
        case 'P':
            return 15;
        case 'Q':
            return 16;
        case 'R':
            return 17;
        case 'S':
            return 18;
        case 'T':
            return 19;
        case 'U':
            return 20;
        case 'V':
            return 21;
        case 'W':
            return 22;
        case 'X':
            return 23;
        case 'Y':
            return 24;
        case 'Z':
            return 25;
    }
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char dict[LENGTH + 1];
    bool cond = false;
    while (cond == false)
    {
        if (fscanf(file, "%s", dict) == EOF)
        {
            break;
        }
        int h = hash(dict);
        node *point = malloc(sizeof(node));
        if (point == NULL)
        {
            return false;
        }
        if (table[h] != NULL)
        {
            strcpy(point -> word, dict);
            point -> next = table[h];
            table[h] = point;
        }
        else
        {
            strcpy(point -> word, dict);
            table[h] = point;
            table[h] -> next = NULL;
        }
        Nsize++;
    }
    fclose(file);
    // TODO
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return Nsize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *temp = NULL;
    for (int i = 0; i < N; i++)
    {
        temp = table[i];
        node *del = temp;
        while (temp != NULL)
        {
            temp = temp -> next;
            free(del);
            del = temp;
        }
    }
    return true;
}