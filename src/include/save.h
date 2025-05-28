#ifndef SAVE_H
#define SAVE_H
#include "familyTree.h"

/* Formato de pessoa que pode ser salvo na
 * memória não volátil
 */
typedef struct SerializedPerson {
	int id;
	char firstName[MAX_NAME_LEN];
    char middleName[MAX_NAME_LEN];
    char lastName[MAX_NAME_LEN];
    char description[MAX_DESC_LEN];
	/* Campos de data foram transformados em string.
	 * O tipo time_t é diferente para cada implementação,
	 * então para manter a portabilidade, o formato de data
	 * é convertido para string e vice-versa
	 */
    char dateOfBirth[11];
    char dateOfDeath[11];
	/* zero ou um, defini o tipo
	 * char porque é muito pequeno
	 */
    char isAlive;
	/* Ao invés de guardar o ponteiro, guarda-se o ID.
	 * Não é necessário guardar informação dos irmãos e 
	 * filhos porque addChild() reconstrói isso.
	 */
    int parent;
} SerializedPerson;

/* Guarda a árvore em um arquivo */
void saveToFile(char *path, Person *root);
/* Carrega a árvore de um arquivo */
/* Retorno é o sucesso desta operação */
bool unserializeTree(char *path, Person **root);
#endif /* SAVE_H */
