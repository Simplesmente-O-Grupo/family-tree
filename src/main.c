#include <stdio.h>
#include <assert.h>

#include "include/context.h"
#include "include/familyTree.h"
#include "include/ui_utils.h"
#include "include/tree-manager-screen.h"
#include "include/main-menu-screen.h"


int main() {
	Context appContext;
	appContext.screenState = MAIN_MENU;

	while (appContext.screenState != EXIT) {
		switch(appContext.screenState) {
			case MAIN_MENU:
			mainMenuScreen(&appContext);
			break;
			case IMPORT_SAVED_DATA:
			/* Importar os dados da aplicação */
			break;
			case NEW_TREE:
				Person *person = createPersonDialog();
				assert(person != NULL);
				appContext.treeRoot = person;
				appContext.screenState = TREE_MANAGER;
			break;
			case TREE_MANAGER:
				treeManagerScreen(&appContext);
			break;
			case EXIT:
			/* Não faz nada */
			break;
		}
	}

	return 0;
}

