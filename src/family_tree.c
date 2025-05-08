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
	person->nextSibling = NULL;
	person->prevSibling = NULL;

	return person;
}

void addChild(Person *parent, Person *child) {
	/* Unir o filho ao pai */
	child->parent = parent;

	/* Unir o pai ao filho */
	Person *sibling = parent->children;
	parent->children = child;
	child->nextSibling = sibling;
	if (sibling != NULL) {
		sibling->prevSibling = child;
	}
}

void removePerson(Person *root) {
	/* Caso base: A pessoa não existe */
	if (root == NULL) return;

	/* Ajustar a lista de irmãos */
	if (root->prevSibling != NULL) {
		root->prevSibling->nextSibling = root->nextSibling;
	}
	if (root->nextSibling != NULL) {
		root->nextSibling->prevSibling = root->prevSibling;
	}

	/* Remover os filhos */
	removePerson(root->children);

	/* Remover a pessoa */
	free(root);
}
