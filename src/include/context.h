#ifndef CONTEXT_H
#define CONTEXT_H

#include "familyTree.h"

typedef enum ScreenState {
	MAIN_MENU,
	IMPORT_SAVED_DATA,
	NEW_TREE,
	TREE_MANAGER,
	EXIT
} ScreenState;

typedef struct Context {
	ScreenState screenState;
	Person *treeRoot;
} Context;

#endif /* CONTEXT_H */
