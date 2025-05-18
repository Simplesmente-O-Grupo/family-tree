/* familyTree.c */
#include "include/familyTree.h"
#include "include/input.h"
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

/**
 * Verifica se já existe uma pessoa com o ID especificado na árvore
 * @param root Raiz da árvore
 * @param id ID a verificar
 * @return true se o ID já existe, false caso contrário
 */
bool checkIdExists(Person *root, int id)
{
	if (root == NULL)
	{
		return false;
	}

	// Verifica o nó atual
	if (root->id == id)
	{
		return true;
	}

	// Verifica os filhos
	if (checkIdExists(root->children, id))
	{
		return true;
	}

	// Verifica os irmãos
	if (checkIdExists(root->nextSibling, id))
	{
		return true;
	}

	return false;
}

Person *createPersonDialog(void)
{
	Person *person = malloc(sizeof(Person));
	if (person == NULL)
	{
		fprintf(stderr, "Não foi possível alocar memória para pessoa.\n");
		return NULL;
	}

	struct tm time = {0};

	/* Preencher dados */
	int id;
	do
	{
		id = askInt("\nID (deve ser único): ");

		/* Limpar o buffer */
		while (getchar() != '\n' && !feof(stdin))
			;

		/* Verificar se o ID já existe (função a ser implementada) */
		/* Em uma aplicação real, você teria uma raiz global para verificar */
		/* Por ora, apenas simularemos a verificação */
		printf("Verificando ID...\n");

		/* Simula a verificação de IDs - em uma implementação real,
		   você passaria a raiz da árvore aqui */
		/* if (checkIdExists(rootGlobal, id)) {
			printf("Erro: ID %d já existe. Por favor, escolha outro ID.\n", id);
		} */
	} while (0); /* Substitua por: } while (checkIdExists(rootGlobal, id)); */

	person->id = id;

	printf("Nome: ");
	getnstr(person->firstName, MAX_NAME_LEN);

	printf("Nome do meio (pode ser vazio): ");
	getnstr(person->middleName, MAX_NAME_LEN);

	printf("Sobrenome: ");
	getnstr(person->lastName, MAX_NAME_LEN);

	printf("Descrição: ");
	getnstr(person->description, MAX_DESC_LEN);

	time.tm_year = askInt("Ano de nascimento: ") - 1900;
	time.tm_mon = askInt("Digite o mês de nascimento: ") - 1;
	time.tm_mday = askInt("Digite o dia de nascimento: ");

	person->dateOfBirth = mktime(&time);

	int tmp = askInt("Esta pessoa morreu? [1/0] ");
	person->isAlive = (tmp == 0);
	if (person->isAlive)
	{
		person->dateOfDeath = -1;
	}
	else
	{
		struct tm timeDeath = {0};
		timeDeath.tm_year = askInt("Ano da morte: ") - 1900;
		timeDeath.tm_mon = askInt("Digite o mês da morte: ") - 1;
		timeDeath.tm_mday = askInt("Digite o dia da morte: ");
		person->dateOfDeath = mktime(&timeDeath);
	}

	person->parent = NULL;
	person->children = NULL;
	person->nextSibling = NULL;
	person->prevSibling = NULL;

	return person;
}

void addChild(Person *parent, Person *child)
{
	if (!parent || !child)
		return;

	child->parent = parent;
	child->prevSibling = NULL; // Novo nó sempre no início

	if (parent->children)
	{
		parent->children->prevSibling = child;
	}
	child->nextSibling = parent->children;
	parent->children = child;
}

void removePerson(Person *person)
{
	/* Caso base: A pessoa não existe */
	if (person == NULL)
		return;

	/* Se esta pessoa tem um pai e é o primeiro filho */
	if (person->parent != NULL && person->parent->children == person)
	{
		person->parent->children = person->nextSibling;
	}

	/* Ajustar a lista de irmãos */
	if (person->prevSibling != NULL)
	{
		person->prevSibling->nextSibling = person->nextSibling;
	}
	if (person->nextSibling != NULL)
	{
		person->nextSibling->prevSibling = person->prevSibling;
	}

	/* Remover recursivamente todos os filhos */
	Person *child = person->children;
	while (child != NULL)
	{
		Person *nextChild = child->nextSibling;
		removePerson(child);
		child = nextChild;
	}

	/* Remover a pessoa */
	free(person);
}

static void _printTree(Person *root, int level)
{
	/* Caso base: a raíz não existe */
	if (root == NULL)
		return;

	/* Caso geral: imprimir com base no nível */
	printf("ID: %d | ", root->id);
	for (int i = 0; i < level; i++)
	{
		putchar('\t');
	}
	printf("%s %s %s\n", root->firstName,
		   root->middleName[0] != '\0' ? root->middleName : "",
		   root->lastName);

	/* Imprimir os filhos */
	_printTree(root->children, level + 1);

	/* Imprimir os irmãos */
	_printTree(root->nextSibling, level);
}

void printTree(Person *root)
{
	_printTree(root, 0);
}

/* Search person informationd passing his name as parameter  */
/**
 * Cria uma nova tabela hash com o tamanho especificado
 * @param size Tamanho da tabela (número de "baldes")
 * @return Ponteiro para a tabela hash criada ou NULL se falhar
 */

HashTable *createHashTable(int size)
{
	HashTable *table = (HashTable *)malloc(sizeof(HashTable));
	if (table == NULL)
	{
		fprintf(stderr, "Error: Not possible memory allocation.\n");
		return NULL;
	}

	// Define o tamanho da tabela
	table->size = size;

	// Aloca memória para os baldes (array de ponteiros)
	// calloc inicializa todos os ponteiros como NULL
	table->buckets = (HashNode **)calloc(size, sizeof(HashNode *));
	if (table->buckets == NULL)
	{
		fprintf(stderr, "Error: Not possible memory allocation for the buckets.\n");
		free(table);
		return NULL;
	}
	return table;
}

/**
 * Calcula o valor hash de uma string
 * @param str String para calcular o hash
 * @param tableSize Tamanho da tabela hash
 * @return Índice na tabela hash
 * A função de hash converte uma string (nome) em um número que representa a posição na tabela:
 */

unsigned int hashString(const char *str, int tableSize)
{
	unsigned int hash = 0;
	// Para cada caractere na string
	for (int i = 0; str[i]; i++)
	{
		// Converte para minúsculo para busca case-insensitive
		char c = tolower(str[i]);

		// Algoritmo simples: multiplicar hash atual por 31 e somar ao caractere
		hash = (hash * 31 + c) % tableSize;
	}
	return hash;
}

/**
 * Insere uma pessoa na tabela hash usando um nome específico
 * @param table Tabela hash onde inserir
 * @param name Nome a ser usado como chave
 * @param person Ponteiro para a pessoa
 */

/**
 * Insere uma pessoa na tabela hash usando um nome específico
 * @param table Tabela hash onde inserir
 * @param name Nome a ser usado como chave
 * @param person Ponteiro para a pessoa
 */

void insertIntoHashTable(HashTable *table, const char *name, Person *person)
{
	// Se a tabela ou a pessoa ou o nome são nulos, retornar
	if (table == NULL || person == NULL || name == NULL || name[0] == '\0')
	{
		return;
	}

	// Calcula o índice usando a função de hash
	unsigned int index = hashString(name, table->size);

	// Verifica se já existe um nó com este mesmo nome e pessoa
	HashNode *current = table->buckets[index];
	while (current != NULL)
	{
		if (strcasecmp(current->name, name) == 0 && current->person == person)
		{
			// Já existe, não precisa inserir novamente
			return;
		}
		current = current->next;
	}

	// Cria um novo nó
	HashNode *newNode = (HashNode *)malloc(sizeof(HashNode));
	if (newNode == NULL)
	{
		fprintf(stderr, "Erro: Não foi possível alocar memória para nó na tabela hash.\n");
		return;
	}

	// Copia o nome para o nó
	strncpy(newNode->name, name, MAX_NAME_LEN - 1);
	newNode->name[MAX_NAME_LEN - 1] = '\0'; // Garante que termina com '\0'

	// Define o ponteiro para a pessoa
	newNode->person = person;

	// Insere o nó no início da lista no índice calculado
	newNode->next = table->buckets[index];
	table->buckets[index] = newNode;
}

/**
 * Insere todos os nomes de uma pessoa na tabela hash
 * @param table Tabela hash
 * @param person Pessoa a ser inserida
 */
void indexPersonInHashTable(HashTable *table, Person *person)
{
	if (table == NULL || person == NULL)
	{
		return;
	}

	// Insere todos os nomes da pessoa na tabela
	insertIntoHashTable(table, person->firstName, person);

	if (person->middleName[0] != '\0')
	{
		insertIntoHashTable(table, person->middleName, person);
	}

	insertIntoHashTable(table, person->lastName, person);
}

/**
 * Percorre a árvore familiar e indexa todas as pessoas na tabela hash
 * @param root Raiz da árvore familiar
 * @param table Tabela hash
 */
void indexFamilyTreeInHashTable(Person *root, HashTable *table)
{
	if (root == NULL || table == NULL)
	{
		return;
	}

	// Indexa a pessoa atual
	indexPersonInHashTable(table, root);

	// Indexa os filhos
	indexFamilyTreeInHashTable(root->children, table);

	// Indexa os irmãos
	indexFamilyTreeInHashTable(root->nextSibling, table);
}

/**
 * Busca pessoas na tabela hash pelo nome
 * @param table Tabela hash
 * @param searchTerm Termo a ser buscado
 * @return Array de ponteiros para as pessoas encontradas (último elemento é NULL)
 */
Person **searchInHashTable(HashTable *table, const char *searchTerm)
{
	if (table == NULL || searchTerm == NULL || searchTerm[0] == '\0')
	{
		return NULL;
	}

	// Aloca memória para o array de resultados (máximo de 100 resultados + NULL)
	Person **results = (Person **)malloc(sizeof(Person *) * 101);
	if (results == NULL)
	{
		fprintf(stderr, "Erro: Não foi possível alocar memória para resultados.\n");
		return NULL;
	}

	// Inicializa todos os resultados como NULL
	for (int i = 0; i <= 100; i++)
	{
		results[i] = NULL;
	}

	int resultCount = 0;

	// Converte o termo de busca para minúsculas para comparação case-insensitive
	char lowerSearch[MAX_NAME_LEN];
	for (int i = 0; searchTerm[i] && i < MAX_NAME_LEN - 1; i++)
	{
		lowerSearch[i] = tolower(searchTerm[i]);
	}
	lowerSearch[strlen(searchTerm)] = '\0';

	Person **results = searchInHashTable(table, searchTerm);
	if (!results)
	{
		freeHashTable(table);
		return NULL;
	}

	// Percorre todos os baldes da tabela hash
	for (int i = 0; i < table->size; i++)
	{
		HashNode *current = table->buckets[i];

		// Percorre todos os nós neste balde
		while (current != NULL && resultCount < 100)
		{
			// Copia o nome do nó para converter para minúsculas
			char lowerName[MAX_NAME_LEN];
			strncpy(lowerName, current->name, MAX_NAME_LEN - 1);
			lowerName[MAX_NAME_LEN - 1] = '\0';

			for (int j = 0; lowerName[j]; j++)
			{
				lowerName[j] = tolower(lowerName[j]);
			}

			// Verifica se o termo de busca está contido no nome
			if (strstr(lowerName, lowerSearch) != NULL)
			{
				// Verifica se esta pessoa já está nos resultados
				bool alreadyAdded = false;
				for (int j = 0; j < resultCount; j++)
				{
					if (results[j] == current->person)
					{
						alreadyAdded = true;
						break;
					}
				}

				// Se não estiver nos resultados ainda, adiciona
				if (!alreadyAdded)
				{
					results[resultCount++] = current->person;
				}
			}

			current = current->next;
		}
	}

	// Se não encontrou nenhum resultado, libera memória e retorna NULL
	if (resultCount == 0)
	{
		free(results);
		return NULL;
	}

	return results;
}

/**
 * Libera a memória alocada para a tabela hash
 * @param table Tabela hash a ser liberada
 */
void freeHashTable(HashTable *table)
{
	if (table == NULL)
	{
		return;
	}

	// Percorre todos os baldes
	for (int i = 0; i < table->size; i++)
	{
		HashNode *current = table->buckets[i];

		// Libera todos os nós neste balde
		while (current != NULL)
		{
			HashNode *next = current->next;
			free(current);
			current = next;
		}
	}

	// Libera o array de baldes
	free(table->buckets);

	// Libera a estrutura da tabela
	free(table);
}

/**
 * Busca pessoas pelo nome na árvore familiar usando tabela hash
 * @param root Raiz da árvore familiar
 * @param searchTerm Termo a ser buscado
 * @return Array de ponteiros para as pessoas encontradas
 */
Person **searchPersonByName(Person *root, const char *searchTerm)
{
	if (root == NULL || searchTerm == NULL || searchTerm[0] == '\0')
	{
		return NULL;
	}

	// Contar o número de pessoas na árvore para dimensionar a tabela hash
	int personCount = 0;
	countPersonsInTree(root, &personCount);

	// Criar uma tabela hash com tamanho proporcional ao número de pessoas
	// Um bom tamanho é geralmente 2x o número de elementos esperados
	int tableSize = personCount * 2;
	if (tableSize < 10)
		tableSize = 10; // Tamanho mínimo

	HashTable *table = createHashTable(tableSize);
	if (table == NULL)
	{
		return NULL;
	}

	// Indexar toda a árvore familiar na tabela hash
	indexFamilyTreeInHashTable(root, table);

	// Buscar pessoas usando a tabela hash
	Person **results = searchInHashTable(table, searchTerm);

	// Liberar a memória da tabela hash
	freeHashTable(table);

	return results;
}

/**
 * Função auxiliar para contar o número de pessoas na árvore
 * @param root Nó atual
 * @param count Ponteiro para contador
 */
void countPersonsInTree(Person *root, int *count)
{
	if (root == NULL)
	{
		return;
	}

	// Incrementa o contador para esta pessoa
	(*count)++;

	// Conta os filhos
	countPersonsInTree(root->children, count);

	// Conta os irmãos
	countPersonsInTree(root->nextSibling, count);
}

/**
 * Interface para buscar pessoas pelo nome
 * @param root Raiz da árvore familiar
 */
void searchPersonDialog(Person *root)
{
	if (root == NULL)
	{
		printf("Árvore familiar vazia.\n");
		return;
	}

	// Solicitar o termo de busca
	char searchTerm[MAX_NAME_LEN];
	printf("\nDigite o nome, nome do meio ou sobrenome para buscar: ");
	scanf("%s", searchTerm);

	// Limpar o buffer
	while (getchar() != '\n' && !feof(stdin))
		;

	// Buscar pessoas
	Person **results = searchPersonByName(root, searchTerm);

	if (results == NULL)
	{
		printf("Nenhuma pessoa encontrada com o termo '%s'.\n", searchTerm);
		return;
	}

	// Contar e mostrar resultados
	int count = 0;
	while (results[count] != NULL)
	{
		count++;
	}

	printf("\nForam encontradas %d pessoa(s) com o termo '%s':\n", count, searchTerm);

	// Exibir a lista de pessoas encontradas
	for (int i = 0; i < count; i++)
	{
		printf("%d. %s %s %s (ID: %d)\n",
			   i + 1,
			   results[i]->firstName,
			   results[i]->middleName[0] != '\0' ? results[i]->middleName : "",
			   results[i]->lastName,
			   results[i]->id);
	}

	// Perguntar se deseja ver detalhes de alguma pessoa
	if (count > 0)
	{
		int choice;
		printf("\nSelecione um número para ver detalhes (0 para cancelar): ");
		scanf("%d", &choice);

		// Limpar buffer
		while (getchar() != '\n' && !feof(stdin))
			;

		if (choice > 0 && choice <= count)
		{
			displayPersonDetails(results[choice - 1]);
		}
	}

	// Liberar memória
	free(results);
}

/**
 * Exibe detalhes de uma pessoa
 * @param person Pessoa a ser exibida
 */
void displayPersonDetails(Person *person)
{
	if (person == NULL)
	{
		printf("Pessoa não encontrada.\n");
		return;
	}

	printf("\n===== DETALHES DA PESSOA =====\n");
	printf("ID: %d\n", person->id);
	printf("Nome completo: %s %s %s\n",
		   person->firstName,
		   person->middleName[0] != '\0' ? person->middleName : "",
		   person->lastName);

	// Exibir data de nascimento
	char birthDate[20];
	struct tm *birthTime = localtime(&person->dateOfBirth);
	strftime(birthDate, sizeof(birthDate), "%d/%m/%Y", birthTime);
	printf("Data de nascimento: %s\n", birthDate);

	// Exibir data de morte se aplicável
	if (!person->isAlive)
	{
		char deathDate[20];
		struct tm *deathTime = localtime(&person->dateOfDeath);
		strftime(deathDate, sizeof(deathDate), "%d/%m/%Y", deathTime);
		printf("Data de falecimento: %s\n", deathDate);
	}

	printf("Status: %s\n", person->isAlive ? "Vivo" : "Falecido");
	printf("Descrição: %s\n", person->description);

	// Exibir pai/mãe
	if (person->parent != NULL)
	{
		printf("Pai/Mãe: %s %s %s\n",
			   person->parent->firstName,
			   person->parent->middleName[0] != '\0' ? person->parent->middleName : "",
			   person->parent->lastName);
	}
	else
	{
		printf("Pai/Mãe: Não registrado\n");
	}

	// Contar e listar irmãos
	int siblingCount = 0;
	Person *sibling = person->parent ? person->parent->children : NULL;
	printf("Irmãos: ");

	while (sibling != NULL)
	{
		if (sibling != person)
		{
			siblingCount++;
			printf("%s%s", sibling->firstName,
				   sibling->nextSibling != NULL ? ", " : "");
		}
		sibling = sibling->nextSibling;
	}

	if (siblingCount == 0)
	{
		printf("Nenhum");
	}
	printf("\n");

	// Contar e listar filhos
	int childCount = 0;
	Person *child = person->children;
	printf("Filhos: ");

	while (child != NULL)
	{
		childCount++;
		printf("%s%s", child->firstName,
			   child->nextSibling != NULL ? ", " : "");
		child = child->nextSibling;
	}

	if (childCount == 0)
	{
		printf("Nenhum");
	}
	printf("\n");

	printf("==============================\n");
}

bool checkIdExists(Person *root, int id)
{
	if (!root)
		return false;
	if (root->id == id)
		return true;
	return checkIdExists(root->children, id) || checkIdExists(root->nextSibling, id);
}