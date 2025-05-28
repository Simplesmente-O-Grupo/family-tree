#include <stdio.h>
#include <stdlib.h>

/* Limpa a tela em mais de uma
 * plataforma diferente.
 */
void clearScreen(void) {
#ifdef _WIN32
	system("cls");
#else
	printf("\e[1;1H\e[2J");
#endif /* WIN32 */
}
