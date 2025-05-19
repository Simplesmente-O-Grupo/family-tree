#include <stdio.h>
#include <stdbool.h>

#include "../include/context.h"
#include "../include/familyTree.h"
#include "../include/ui_utils.h"
#include "../include/input.h"

static void printMenu();

/* Como esta função mantém um estado local, ela possui um loop
 * interno ao invés de voltar para main.c
 */
void treeManagerScreen(Context *appContext) {
	bool exitScreen = false;
	int option;
	Person *localRoot = appContext->treeRoot;

	while (!exitScreen) {
		clearScreen();
		printTree(localRoot);
		printMenu();
		option = askInt("Escolha uma opção: ");

		switch (option) {
			case 1:
			break;
			case 2:
			break;
			case 3:
				appContext->screenState = MAIN_MENU;
				removePerson(appContext->treeRoot);
				exitScreen = true;
			break;
			case 4:
			break;
			case 5:
			break;
		}
	}
}

static void printMenu() {
	printf("1: Alterar pessoa 4: Selecionar pessoa\n");
	printf("2: Remover Pessoa 5: Limpar seleção\n");
	printf("3: Voltar\n");
	printf("\n");
}
