#include "include/familyTree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

Person *createPerson(int id, char *firstName, char *middleName, char *lastName, char *description, int dateOfBirth, int dateOfDeath, bool isAlive) {
	Person *person = malloc(sizeof (Person));
	if (person == NULL) return NULL;

	/* Verificar se já existe uma pessoa com o mesmo ID */
	/* TODO: Função para verificar Ids. */

	/* Preencher dados */
	person->id = id;
	strncpy(person->firstName, firstName, MAX_NAME_LEN);
	strncpy(person->middleName, middleName, MAX_NAME_LEN);
	strncpy(person->lastName, lastName, MAX_NAME_LEN);
	strncpy(person->description, description, MAX_NAME_LEN);
	person->dateOfBirth = dateOfBirth;
	person->dateOfDeath = dateOfDeath;
	person->isAlive = isAlive;
	person->parent = NULL;
	person->children = NULL;
	person->nextBrother = NULL;

	return person;
}
