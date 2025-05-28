#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "include/save.h"
#include "include/familyTree.h"

static SerializedPerson serializePerson(Person *person) {
	SerializedPerson neop;
	
	neop.id = person->id;
	strcpy(neop.firstName, person->firstName);
	strcpy(neop.middleName, person->middleName);
	strcpy(neop.lastName, person->lastName);
	strcpy(neop.description, person->description);

	struct tm *time;
	char date[11];
	time = localtime(&(person->dateOfBirth));
	strftime(date, 11, "%d/%m/%Y", time);
	strcpy(neop.dateOfBirth, date);

	time = localtime(&(person->dateOfDeath));
	strftime(date, 11, "%d/%m/%Y", time);
	strcpy(neop.dateOfDeath, date);

	neop.isAlive = person->isAlive ? 1 : 0;

	neop.parent = person->parent ? person->parent->id : -1;
	
	return neop;
}

static void _serializeTree(SerializedPerson *people, Person *root, int *i) {
	/* Caso base, não tem o que salvar */
	if (root == NULL) return;

	/* Caso geral, serializar pessoa e ir para a próxima */
	people[(*i)++] = serializePerson(root);
	_serializeTree(people, root->nextSibling, i);
	_serializeTree(people, root->children, i);
}

SerializedPerson *serializeTree(Person *root, size_t *qnt) {
	SerializedPerson *people = malloc(sizeof(SerializedPerson) * countPeople(root));
	if (people == NULL) return NULL;

	int i = 0;

	_serializeTree(people, root, &i);

	*qnt = i;
	return people;
}

void saveToFile(char *path, Person* root) {
	size_t qnt;
	SerializedPerson *people = serializeTree(root, &qnt);

	FILE *fp = fopen(path, "wb");
	if (fp == NULL) {
		free(people);
		fprintf(stderr, "Não foi possível criar o arquivo");
		getchar();
		return;
	}

	fwrite(people, sizeof(SerializedPerson), qnt, fp);

	fclose(fp);
	free(people);
}

static bool unserializePerson(Person **root, FILE *fp) {
	Person *neop = malloc(sizeof(Person));
	if (neop == NULL) return false;
	/* Lê a próxima pessoa */
	SerializedPerson person;
	if (fread(&person, sizeof(SerializedPerson), 1, fp) < 1) {
		return false;
	}
	
	neop->id = person.id;
	strcpy(neop->firstName, person.firstName);
	strcpy(neop->middleName, person.middleName);
	strcpy(neop->lastName, person.lastName);
	strcpy(neop->description, person.description);

	struct tm time = {0};
	sscanf(person.dateOfBirth,"%d/%d/%d", &(time.tm_mday), &(time.tm_mon), &(time.tm_year));
	time.tm_mon -= 1;
	time.tm_year -= 1900;
	neop->dateOfBirth = mktime(&time);

	memset(&time, 0, sizeof(struct tm));
	sscanf(person.dateOfDeath,"%d/%d/%d", &(time.tm_mday), &(time.tm_mon), &(time.tm_year));
	time.tm_mon -= 1;
	time.tm_year -= 1900;
	neop->dateOfDeath = mktime(&time);

	neop->isAlive = person.isAlive ? true : false;

	neop->parent = NULL;
	neop->children = NULL;
	neop->prevSibling = NULL;
	neop->nextSibling = NULL;

	if (person.parent < 0) {
		*root = neop;
	} else {
		Person *parent = findPersonById(*root, person.parent);
		assert(parent != NULL);
		addChild(parent, neop);
	}
	return true;
}

bool unserializeTree(char *path, Person **root) {
	removePerson(*root);
	FILE *fp = fopen(path, "rb");
	if (fp == NULL) return false;

	bool reading = unserializePerson(root, fp);
	while (reading) {
		reading = unserializePerson(root, fp);
	}
	fclose(fp);

	if (*root == NULL) return false;
	return true;
}
