#include <stdio.h>
#include <time.h>
#include "include/familyTree.h"
#include "include/context.h"
#include "include/input.h"


/* Escreve os dados da Pessoa em JSON
 *
 * Essa funcionalidade serve para que seja possível visualizar a árvore
 * em programas externos.
 */
static void writePersonJSON(Person *person, FILE *fp) {
	if (person == NULL) return;

	struct tm *tmpTime;
	char tmpDate[25];

	fprintf(fp, "{\n");
	fprintf(fp, "  \"id\": %d,\n", person->id);
	fprintf(fp, "  \"firstName\": \"%s\",\n", person->firstName);
	fprintf(fp, "  \"middleName\": \"%s\",\n", person->middleName);
	fprintf(fp, "  \"lastName\": \"%s\",\n", person->lastName);
	fprintf(fp, "  \"description\": \"%s\",\n", person->description);

	tmpTime = localtime(&(person->dateOfBirth));
	strftime(tmpDate, 25, "%Y-%m-%d", tmpTime);
	fprintf(fp, "  \"dateOfBirth\": \"%s\",\n", tmpDate);

	fprintf(fp, "  \"isAlive\": %s,\n", person->isAlive ? "true" : "false");

	tmpTime = localtime(&(person->dateOfDeath));
	strftime(tmpDate, 25, "%Y-%m-%d", tmpTime);
	fprintf(fp, "  \"dateOfDeath\": \"%s\",\n", tmpDate);

	fprintf(fp, "  \"children\": [\n");

	//Percorre os filhos
	Person *child = person->children;
	int firstChild = 1;
	while (child != NULL) {
		if (!firstChild)
			fprintf(fp, ",\n");
		writePersonJSON(child, fp);
		firstChild = 0;
		child = child->nextSibling;
	}
	fprintf(fp, "\n  ]\n");
	fprintf(fp, "}");
}

/* Função que salva a árvore em JSON no arquivo com o nome especificado */
void saveTreeToJSON(Context *ctx, const char *filename) {
	FILE *fp = fopen(filename, "w");
	if (!fp) {
		fprintf(stderr, "Erro ao abrir o arquivo %s para escrita.\n", filename);
		return;
	}

	if (ctx->treeRoot == NULL)
		fprintf(fp, "null");
	else
		writePersonJSON(ctx->treeRoot, fp);

	fclose(fp);
}

//Função que solicita ao usuário o nome do arquivo e salva a árvore
void SaveTreeNameUser(Context *ctx) {
	char filename[100];

	printf("Digite o nome do arquivo para salvar (ex: arvore.json): ");
	// Usa a função para ler a string 
	getnstr(filename, sizeof(filename));

	saveTreeToJSON(ctx, filename);
	printf("Arquivo '%s' salvo com sucesso!\n", filename);

	// Aguarda o usuário pressionar Enter para continuar
	printf("Pressione Enter para continuar...");
	getchar();
}
