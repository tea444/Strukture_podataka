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

typedef struct _osoba* Pozicija;

typedef struct _osoba {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int godinaRodenja;
	Pozicija next;
}Osoba;

Pozicija stvoriOsobu();
int UnosP(Pozicija);
int Ispis(Pozicija);
int UnosK(Pozicija);
Pozicija Trazi(Pozicija);
Pozicija TraziPrev(Pozicija);
int Brisi(Pozicija);
int UnosIza(Pozicija);
int UnosIspred(Pozicija);
int SortiraniUnos(Pozicija);

int main() {
	Osoba head = { .ime = {0},.prezime = {0}, .godinaRodenja = 0, .next = NULL };

	int odabir = 0;

	do {
		printf("Unosom broja odabires radnju koju zelis napraviti:\n 1) dinamicki dodaje novi element na pocetak liste\n 2) ispisuje listu\n 3) dinamicki dodaje novi element na kraj liste\n 4) pronalazi element u listi(po prezimenu)\n 5) brise odredeni element iz liste\n");
		printf(" 6) dinamicki dodaje novi element iza odredenog elementa\n 7) dinamicki dodaje novi element ispred odredenog elementa\n 8) sortira listu po prezimenima osoba\n 9) upisuje listu u datoteku\n 10) cita listu iz datoteke\n  Unosom 0 izlazite iz menija\n");

		scanf("%d", &odabir);

		switch (odabir) {
		case 1:
			UnosP(&head);
			break;
		case 2:
			Ispis(head.next);
			break;
		case 3:
			UnosK(&head);
			break;
		case 4:
			Trazi(&head);
			break;
		case 5:
			Brisi(&head);
			break;
		case 6:
			UnosIza(&head);
			break;
		case 7:
			UnosIspred(&head);
			break;
		case 8:
			SortiraniUnos(&head);
			break;
		/*case 9:
			Brisi(&head);
			break;
		case 10:
			Brisi(&head);
			break;*/
		default:
			printf("Unijeli ste neispravan broj:\n"); //Kad unesem nulu ne zelim da se ovo ispise??!
		}
	}

	while (odabir != 0);

	return EXIT_SUCCESS;
}

Pozicija stvoriOsobu() {
	Pozicija novaOsoba = NULL;
	char imeOs[MAX_SIZE] = { 0 };
	char prezimeOs[MAX_SIZE] = { 0 };
	int godinaRodenjaOs = 0;

	novaOsoba = (Pozicija)malloc(sizeof(Osoba));

	if (!novaOsoba) {							//PROVJERA MALLOCA!!
		printf("Gre�ka u alociranju!\n");
		return NULL;
	}

	printf("Unesi ime: \n");
	scanf("%s", imeOs);

	printf("Unesi prezime: \n");
	scanf("%s", prezimeOs);

	printf("Unesi godinu rodenja: \n");
	scanf("%d", &godinaRodenjaOs);

	strcpy(novaOsoba->ime, imeOs); //char* strcpy(char* destination, const char* source);
	strcpy(novaOsoba->prezime, prezimeOs);
	novaOsoba->godinaRodenja = godinaRodenjaOs;

	return novaOsoba;
}

int UnosP(Pozicija P) {
	Pozicija novaOs = NULL;
	novaOs = stvoriOsobu();

	novaOs->next = P->next;
	P->next = novaOs;

	return EXIT_SUCCESS;
}

int Ispis(Pozicija P) {

	while (P != NULL) {
		printf("%s \t %s \t %d\n", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}
	return EXIT_SUCCESS;
}

int UnosK(Pozicija P) {
	Pozicija novaOs = NULL;
	novaOs = stvoriOsobu();

	while (P->next != NULL)
		P = P->next;

	novaOs->next = P->next;
	P->next = novaOs;

	return EXIT_SUCCESS;
}

Pozicija Trazi(Pozicija P) {

	char prez[MAX_SIZE];
	printf("Unesi prezime osobe koju zelis pronaci: \n");
	scanf("%s", prez);


	while (P != NULL && strcmp(P->prezime, prez))
		P = P->next;

	if (P == NULL)
		printf("Ne postoji osoba sa trazenim prezimenom!\n");
	else
		printf("%s\t %s\t %d\n", P->ime, P->prezime, P->godinaRodenja);

	return P;
}

Pozicija TraziPrev(Pozicija P) {
	Pozicija prev = P;
	P = P->next;

	char prez[MAX_SIZE];
	printf("Unesi prezime osobe koju zelis izbrisati: \n");
	scanf("%s", prez);

	while (P != NULL && strcmp(P->prezime, prez)) { //string compare!!
		prev = P;
		P = P->next;
	}

	if (P == NULL) 
		return P;

	else
		return prev;
}

int Brisi(Pozicija P) {
	Pozicija prev = NULL;
	prev = TraziPrev(P);

	if (prev != NULL) {
		P = prev->next;
		prev->next = P->next;
		free(P);
	}
	else
		printf("Ne postoji osoba unesenog prezimena!\n");

	return EXIT_SUCCESS;
}

int UnosIza(Pozicija P) {
	
	char prez[MAX_SIZE];
	printf("Unesi prezime osobe iza koje zelis postaviti novu osobu: \n");
	scanf("%s", prez);

	while (P != NULL && strcmp(P->prezime, prez)) {
		P=P->next;
	}

	if (P != NULL) {
		Pozicija q = NULL;
		q = stvoriOsobu();

		q->next = P->next;
		P->next = q;
	}
	else
		printf("Prezime koje ste unijeli ne postoji!\n");
	
	return EXIT_SUCCESS;
}

int UnosIspred(Pozicija P) {
	Pozicija prev = P;
	P = P->next;

	char prez[MAX_SIZE];
	printf("Unesi prezime osobe ispred koje zelis postaviti novu osobu: \n");
	scanf("%s", prez);

	while (P != NULL && strcmp(P->prezime, prez)) {
		prev = P;
		P = P->next;
	}

	if (P != NULL) {
		Pozicija q = NULL;
		q = stvoriOsobu();

		q->next = prev->next;
		prev->next = q;
	}
	else
		printf("Prezime koje ste unijeli ne postoji!\n");

	return EXIT_SUCCESS;
}

int SortiraniUnos(Pozicija P) {

}

