#ifndef SAVE_H
#define SAVE_H
#include "familyTree.h"

/* "dd/mm/yyyy"
 * 11
 */
typedef struct SerializedPerson {
	int id;
	char firstName[MAX_NAME_LEN];
    char middleName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    char dateOfBirth[11];
    char dateOfDeath[11];
    char isAlive;
    int parent;
} SerializedPerson;

void saveToFile(char *path, Person *root);
bool unserializeTree(char *path, Person **root);
#endif /* SAVE_H */
