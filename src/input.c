#include "include/input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void clearInputBuffer(void)
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;
}

int askInt(const char *prompt)
{
	int val;
	printf("%s", prompt);
	while (scanf("%d", &val) != 1)
	{ // Loop até entrada válida
		printf("Entrada inválida. Digite um número: ");
		clearInputBuffer();
		; // Limpa buffer
	}
	clearInputBuffer();
	return val;
}

char *getnstr(char *str, int n)
{
	if (!fgets(str, n, stdin))
		return NULL;
	str[strcspn(str, "\n")] = '\0'; // Remove '\n' de forma segura
	return str;
}

char *askString(const char *prompt)
{
	char buffer[256];
	printf("%s", prompt);
	if (!fgets(buffer, sizeof(buffer), stdin))
		return NULL;
	buffer[strcspn(buffer, "\n")] = '\0'; // Remove '\n'

	// Aloca memória e retorna a string
	char *str = malloc(strlen(buffer) + 1);
	if (str)
		strcpy(str, buffer);
	return str;
}
