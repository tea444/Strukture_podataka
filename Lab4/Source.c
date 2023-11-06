/*
4. Napisati program za zbrajanje i mnozenje polinoma. Koeficijenti i eksponenti se
èitaju iz datoteke.
Napomena: Eksponenti u datoteci nisu nuzno sortirani.
*/

#define _CRT_SECURE_NO_WARNINGS
#define EXIT_FAILURE (-1)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _polynome* Position;

typedef struct _polynome {
	int constant;
	int exponent;
	Position next;
}Polynome;


//int readFile(Position, Position, char*);
//int mergeAfter(Positon, Position) current, newElement
//int insertAfter(Position, Position);
//int deleteAfter(Position);;
//int parseStringIntoList(Position, char* ?) head, buffer
//freeMemory();
//addPoly();
//multiplyPoly();

Position createPolynome();
int insertSorted(Position, Position);
int printPolynome(Position);

int main() {
	Polynome Head1 = { .constant = 0, .exponent = 0, .next = NULL }; //treba readFromFile() i ostale funkcijes
    Polynome Head2 = { .constant = 0, .exponent = 0, .next = NULL };

 

	return EXIT_SUCCESS;

}

Position createPolynome() {
    Position newPoly = NULL;
    int _constant = 0;
    int _exponent = 0;

    newPoly = (Position)malloc(sizeof(Polynome));

    if (!newPoly) {
        printf("Error allocation!\n");
        return EXIT_FAILURE;
    }

    printf("Enter a constant:\n");
    scanf("%d", _constant);

    printf("Enter an exponent:\n");
    scanf("%d", _exponent);

    newPoly->constant = _constant;
    newPoly->exponent = _exponent;
    newPoly->next = NULL;

    return newPoly;
}

int insertSorted(Position head1, Position head2) {
    Position temp = NULL;
    temp = (Position)malloc(sizeof(Polynome));

    if (!temp) {
        printf("Error allocation!\n");
        return EXIT_FAILURE;
    }

    if (head2->constant == 0)
        return EXIT_SUCCESS;

    while (head1 != NULL) {
        if (head1->next == NULL || (head2->exponent) > (head1->next->exponent)) {
            head2->next = head1->next;
            head1->next = head2;
            return EXIT_SUCCESS;
        }
        else if (head2->exponent == head1->next->exponent) {
            head1->next->constant += head2->constant;
            if (head1->next->constant == 0) {
                temp = head1->next;
                head1->next = head1->next->next;
                free(temp);
            }
            return EXIT_SUCCESS;
        }
        head1 = head1->next;
    }
    return EXIT_SUCCESS;
}


int printPolynome(Position firstElement) {

    while (firstElement != NULL) {
        printf("%dx^%d  ", firstElement->constant, firstElement->exponent);
        firstElement = firstElement->next;
    }
    return EXIT_SUCCESS;
}
