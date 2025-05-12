#include <stdio.h>

#include "include/states.h"

#include "include/main-menu-screen.h"


int main() {
	State appState = MAIN_MENU;

	while (appState != EXIT) {
		switch(appState) {
			case MAIN_MENU:
			mainMenuScreen(&appState);
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

