/* 2. Definirati strukturu osoba (ime, prezime, godina roðenja) i napisati program koji:
A. dinamièki dodaje novi element na poèetak liste,
B. ispisuje listu,
C. dinamièki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)

typedef struct _person* Position;

typedef struct _person {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

Position createPerson();
int addToFront(Position);

int main() {
	Person head = { .ime = {0},.prezime = {0}, .birthYear=0, .next=NULL };


	return EXIT_SUCCESS;

}
Position createPerson() {
	Position newPerson = NULL;
	char ime[MAX_SIZE] = { 0 };
	char prezime[MAX_SIZE] = { 0 };
	int birthYear = 0;

	newPerson = (Position)malloc(sizeof(Person));

	//Provjera

	printf("Unesi ime\n");
	scanf("%s", ime);

	// -||-

	strcpy(newPerson->ime, ime); //ime je pokazivac za ime[max size]

	// -||-

	return newPerson;

}

int addToFront(Position head) {
	Position newPerson = NULL;
	newPerson = createPerson();

	if (newPerson) {
		newPerson->next = head->next;
		head->next = newPerson;
	}

}