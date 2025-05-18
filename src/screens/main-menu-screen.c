#include <stdio.h>
#include <stdlib.h>
#include "include/context.h"
#include "include/familyTree.h"
#include "include/input.h"

void treeManagerScreen(Context *ctx)
{
    int choice;
    do
    {
        printf("\n===== MENU ÁRVORE =====\n");
        printf("1. Adicionar nova pessoa\n");
        printf("2. Buscar pessoa por nome\n");
        printf("3. Exibir árvore genealógica\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha: ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n')
                ;
            continue;
        }
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        case 1:
        {
            Person *newPerson = createPersonDialog();
            if (newPerson)
            {
                printf("Digite o ID do pai/mãe (ou 0 se não tiver): ");
                int parentId = askInt("");

                if (parentId == 0)
                {
                    // Lógica para adicionar como irmão da raiz
                    newPerson->nextSibling = ctx->treeRoot->nextSibling;
                    if (ctx->treeRoot->nextSibling)
                    {
                        ctx->treeRoot->nextSibling->prevSibling = newPerson;
                    }
                    ctx->treeRoot->nextSibling = newPerson;
                    newPerson->prevSibling = ctx->treeRoot;
                }
                else
                {
                    // Lógica para encontrar e adicionar como filho
                    Person *parent = findPersonById(ctx->treeRoot, parentId);
                    if (parent)
                    {
                        addChild(parent, newPerson);
                        printf("Pessoa adicionada com sucesso!\n");
                    }
                    else
                    {
                        printf("Pai/Mãe não encontrado.\n");
                        free(newPerson);
                    }
                }
            }
            break;
        }
        case 2:
            searchPersonDialog(ctx->treeRoot);
            break;
        case 3:
            printTree(ctx->treeRoot);
            break;
        case 0:
            ctx->screenState = MAIN_MENU;
            break;
        default:
            printf("Opção inválida!\n");
        }
    } while (ctx->screenState == TREE_MANAGER);
}