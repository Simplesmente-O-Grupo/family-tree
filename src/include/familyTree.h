#ifndef FAMILY_TREE_H // include protection.
#define FAMILY_TREE_H
#include <stdbool.h>

#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 300

typedef struct Person
{
    int id;              /* Unique identifier.*/
    char firstName[MAX_NAME_LEN]; /* Firt Name of Person */
    char middleName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];   /* Special description about person 299 + \0 */
    int dateOfBirth;
    int dateOfDeath;
	bool isAlive;
    struct Person *parent;      /* Pointer to parent, the first must be initate as NULL */
    struct Person *children;    /* Pointer to Array of children */
    struct Person *nextSibling; /* Linked List */
	struct Person *prevSibling; 
} Person;

Person *createPerson(int id, char *firstName, char *middleName, char *lastName, char *description, int dateOfBirth, int dateOfDeath, bool isAlive);

void addChild(Person *parent, Person *child);
void removePerson(Person *root);

#endif
