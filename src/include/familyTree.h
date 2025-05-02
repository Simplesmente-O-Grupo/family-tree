#ifndef FAMILY_TREE_H // include protection.
#define FAMILY_TREE_H

typedef struct FamilyTree
{
    int id;              /* Unique identifier.*/
    char firstName[100]; /* Firt Name of Person */
    char middleName[100];
    char lastName[100];
    int dateOfBirth;
    int dateOfDeath;
    struct FamilyTree *father;      /* Pointer to father, the first must be initate as NULL */
    struct FamilyTree *children;    /* Pointer to Array of children */
    struct FamilyTree *nextBrother; /* Linked List */
    char specialDescription[300];   /* Special description about person 299 + \0 */
    int childrenCount;              /* Children quantity */
    bool lifeStatus;
} FamilyTree;

#endif
