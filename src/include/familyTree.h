#ifndef FAMILY_TREE_H // include protection.
#define FAMILY_TREE_H
#include <stdbool.h>

typedef struct Person
{
    int id;              /* Unique identifier.*/
    char firstName[100]; /* Firt Name of Person */
    char middleName[100];
    char lastName[100];
    char description[300];   /* Special description about person 299 + \0 */
    int dateOfBirth;
    int dateOfDeath;
	bool isAlive;
    struct Person *father;      /* Pointer to father, the first must be initate as NULL */
    struct Person *children;    /* Pointer to Array of children */
    struct Person *nextBrother; /* Linked List */
} Person;

#endif
