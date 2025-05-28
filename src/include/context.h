#ifndef CONTEXT_H
#define CONTEXT_H

#include "familyTree.h"

/* Estado atual da aplicação */
typedef enum ScreenState {
	MAIN_MENU,
	IMPORT_SAVED_DATA, 
	NEW_TREE,
	TREE_MANAGER,
	PERSON_EDITOR,
	EXIT
} ScreenState;

/* Contexto global da aplicação */
typedef struct Context {
	ScreenState screenState; /* Estado atual */
	Person *treeRoot; // Raiz da árvore genealógica
	Person *selected; // Raiz local para exibição
	Person *editing;  // Pessoa a ser editada
} Context;

#endif
