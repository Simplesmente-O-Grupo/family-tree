#include <stdio.h>

void clearScreen(void) {
#ifdef _WIN32
	system("cls");
#else
	printf("\e[1;1H\e[2J");
#endif /* WIN32 */
}
