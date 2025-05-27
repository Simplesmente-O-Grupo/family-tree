#include <stdio.h>
#include <assert.h>

#include "include/context.h"
#include "include/person-editor.h"
#include "include/familyTree.h"
#include "include/ui_utils.h"
#include "include/tree-manager-screen.h"
#include "include/main-menu-screen.h"
#include "include/tree-manager-screen.h"

int main()
{
	Context appContext = {
		.screenState = MAIN_MENU,
		.treeRoot = NULL // Inicializa explicitamente como NULL
	};

	while (appContext.screenState != EXIT)
	{
		switch (appContext.screenState)
		{
			case MAIN_MENU:
				mainMenuScreen(&appContext);
				break;

			case IMPORT_SAVED_DATA:
				// TODO: Implementar importação de dados
				printf("Funcionalidade de importação não implementada ainda.\n");
				appContext.screenState = MAIN_MENU;
				break;

			case NEW_TREE:
				Person *person = createPersonDialog();
				assert(person != NULL && "Falha ao criar pessoa raiz");
				appContext.treeRoot = person;
				appContext.screenState = TREE_MANAGER;
				break;

			case PERSON_EDITOR:
				personEditor(&appContext);
				break;

			case TREE_MANAGER:
				if (appContext.treeRoot == NULL)
				{
					printf("Erro: Árvore não inicializada\n");
					appContext.screenState = MAIN_MENU;
				}
				else
			{
					treeManagerScreen(&appContext);
				}
				break;

			case EXIT:
				// Nada a fazer, o loop será encerrado
				break;

			default:
				printf("Estado inválido! Reiniciando para o menu principal.\n");
				appContext.screenState = MAIN_MENU;
		}
	}

	// Limpeza final
	if (appContext.treeRoot != NULL)
	{
		removePerson(appContext.treeRoot);
		appContext.treeRoot = NULL;
	}

	return 0;
}
