#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "../src/include/familyTree.h"

void internal_print_tree(Person *root, int level) {
	/* Caso base, pessoa é nulo */
	if (root == NULL) return;

	for (int i = 0; i < level; i++) {
		printf("\t");
	}
	printf("%s %s %s\n", root->firstName, root->middleName, root->lastName);

	/* Continue com os filhos */
	internal_print_tree(root->children, level + 1);
	/* Continue com os irmãos */
	internal_print_tree(root->nextSibling, level);
}

void printTree(Person *root) {
	internal_print_tree(root, 0);
}

int main() {
	printf("Criando pessoas...   ");

	Person *joseph = createPerson(1, "Joseph", "", "Joestar", "desc", -1554595200, 0, true);
	Person *holly = createPerson(2, "Holly", "", "Kujo", "desc", -883612800, 0, true);
	Person *josuke = createPerson(3, "Josuke", "", "Higashikata", "desc", 410227200, 0, true);
	Person *jotaro = createPerson(4, "Jotaro", "", "Kujo", "desc", 31536000, 0, true);

	assert(joseph != NULL);
	assert(holly != NULL);
	assert(josuke != NULL);
	assert(jotaro != NULL);
	printf("SUCESSO!\n");

	printf("Adicionando parentesco...   ");

	addChild(joseph, holly);
	addChild(joseph, josuke);
	addChild(holly, jotaro);

	printf("SUCESSO!\n");

	printf("Verificando parentesco...   ");

	assert(joseph->parent == NULL);
	assert(joseph->children == josuke);
	assert(joseph->children->nextSibling == holly);
	assert(joseph->children->nextSibling->nextSibling == NULL);
	assert(joseph->nextSibling == NULL);
	assert(joseph->prevSibling == NULL);

	assert(josuke->parent == joseph);
	assert(josuke->nextSibling == holly);
	assert(josuke->nextSibling->nextSibling == NULL);
	assert(josuke->prevSibling == NULL);
	assert(josuke->children == NULL);

	assert(holly->parent == joseph);
	assert(holly->nextSibling == NULL);
	assert(holly->children == jotaro);
	assert(holly->children->nextSibling == NULL);
	assert(holly->prevSibling == josuke);

	assert(jotaro->parent == holly);
	assert(jotaro->nextSibling == NULL);
	assert(jotaro->children == NULL);
	assert(jotaro->prevSibling == NULL);
	printf("SUCESSO!\n");

	printTree(joseph);

	printf("Removendo algumas pessoas...   ");
	removePerson(holly);
	assert(josuke->nextSibling == NULL);
	printf("SUCESSO!\n");

	printTree(joseph);

	free(joseph);
	free(josuke);
	return 0;
}
