#include <stdio.h>

#include "include/context.h"

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
			/* Criar nova árvore */
			break;
			case EXIT:
			/* Não faz nada */
			break;
		}
	}

	return 0;
}

