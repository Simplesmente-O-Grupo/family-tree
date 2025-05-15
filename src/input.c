#include <stdio.h>

int askInt(char *prompt) {
	int ret, answer;

	do {
		printf("%s", prompt);
		ret = scanf("%d", &answer);
	} while (ret != 1);

	return answer;
}

void getnstr(char *str, int n) {
	int ch, acc = 0;

	do {
		ch = getchar();

		if (ch == '\n')
			str[acc++] = '\0';
		else
			str[acc++] = ch;
	} while (ch != '\n' && ch != EOF && acc < n);
}
