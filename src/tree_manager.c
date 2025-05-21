#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "include/context.h"
#include "include/familyTree.h"
#include "include/ui_utils.h"
#include "include/input.h"

/* Como esta função mantém um estado local, ela possui um loop
 * interno ao invés de voltar para main.c
 */
void treeManagerScreen(Context *appContext) {
	int option;
	Person *localRoot = appContext->treeRoot;

	while (appContext->screenState == TREE_MANAGER) {
		clearScreen();
		printTree(localRoot);
		printf("\n");
		printf("1: Alterar pessoa   4: Selecionar pessoa\n");
		printf("2: Remover pessoa   5: Limpar seleção\n");
		printf("3: Adicionar pessoa 6: Exibir árvore\n");
		printf("4: Voltar           7: Buscar pessoa \n");

		option = askInt("Escolha uma opção: ");

		switch (option) {
			case 1:
			break;
			case 2:
			break;
			case 3:
			Person *newPerson = createPersonDialog();
				if (newPerson) {
					int parentId = askInt("Digite o ID do pai/mãe: ");

					// Lógica para encontrar e adicionar como filho
					Person *parent = findPersonById(appContext->treeRoot, parentId);
					if (parent)
					{
						addChild(parent, newPerson);
						printf("Pessoa adicionada com sucesso!\n");
					}
					else {
						printf("Pai/Mãe não encontrado.\n");
						free(newPerson);
					}
				}

			break;
			case 4:
				appContext->screenState = MAIN_MENU;
				removePerson(appContext->treeRoot);
			break;
			case 5:
			break;

			case 6:
				printTree(appContext->treeRoot);
			break;

			case 7:
				Person **result = searchPersonDialog(appContext->treeRoot);
				if (result) {
					// Faça algo com a pessoa selecionada (result[0])
					printf("\nPessoa selecionada: %s %s\n",
			result[0]->firstName, result[0]->lastName);
					free(result);
				}

			break;
			default:
				printf("Opção Inválida.\n");
		}
	}
}
