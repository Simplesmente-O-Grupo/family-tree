#include <stdio.h>
#include <time.h>

#include "include/familyTree.h"
#include "include/context.h"
#include "include/ui_utils.h"
#include "include/input.h"

/* Formata uma timestamp para uma data com formato
 * dd/mm/aaaa
 */
static void formatDate(char *buffer, size_t bufflen, time_t timestamp);

/* Aqui eu crio uma função própria
 * porque eu preciso mostrar números
 * próximos aos campos editáveis
 */
static void printPerson(Person *person);

/* Tela de edição de pessoas.
 * Esta tela mostra todos os dados de uma pessoa e
 * permite editar certos campos
 */
void personEditor(Context *appContext) {
	clearScreen();
	Person *editing = appContext->editing;
	printf("+-----%s %s %s-----+\n", editing->firstName, editing->middleName, editing->lastName);
	printPerson(editing);
	printf("Campos sem número são apenas leitura.\n\n");
	int option = askInt("Digite um campo para editar, 0 para sair: ");

	switch(option) {
		case 0:
			appContext->screenState = TREE_MANAGER;
			break;
		case 1:
			printf("Digite o novo nome: ");
			getnstr(editing->firstName, MAX_NAME_LEN);
			break;
		case 2:
			printf("Digite o novo nome: ");
			getnstr(editing->middleName, MAX_NAME_LEN);
			break;
		case 3:
			printf("Digite o novo nome: ");
			getnstr(editing->lastName, MAX_NAME_LEN);
			break;
		case 4:
			printf("Digite a nova descrição: ");
			getnstr(editing->description, MAX_DESC_LEN);
			break;
		case 5:
			/* Se uma pessoa passar de viva para morta,
			 * é necessário definir uma data de morte
			 */
			if (editing->isAlive) {
				editing->dateOfDeath = askDate();
				editing->isAlive = false;
			} else {
				/* O mesmo não é verdadeiro para o contrário */
				editing->isAlive = true;
			}
			break;
		case 6:
			editing->dateOfBirth = askDate();
			break;
		case 7:
			editing->dateOfDeath = askDate();
			break;
	}
}

/* Formata uma timestamp para uma data com formato
 * dd/mm/aaaa
 */
static void formatDate(char *buffer, size_t bufflen, time_t timestamp) {
	struct tm *time = localtime(&timestamp);

	strftime(buffer, bufflen, "%d/%m/%Y", time);
}

/* Aqui eu crio uma função própria
 * porque eu preciso mostrar números
 * próximos aos campos editáveis
 */
static void printPerson(Person *person) {
	char dateBuf[25];
	int age;

	time_t endDate = person->isAlive ? time(NULL) : person->dateOfDeath;

	/* Retorna a diferença de segundos entre as duas datas */
	double agediff = difftime(endDate, person->dateOfBirth);
	/* Converte isto para anos */
	age = (int) (agediff / 60 / 60 / 24 / 365);

	printf("    ID: %d\n", person->id);
	printf("1 - Primeiro nome: %s\n", person->firstName);
	printf("2 - Nome do meio: %s\n", person->middleName);
	printf("3 - Último nome: %s\n", person->lastName);
	printf("4 - Descrição: %s\n", person->description);
	printf("5 - Morreu?: %s\n", !person->isAlive ? "Sim" : "Não");
	printf("    Idade: %d\n", age);

	formatDate(dateBuf, 25, person->dateOfBirth);
	printf("6 - Data de nascimento: %s\n", dateBuf);

	if (!person->isAlive) {
		formatDate(dateBuf, 25, person->dateOfDeath);
		printf("7 - Data de morte: %s\n", dateBuf);
	}
}
