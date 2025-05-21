#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "context.h"

// Salva a árvore em um arquivo Jason
void saveTreeToJSON(Context *ctx, const char *filename);

// Solicita ao usuário o nome do arquivo e chama saveTreeToJSON.
void SaveTreeNameUser(Context *ctx);
#endif 
