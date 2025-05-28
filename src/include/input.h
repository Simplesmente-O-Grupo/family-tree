#ifndef INPUT_H
#define INPUT_H
#include <time.h>

// Solicita um número inteiro ao usuário
int askInt(const char *prompt);

// Lê uma string com tamanho limitado
char *getnstr(char *str, int n);

// Pergunta e aloca uma string do usuário
char *askString(const char *prompt);

// Pergunta uma data ao usuário
time_t askDate();

#endif
