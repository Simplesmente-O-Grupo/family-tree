#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "include/json_serializer.h"
#include "include/context.h"
#include "include/familyTree.h"
#include "include/ui_utils.h"
#include "include/input.h"
#include "include/save.h"

static void removePersonDialog(Person *root) {
	clearScreen();
	printTree(root);
	int id = askInt("Digite o ID da pessoa para remover: ");
	Person *target = findPersonById(root, id);
	if (target != NULL) {
		removePerson(target);
	} else {
		printf("Pessoa não encontrada.\n");
	}
}

/* NUNCA passe a árvore global no argumento
 * localRoot, senão a função  CAUSARÁ vazamento de meória.
 */
static void selectPersonDialog(Context *appContext, Person **localRoot) {
	clearScreen();
	printTree(*localRoot);

	int id = askInt("Digite o ID da pessoa: ");
	Person *target = findPersonById(*localRoot, id);

	if (target != NULL) {
		if (target->id == (*localRoot)->id) {
			*localRoot = appContext->treeRoot;
		} else {
			*localRoot = target;
		}
	} else {
		printf("Pessoa não encontrada.\n");
	}
}

/* Como esta função mantém um estado local, ela possui um loop
 * interno ao invés de voltar para main.c
 */
void treeManagerScreen(Context *appContext) {
	int option;
	char path[256];
	int id;

	if (appContext->selected == NULL) {
		appContext->selected = appContext->treeRoot;
	}

	clearScreen();
	printTree(appContext->selected);
	printf("\n");
	printf("1: Visualizar pessoa 5: Selecionar pessoa\n");
	printf("2: Remover pessoa    6: Limpar seleção\n");
	printf("3: Adicionar pessoa  7: Salvar árvore\n");
	printf("4: Voltar            8: Buscar pessoa \n");
	printf("9: Salvar árvore em Json\n");

	option = askInt("Escolha uma opção: ");

	Person *newPerson;
	Person **result;
	switch (option) {
		case 1:
			id = askInt("Digite o ID da pessoa: ");

			Person *toEdit = findPersonById(appContext->selected, id);
			appContext->editing = toEdit;
			if (toEdit != NULL) {
				appContext->screenState = PERSON_EDITOR;
			}
			break;
		case 2:
			removePersonDialog(appContext->selected);
			break;
		case 3:
			newPerson = createPersonDialog();
			if (newPerson) {
				int parentId = askInt("Digite o ID do pai/mãe: ");

				// Lógica para encontrar e adicionar como filho
				Person *parent = findPersonById(appContext->treeRoot, parentId);
				if (parent) {
					addChild(parent, newPerson);
					printf("Pessoa adicionada com sucesso!\n");
				} else {
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
			selectPersonDialog(appContext, &(appContext->selected));
			break;

		case 6:
			appContext->selected = appContext->treeRoot;
			break;

		case 7:
			printf("Digite o caminho do arquivo: ");
			getnstr(path, 256);
			saveToFile(path, appContext->treeRoot);
			break;

		case 8:
			result = searchPersonDialog(appContext->treeRoot);
			if (result) {
				// Faça algo com a pessoa selecionada (result[0])
				printf("\nPessoa selecionada: %s %s\n", 
					result[0]->firstName, result[0]->lastName);
				free(result);
			}
			break;
		case 9:
			SaveTreeNameUser(appContext);
			break;
		default:
			printf("Opção Inválida.\n");
	}
}
