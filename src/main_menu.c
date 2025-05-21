#include <stdio.h>

#include "include/context.h"
#include "include/ui_utils.h"

static void printLogo(void);
static void printMenu();

void mainMenuScreen(Context *ctx)
{
	int option, ret;
	do
	{
		printMenu();
		printf("\nEscolha uma opção: ");
		ret = scanf("%d", &option);
		while (getchar() != '\n' || feof(stdin))
			;
		clearScreen();
	} while (ret != 1 || option > 3 || option < 1);

	switch (option)
	{
	case 1:
		ctx->screenState = NEW_TREE;
		break;

	case 2:
		ctx->screenState = IMPORT_SAVED_DATA;
		break;

	case 3:
		ctx->screenState = EXIT;
		break;
	}
}

static void printMenu()
{
	printLogo();
	printf("\n1: Iniciar nova árvore.\n");
	printf("2: Editar árvore existente.\n");
	printf("3: Sair.\n");
}

static void printLogo(void)
{
	printf("    ______                _ __         ______             \n");
	printf("   / ____/___ _____ ___  (_) /_  __   /_  __/_______  ___ \n");
	printf("  / /_  / __ `/ __ `__ \\/ / / / / /    / / / ___/ _ \\/ _ \\\n");
	printf(" / __/ / /_/ / / / / / / / / /_/ /    / / / /  /  __/  __/\n");
	printf("/_/    \\__,_/_/ /_/ /_/_/_/\\__, /    /_/ /_/   \\___/\\___/ \n");
	printf("                          /____/                          \n");
	putchar('\n');
	printf("   __   _                   __       ___                          \n");
	printf("  / /  (_)__ ____ ____  ___/ /__    / _ \\___ ___ ___ ___  ___ ____\n");
	printf(" / /__/ / _ `/ _ `/ _ \\/ _  / _ \\  / ___/ -_|_-<(_-</ _ \\/ _ `(_-<\n");
	printf("/____/_/\\_, /\\_,_/_//_/\\_,_/\\___/ /_/   \\__/___/___/\\___/\\_,_/___/\n");
	printf("       /___/                                                      \n");
}
