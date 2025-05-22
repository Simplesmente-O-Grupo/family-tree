#include <stdio.h>
#include <stdlib.h>
#include "include/familyTree.h"

void printPerson(Person *person)
{
	printf("Nome: %s %s %s\n", person->firstName, person->middleName, person->lastName);
	printf("Descrição: %s\n", person->description);
	printf("Data de nascimento: %lld\n", person->dateOfBirth);
	if (!person->isAlive)
	{
		printf("Data de morte: %lld\n", person->dateOfDeath);
	}
}

void clearScreen(void)
{
#ifdef _WIN32
	system("cls");
#else
	printf("\e[1;1H\e[2J");
#endif /* WIN32 */
}
