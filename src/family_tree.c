#include "include/familyTree.h"
#include "include/input.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

Person *createPersonDialog(void) {
	Person *person = malloc(sizeof (Person));
	if (person == NULL) {
		fprintf(stderr, "Não foi possível alocar memória para pessoa.\n");
		return NULL;
	}

	struct tm time = {0};

	/* Preencher dados */
	person->id = askInt("\nID: ");

	while (getchar() != '\n' && !feof(stdin));
	/* Verificar se já existe uma pessoa com o mesmo ID */
	/* TODO: Função para verificar Ids. */

	printf("Nome: ");
	getnstr(person->firstName, MAX_NAME_LEN);

	printf("Nome do meio (pode ser vazio): ");
	getnstr(person->middleName, MAX_NAME_LEN);

	printf("Sobrenome: ");
	getnstr(person->lastName, MAX_NAME_LEN);

	printf("Descrição: ");
	getnstr(person->description, MAX_NAME_LEN);

	time.tm_year = askInt("Ano de nascimento: ") - 1900;
	time.tm_mon = askInt("Digite o mês de nascimento: ") - 1;
	time.tm_mday = askInt("Digite o dia de nascimento: ");

	person->dateOfBirth = mktime(&time);

	int tmp = askInt("Esta pessoa morreu? [1/0] ");
	person->isAlive = (tmp == 0);
	if (person->isAlive) {
		person->dateOfDeath = -1;
	} else {
		struct tm timeDeath = {0};
		timeDeath.tm_year = askInt("Ano da morte: ") - 1900;
		timeDeath.tm_mon = askInt("Digite o mês da morte: ") - 1;
		timeDeath.tm_mday = askInt("Digite o dia da morte: ") - 1900;
		person->dateOfDeath = mktime(&timeDeath);
	}

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

static void _printTree(Person *root, int level) {
	/* Caso base: a raíz não existe */
	if (root == NULL) return;

	/* Caso geral: imprimir com base no nível */
	printf("ID: %d | ", root->id);
	for (int i = 0; i < level; i++) {
		putchar('\t');
	}
	printf("%s %s %s\n", root->firstName, root->middleName, root->lastName);

	/* Imprimir os filhos */
	_printTree(root->children, level + 1);

	/* Imprimir os irmãos */
	_printTree(root->nextSibling, level);
}

void printTree(Person *root) {
	_printTree(root, 0);
}

int countPeople(Person *root) {
	/* Caso base: Pessoa não existe */
	if (root == NULL) return 0;

	/* Caso geral: Pessoa existe */
	int tmp = countPeople(root->nextSibling);
	return 1 + countPeople(root->children) + tmp;
}

Person *personById(Person *root, int id) {
	/* Caso base: Pessoa não existe */
	if (root == NULL) return NULL;
	/* Caso base: Pessoa foi encontrada */
	if (root->id == id) return root;

	/* Busque pelos irmãos */
	Person *siblings = personById(root->nextSibling, id);
	if (siblings != NULL) return root;

	/* Busque pelos filhos */
	return personById(root->children, id);
}
