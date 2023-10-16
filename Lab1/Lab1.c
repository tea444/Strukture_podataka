#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE (50)
#define MAX_LINE (1024)
#define FILE_ERROR_OPEN (-1)
#define EXIT_SUCCES (0)

typedef struct _student {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
} Student;

int main() {

	int noRows = 0;
	FILE* filepointer = NULL;
	char buffer[MAX_LINE] = { 0 };

	filepointer = fopen("students.txt", "r");
	if (!filepointer) {
		printf("File is not opened!\n");
			return FILE_ERROR_OPEN;
	}

	fclose(filepointer);
	return EXIT_SUCCES;

}