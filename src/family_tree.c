/* familyTree.c */
#include "include/familyTree.h"
#include "include/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

// Verifica se um ID já existe na árvore
bool checkIdExists(Person *root, int id)
{
	if (root == NULL)
		return false;

	if (root->id == id)
		return true;

	return checkIdExists(root->children, id) || checkIdExists(root->nextSibling, id);
}

// Cria uma nova pessoa preenchendo via diálogo (implementação simplificada)
Person *createPersonDialog(void)
{
	Person *person = malloc(sizeof(Person));
	if (!person)
	{
		fprintf(stderr, "Não foi possível alocar memória para pessoa.\n");
		return NULL;
	}

	struct tm time = {0};
	int id;

	do
	{
		id = -1;
		printf("\nID (deve ser único): ");
		scanf("%d", &id);
		while (getchar() != '\n')
			; // limpa buffer

		// TODO: passar a raiz global da árvore para checkIdExists
		// Exemplo: if (checkIdExists(rootGlobal, id)) { printf("ID já existe\n"); }
	} while (id < 0 /* || checkIdExists(rootGlobal, id) */);

	person->id = id;

	printf("Nome: ");
	fgets(person->firstName, MAX_NAME_LEN, stdin);
	person->firstName[strcspn(person->firstName, "\n")] = 0;

	printf("Nome do meio (pode ser vazio): ");
	fgets(person->middleName, MAX_NAME_LEN, stdin);
	person->middleName[strcspn(person->middleName, "\n")] = 0;

	printf("Sobrenome: ");
	fgets(person->lastName, MAX_NAME_LEN, stdin);
	person->lastName[strcspn(person->lastName, "\n")] = 0;

	printf("Descrição: ");
	fgets(person->description, MAX_DESC_LEN, stdin);
	person->description[strcspn(person->description, "\n")] = 0;

	printf("Ano de nascimento: ");
	scanf("%d", &time.tm_year);
	time.tm_year -= 1900;
	printf("Mês de nascimento: ");
	scanf("%d", &time.tm_mon);
	time.tm_mon -= 1;
	printf("Dia de nascimento: ");
	scanf("%d", &time.tm_mday);
	while (getchar() != '\n')
		; // limpa buffer

	person->dateOfBirth = mktime(&time);

	int tmp;
	printf("Esta pessoa morreu? [1=Sim / 0=Não]: ");
	scanf("%d", &tmp);
	while (getchar() != '\n')
		;

	person->isAlive = (tmp == 0);

	if (person->isAlive)
	{
		person->dateOfDeath = -1;
	}
	else
	{
		struct tm timeDeath = {0};
		printf("Ano da morte: ");
		scanf("%d", &timeDeath.tm_year);
		timeDeath.tm_year -= 1900;
		printf("Mês da morte: ");
		scanf("%d", &timeDeath.tm_mon);
		timeDeath.tm_mon -= 1;
		printf("Dia da morte: ");
		scanf("%d", &timeDeath.tm_mday);
		while (getchar() != '\n')
			;

		person->dateOfDeath = mktime(&timeDeath);
	}

	person->parent = NULL;
	person->children = NULL;
	person->nextSibling = NULL;
	person->prevSibling = NULL;

	return person;
}

// Adiciona filho na lista de filhos do pai (inserção no início)
void addChild(Person *parent, Person *child)
{
	if (!parent || !child)
		return;

	child->parent = parent;
	child->prevSibling = NULL;

	if (parent->children)
	{
		parent->children->prevSibling = child;
	}
	child->nextSibling = parent->children;
	parent->children = child;
}

// Remove uma pessoa (e recursivamente seus descendentes)
void removePerson(Person *person)
{
	if (person == NULL)
		return;

	if (person->parent && person->parent->children == person)
		person->parent->children = person->nextSibling;

	if (person->prevSibling)
		person->prevSibling->nextSibling = person->nextSibling;

	if (person->nextSibling)
		person->nextSibling->prevSibling = person->prevSibling;

	Person *child = person->children;
	while (child)
	{
		Person *nextChild = child->nextSibling;
		removePerson(child);
		child = nextChild;
	}

	free(person);
}

// Imprime árvore recursivamente
static void _printTree(Person *root, int level)
{
	if (root == NULL)
		return;

	for (int i = 0; i < level; i++)
		putchar('\t');

	printf("ID: %d | %s %s %s\n", root->id,
		   root->firstName,
		   root->middleName[0] ? root->middleName : "",
		   root->lastName);

	_printTree(root->children, level + 1);
	_printTree(root->nextSibling, level);
}

void printTree(Person *root)
{
	_printTree(root, 0);
}

// Cria tabela hash com tamanho dado
HashTable *createHashTable(int size)
{
	HashTable *table = malloc(sizeof(HashTable));
	if (!table)
	{
		fprintf(stderr, "Erro: Não foi possível alocar tabela hash.\n");
		return NULL;
	}

	table->size = size;
	table->buckets = calloc(size, sizeof(HashNode *));
	if (!table->buckets)
	{
		fprintf(stderr, "Erro: Não foi possível alocar baldes.\n");
		free(table);
		return NULL;
	}
	return table;
}

// Função hash para string (case-sensitive)
unsigned int hashString(const char *str, int tableSize)
{
	unsigned int hash = 0;
	for (int i = 0; str[i]; i++)
	{
		hash = (hash * 31 + (unsigned char)str[i]) % tableSize;
	}
	return hash;
}

// Insere na tabela hash, evitando duplicatas (comparação case-sensitive)
void insertIntoHashTable(HashTable *table, const char *name, Person *person)
{
	if (!table || !person || !name || !name[0])
		return;

	unsigned int index = hashString(name, table->size);

	for (HashNode *curr = table->buckets[index]; curr; curr = curr->next)
	{
		if (strcmp(curr->name, name) == 0 && curr->person == person)
			return;
	}

	HashNode *newNode = malloc(sizeof(HashNode));
	if (!newNode)
	{
		fprintf(stderr, "Erro: Falha ao alocar nó.\n");
		return;
	}

	strncpy(newNode->name, name, MAX_NAME_LEN - 1);
	newNode->name[MAX_NAME_LEN - 1] = '\0';
	newNode->person = person;
	newNode->next = table->buckets[index];
	table->buckets[index] = newNode;
}

// Indexa os nomes da pessoa na tabela hash
void indexPersonInHashTable(HashTable *table, Person *person)
{
	if (!table || !person)
		return;

	insertIntoHashTable(table, person->firstName, person);
	if (person->middleName[0])
		insertIntoHashTable(table, person->middleName, person);
	insertIntoHashTable(table, person->lastName, person);
}

// Indexa toda a árvore na tabela hash
void indexFamilyTreeInHashTable(Person *root, HashTable *table)
{
	if (!root || !table)
		return;

	indexPersonInHashTable(table, root);
	indexFamilyTreeInHashTable(root->children, table);
	indexFamilyTreeInHashTable(root->nextSibling, table);
}

// Busca na tabela hash, retorna vetor de Person* (busca substring case-sensitive)
Person **searchInHashTable(HashTable *table, const char *searchTerm)
{
	if (!table || !searchTerm || !searchTerm[0])
		return NULL;

	Person **results = malloc(sizeof(Person *) * 101);
	if (!results)
	{
		fprintf(stderr, "Erro: Falha ao alocar resultados.\n");
		return NULL;
	}

	for (int i = 0; i <= 100; i++)
		results[i] = NULL;

	int resultCount = 0;

	for (int i = 0; i < table->size; i++)
	{
		for (HashNode *current = table->buckets[i]; current && resultCount < 100; current = current->next)
		{
			if (strstr(current->name, searchTerm))
			{
				bool alreadyAdded = false;
				for (int j = 0; j < resultCount; j++)
				{
					if (results[j] == current->person)
					{
						alreadyAdded = true;
						break;
					}
				}

				if (!alreadyAdded)
					results[resultCount++] = current->person;
			}
		}
	}

	if (resultCount == 0)
	{
		free(results);
		return NULL;
	}

	return results;
}

// Libera toda a tabela hash
void freeHashTable(HashTable *table)
{
	if (!table)
		return;

	for (int i = 0; i < table->size; i++)
	{
		HashNode *current = table->buckets[i];
		while (current)
		{
			HashNode *next = current->next;
			free(current);
			current = next;
		}
	}
	free(table->buckets);
	free(table);
}

// Conta pessoas na árvore
void countPersonsInTree(Person *root, int *count)
{
	if (!root)
		return;

	(*count)++;
	countPersonsInTree(root->children, count);
	countPersonsInTree(root->nextSibling, count);
}

// Busca por nome usando tabela hash (case-sensitive)
Person **searchPersonByName(Person *root, const char *name)
{
	if (!root || !name)
		return NULL;

	HashTable *table = createHashTable(1000);
	if (!table)
		return NULL;

	indexFamilyTreeInHashTable(root, table);
	Person **results = searchInHashTable(table, name);
	freeHashTable(table);

	return results;
}

// Busca pessoa por ID (busca recursiva)
Person *findPersonById(Person *root, int id)
{
	if (!root)
		return NULL;

	if (root->id == id)
		return root;

	Person *found = findPersonById(root->children, id);
	if (found)
		return found;

	return findPersonById(root->nextSibling, id);
}

// Exibe detalhes da pessoa formatados
void displayPersonDetails(Person *person)
{
	if (!person)
		return;

	printf("ID: %d\n", person->id);
	printf("Nome completo: %s %s %s\n",
		   person->firstName,
		   person->middleName[0] ? person->middleName : "",
		   person->lastName);
	printf("Descrição: %s\n", person->description);

	char buffer[64];
	struct tm *tm_info;

	tm_info = localtime(&person->dateOfBirth);
	strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
	printf("Data de nascimento: %s\n", buffer);

	if (person->isAlive)
		printf("Status: Vivo\n");
	else
	{
		tm_info = localtime(&person->dateOfDeath);
		strftime(buffer, sizeof(buffer), "%d/%m/%Y", tm_info);
		printf("Data de falecimento: %s\n", buffer);
	}
}

/**
 * Realiza uma busca interativa por pessoas na árvore
 * @param root Raiz da árvore genealógica
 * @return Vetor de ponteiros para pessoas encontradas (deve ser liberado pelo caller)
 */
Person **searchPersonDialog(Person *root)
{
	if (!root)
	{
		printf("\nÁrvore vazia! Nenhuma busca pode ser realizada.\n");
		return NULL;
	}

	char searchTerm[MAX_NAME_LEN];
	printf("\nDigite o nome para buscar (ou parte do nome): ");
	getnstr(searchTerm, MAX_NAME_LEN);

	// Busca usando a tabela hash (implementação existente)
	Person **results = searchPersonByName(root, searchTerm);

	if (!results)
	{
		printf("\nNenhuma pessoa encontrada com o termo: '%s'\n", searchTerm);
		return NULL;
	}

	// Exibe resultados
	printf("\n=== RESULTADOS DA BUSCA ===\n");
	for (int i = 0; results[i] != NULL; i++)
	{
		printf("\n[Resultado %d]\n", i + 1);
		displayPersonDetails(results[i]);
		printf("----------------------------");
	}

	// Menu de seleção
	int choice;
	do
	{
		printf("\n\nDigite o número do resultado para selecionar (0 para cancelar): ");
		choice = askInt("");
	} while (choice < 0 || choice > 100); // Limite arbitrário seguro

	if (choice == 0)
	{
		free(results);
		return NULL;
	}

	// Retorna apenas a pessoa selecionada (em um array para manter a interface consistente)
	Person **selected = malloc(2 * sizeof(Person *));
	selected[0] = results[choice - 1];
	selected[1] = NULL;

	free(results);
	return selected;
}

int countPeople(Person *root) {
	/* Caso base: Pessoa não existe */
	if (root == NULL) return 0;

	/* Caso geral: Pessoa existe */
	int tmp = countPeople(root->nextSibling);
	return 1 + countPeople(root->children) + tmp;
}

Person *personById(Person *root, int id) {
	/* Caso base: Pessoa não existe */
	if (root == NULL) return NULL;
	/* Caso base: Pessoa foi encontrada */
	if (root->id == id) return root;

	/* Busque pelos irmãos */
	Person *siblings = personById(root->nextSibling, id);
	if (siblings != NULL) return root;

	/* Busque pelos filhos */
	return personById(root->children, id);
}
