#ifndef FAMILY_TREE_H
#define FAMILY_TREE_H

#include <stdbool.h>
#include <time.h>

#define MAX_NAME_LEN 100
#define MAX_DESC_LEN 300

// Forward declaration
typedef struct Person Person;
typedef struct HashNode HashNode;
typedef struct HashTable HashTable;

struct HashNode
{
    char name[MAX_NAME_LEN];
    Person *person;
    HashNode *next;
};

struct HashTable
{
    HashNode **buckets;
    int size;
};

struct Person
{
    int id;
    char firstName[MAX_NAME_LEN];
    char middleName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
    time_t dateOfBirth;
    time_t dateOfDeath;
    bool isAlive;
    Person *parent;
    Person *children;
    Person *nextSibling;
    Person *prevSibling;
};

// Funções básicas
Person *createPersonDialog(void);
void addChild(Person *parent, Person *child);
void removePerson(Person *root);
void printTree(Person *root);

// Funções de busca
Person *findPersonById(Person *root, int id);
Person **searchPersonByName(Person *root, const char *name);
Person **searchPersonDialog(Person *root);

// Funções de hash table
HashTable *createHashTable(int size);
void insertIntoHashTable(HashTable *table, const char *name, Person *person);
Person **searchInHashTable(HashTable *table, const char *searchTerm);
void freeHashTable(HashTable *table);

// Utilitários
void displayPersonDetails(Person *person);
bool checkIdExists(Person *root, int id);
void countPersonsInTree(Person *root, int *count);
int countPeople(Person *root);

#endif
