/* 2. Definirati strukturu osoba (ime, prezime, godina ro�enja) i napisati program koji:
A. dinami�ki dodaje novi element na po�etak liste,
B. ispisuje listu,
C. dinami�ki dodaje novi element na kraj liste,
D. pronalazi element u listi (po prezimenu),
E. bri�e odre�eni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. */

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE (50)

typedef struct _person* Position;

typedef struct _person {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int main() {
	Person head = { .ime = {0},.prezime = {0}, .birthYear=0, .next=NULL };


	return EXIT_SUCCESS;

}