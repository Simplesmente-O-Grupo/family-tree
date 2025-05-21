#ifndef INPUT_H
#define INPUT_H

// Solicita um número inteiro ao usuário
int askInt(const char *prompt);

// Lê uma string com tamanho limitado
char *getnstr(char *str, int n);

char *askString(const char *prompt);

#endif