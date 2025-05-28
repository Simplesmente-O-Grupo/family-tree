#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "include/input.h"

void clearInputBuffer(void) {
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

/* Pergunta um inteiro ao usuário */
int askInt(const char *prompt) {
	int val;
	printf("%s", prompt);
	while (scanf("%d", &val) != 1) { // Loop até entrada válida
		printf("Entrada inválida. Digite um número: ");
		clearInputBuffer();
	}
	clearInputBuffer();
	return val;
}

/* Obtém uma string de no máximo n caracteres de
 * stdin
 */
char *getnstr(char *str, int n) {
	if (!fgets(str, n, stdin))
		return NULL;
	str[strcspn(str, "\n")] = '\0'; // Remove '\n' de forma segura
	return str;
}

/* Pergunta uma data ao usuário e retorna uma timestamp 
 * (hora, minuto, segundo, etc. são definidos como zero)
 */
time_t askDate() {
	struct tm time = {0};
	
	time.tm_year = askInt("Ano: ") - 1900;
	time.tm_mon = askInt("Mês: ") - 1;
	time.tm_mday = askInt("Dia: ");

	return mktime(&time);
}

/* pede uma string e retorna uma string alocada */
char *askString(const char *prompt) {
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
