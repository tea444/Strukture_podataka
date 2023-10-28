/*
1. Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime, apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100
*/


#define _CRT_SECURE_NO_WARNINGS //mora uvijek biti PRVA LINIJA KODA!

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)
#define MAX_POINTS (15)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int readNoRowsInFile(void);
Student* allocateMemoryAndReadStudents(int);
int showStudents(int, Student*);

int main() {

	int noRows = 0;
	Student* student = NULL;

	printf("Broj redova, tj. studenata zapisanih u datoteci je: %d\n", noRows);

	noRows=readNoRowsInFile();

	if (noRows > 0) {
		student=allocateMemoryAndReadStudents(noRows);
		showStudents(noRows, student);

		free(student);
	}

		return EXIT_SUCCESS;
}

int readNoRowsInFile() {

	int counter = 0;
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen("students.txt", "r");
	if (!fp) {
		printf("File can't open!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(fp)) { // character po character
		fgets(buffer, MAX_LINE, fp); //za èitanje reda, 1. buffer, 2. max count, 3. file string 
		counter++;								
	}

	fclose(fp);
	return counter;  //vraæamo broj redova
}

Student* allocateMemoryAndReadStudents(int noStudents) {
	int counter = 0;
	FILE* fp = NULL;
	Student* students = NULL;

	students = (Student*)malloc(noStudents * sizeof(Student));
	if (!students) {
		printf("Error allocation!\n");
		return NULL;
	}

	fp = fopen("students.txt", "r");
	if (!fp)
	{
		printf("File can't open!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(fp)) {

		fscanf(fp, "%s %s %lf", students[counter].name, students[counter].surname, &students[counter].points);
		counter++;
	}

	fclose(fp);
	
	return students;
}

int showStudents(int noStudents, Student* students) {

	int i = 0;

	for (i = 0;i < noStudents;i++) {

		printf("Ime: %s\t Prezime: %s\t Broj bodova i relativan broj bodova: %lf %lf \n", students[i].name, students[i].surname, students[i].points, students[i].points/MAX_POINTS*100);
	}

	return EXIT_SUCCESS;

} 