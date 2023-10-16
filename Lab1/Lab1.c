#define _CRT_SECURE_NO_WARNINGS //mora bit PRVA LINIJA KODA!

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)
#define MAX_POINTS (15)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int readNoRowsInFile();
Student* allocateMemoryAndReadStudents(int);
int showStudents(int, Student*);

int main() {

	int noRows = 0;
	Student* students = NULL;

	noRows=ReadNoRowsInFile();

	if (noRows > 0) {
		students = allocateMemoryAndReadStudents();
		showStudents(noRows, students);

		free(students);
	}

	printf("%d", noRows);


		return EXIT_SUCCESS;
}

int readNoRowsInFile() {

	int counter = 0;
	FILE* filePointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filePointer = fopen("students.txt", "r");
	if (!filePointer) {
		printf("File is not opened!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer)) { // character po character
		fgets(buffer, MAX_LINE, filePointer); //za èitanje reda, 1. buffer, 2. max count, 3. file string 
		counter++;								// buffer radi array koji broji bro linija i sprema u char
	}

	fclose(filePointer);
	return counter;
}

Student* allocateMemoryAndReadStudents(int noStudents) {
	int counter = 0;
	FILE* filePointer = NULL;
	Student* students = NULL;

	students = (Student*)malloc(noStudents * sizeof(Student));
	if (!students) {
		printf("Neuspjesna alokacij amemorije!\n");
		return NULL;
	}

	filePointer = fopen("students.txt", "r");
	if (!filePointer)
	{
		printf("Neuspjesno otvaranje datoteke!\n");
		return FILE_ERROR_OPEN;
	}

	while (!feof(filePointer)) {

		fscanf(filePointer, " %s %s %lf", students[counter].name, students[counter].surname, students[counter].points);
		counter++;
	}

	fclose(filePointer);
}

int showStudnets(int noStudents, Student* students) {



}