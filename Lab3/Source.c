/*
3. Prethodnom zadatku dodati funkcije:
A. dinamicki dodaje novi element iza odredenog elementa,
B. dinamicki dodaje novi element ispred odredenog elementa,
C. sortira listu po prezimenima osoba,
D. upisuje listu u datoteku,
E. cita listu iz datoteke
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define EXIT_FAILURE (-1)

typedef struct _person* Position;

typedef struct _person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int dateOfBirth;
	Position next;
}Person;

Position createPerson();
int addToFront(Position);
int printList(Position);
int addToEnd(Position);
Position searchBySurname(Position);
Position searchPrevious(Pozicija);
int deletePerson(Position);
int insertAfterPerson(Position);
int insertBeforePerson(Position);
int sortList(Position);
int writeToFile(char*, Position);
int readFromFile(char*);
int deleteList(Position);
int menu(Person);

int main() {
	Person Head = { .name = {0},.surname = {0}, .dateOfBirth = 0, .next = NULL };

	menu(Head);
	
	return EXIT_SUCCESS;
}

Position createPerson() {
	Position newPerson = NULL;
	char namePerson[MAX_SIZE] = { 0 };
	char surnamePerson[MAX_SIZE] = { 0 };
	int dateBirthPerson = 0;

	newPerson = (Position)malloc(sizeof(Person));

	if (!newPerson) {							//PROVJERA MALLOCA!!
		printf("Error allocation!\n");
		return EXIT_FAILURE;
	}

	printf("Enter name: \n");
	scanf("%s", namePerson);

	printf("Enter surname: \n");
	scanf("%s", surnamePerson);

	printf("Enter date of birth: \n");
	scanf("%d", &dateBirthPerson);

	strcpy(newPerson->name, namePerson); //char* strcpy(char* destination, const char* source);
	strcpy(newPerson->surname, surnamePerson);
	newPerson->dateOfBirth = dateBirthPerson;

	return newPerson;
}

int addToFront(Position head) {
	Position newPerson = NULL;
	newPerson = createPerson();

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int printList(Position firstElement) {

	while (firstElement != NULL) {
		printf("%s \t %s \t %d\n", firstElement->name, firstElement->surname, firstElement->dateOfBirth);
		firstElement = firstElement->next;
	}
	return EXIT_SUCCESS;
}

int addToEnd(Position head) {
	Position newPerson = NULL;
	newPerson = createPerson();

	while (head->next != NULL)
		head = head->next;

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

Position searchBySurname(Position head) {

	char surnamePerson[MAX_SIZE];
	printf("Enter surname of the person you want to delete: \n");
	scanf("%s", surnamePerson);


	while (head != NULL && strcmp(head->surname, surnamePerson))
		head = head->next;

	if (head == NULL)
		printf("The last name you entered does not exist!\n");
	else
		printf("%s\t %s\t %d\n", head->name, head->surname, head->dateOfBirth);

	return head;
}

Position searchPrevious(Position head) {
	Position previousPerson = head;
	head = head->next;

	char surnamePerson[MAX_SIZE];
	printf("Enter surname of the person you want to delete:\n");
	scanf("%s", surnamePerson);

	while (head != NULL && strcmp(head->surname, surnamePerson)) { //string compare!!
		previousPerson = head;
		head = head->next;
	}

	if (head == NULL) 
		return head;

	else
		return previousPerson;
}

int deletePerson(Position head) {
	Position previous = NULL;
	previous = searchPrevious(head);

	if (previous != NULL) {
		head = previous->next;
		previous->next = head->next;
		free(head);
	}
	else
		printf("The last name you entered does not exist!\n");

	return EXIT_SUCCESS;
}

int insertAfterPerson(Position head) {
	
	char surnamePerson[MAX_SIZE];
	printf("Enter the last name of the person after whom you want to put a new person: \n");
	scanf("%s", surnamePerson);

	while (head != NULL && strcmp(head->surname, surnamePerson)) {
		head=head->next;
	}

	if (head != NULL) {
		Position temp = NULL;
		temp = createPerson();

		temp->next = head->next;
		head->next = temp;
	}
	else
		printf("The last name you entered does not exist!\n");
	
	return EXIT_SUCCESS;
}

int insertBeforePerson(Position head) {
	Position previous = head;
	head = head->next;

	char surnamePerson[MAX_SIZE];
	printf("Enter the last name of the person before whom you want to put a new person:\n");
	scanf("%s", surnamePerson);

	while (head != NULL && strcmp(head->surname, surnamePerson)) {
		previous = head;
		head = head->next;
	}

	if (head != NULL) {
		Position temp = NULL;
		temp = createPerson();

		temp->next = previous->next;
		previous->next = temp;
	}
	else
		printf("The last name you entered does not exist!\n");

	return EXIT_SUCCESS;
}

int sortList(Position head) {
	Position temp, end, person, previousPerson;

	end = NULL;

	while (head->next != end) {
		previousPerson = head;
		person = head->next;
		while (person->next != end) {
			if (strcmp(person->surname, person->next->surname) > 0) {
				temp = person->next;
				previousPerson->next = temp;
				person->next = temp->next;
				temp->next = person;

				person = temp;
			}
			previousPerson = person;
			person = person->next;
		}
		end = person;
	}
	return EXIT_SUCCESS;
}

int writeToFile(char* fileName, Position head) {
	FILE* fp = NULL;
	fp = fopen(fileName, "w");

	if (!fp) {
		printf("Error while opening the file!");
		return EXIT_FAILURE;
	}
	


	return EXIT_SUCCESS;
}

int readFromFile(char* fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	Person* newPerson = NULL;

	if (!fp) {
		printf("Error while opening the file!");
		return EXIT_FAILURE;
	}

	while (!feof(fp)) {
		scnaf("%s %s %d", newPerson);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}

int deleteList(Position head) {
	Position temp;

	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

int menu(Person head) {
	int choice = 0;

	do {
		printf("\n");
		printf("By entering a number, you select the action you want to do:\n 1) dynamically add a new element to the beginning of the list\n 2) print the list\n 3) dynamically add a new element to the end of the list\n 4) find the element in the list (by last name)\n 5) delete a certain element from the list\n");
		printf(" 6) dynamically add a new element after the specified element\n 7) dynamically add a new element in front of the specified element\n 8) sort the list by surnames of persons\n 9) write the list to the file\n 10) read the list from the file\n Enter 0 to exit from the menu\n");

		scanf("%d", &choice);

		switch (choice) {
		case 0:
			printf("You exited successfully from the menu!\n");
			break;
		case 1:
			addToFront(&head);
			break;
		case 2:
			printList(head.next);
			break;
		case 3:
			addToEnd(&head);
			break;
		case 4:
			searchBySurname(&head);
			break;
		case 5:
			deletePerson(&head);
			break;
		case 6:
			insertAfterPerson(&head);
			break;
		case 7:
			insertBeforePerson(&head);
			break;
		case 8:
			sortList(&head);
			break;
		/*case 9:
				writeToFile();
				break;
		case 10:
				readFromFile();
				break;*/
		default:
			printf("Number is not on menu! Please, try again!:\n");
		}
	}

	while (choice != 0);

	deleteList(&head); //Na kraju brisemo cijelu listu da ne zauzima memoriju!

	return EXIT_SUCCESS;
}
