#ifndef CONTEXT_H
#define CONTEXT_H

#include "familyTree.h"

typedef enum ScreenState {
	MAIN_MENU,
	IMPORT_SAVED_DATA,
	NEW_TREE,
	TREE_MANAGER,
	PERSON_EDITOR,
	EXIT
} ScreenState;

typedef struct Context {
	ScreenState screenState;
	Person *treeRoot; // Raiz da árvore genealógica
	Person *selected; // Raiz local para exibição
	Person *editing;  // Pessoa a ser editada
} Context;

#endif
