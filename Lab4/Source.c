#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _clan;
typedef struct _clan* Position;

typedef struct _clan {
    int c;
    int e;

    Position next;
} Clan;

int readFromFile(Position, Position);
int sortInput(Position, Position);
int printPolinom(Position);
int sumOfPolinoms(Position, Position, Position);
int productOfPolinoms(Position, Position, Position);
int freeMemory(Position, Position);
Position createPolinom(int, int);

int insertAfter(Position, Position);

int main(void) {
    Clan head = { .c = 0, .e = 0, .next = NULL };
    Clan head1 = { .c = 0, .e = 0, .next = NULL };
    Clan head2 = { .c = 0, .e = 0, .next = NULL };
    Position P = NULL, Q = NULL, tempp = NULL;
    Clan Sum = { .c = 0, .e = 0, .next = NULL };
    Clan Product = { .c = 0, .e = 0, .next = NULL };
    int e = 0, c = 0;
    printf("Polinomi:\n");
    readFromFile(&head1, &head2);
    printf("\n");

    sumOfPolinoms(&head1, &head2, &Sum);
    printf("Suma: ");
    printPolinom(&Sum);
    printf("\n");


    productOfPolinoms(&head1, &head2, &Product);
    printf("\n");
    printf("Produkt: ");
    printPolinom(&Product);

    freeMemory(&head1, tempp);
    freeMemory(&head2, tempp);
    freeMemory(&Sum, tempp);
    freeMemory(&Product, tempp);

    return 0;
}

Position createPolinom(int c, int e) {
    Position x = NULL;
    x = (Position)malloc(sizeof(struct _clan));

    x->c = c;
    x->e = e;
    x->next = NULL;
    return x;
}

int readFromFile(Position head1, Position head2) {
    int n = 0, br = 1, e = 0, c = 0;
    char buffer[256] = { 0 };
    char* p = buffer;
    FILE* fp = NULL;
    fp = fopen("polinomi.txt", "r");

    Position x = NULL;
    Position temp = NULL;

    while (!feof(fp)) {
        fgets(p, 256, fp);

        while (strlen(p) > 0) {

            sscanf(p, "%d %d %n", &c, &e, &n);
            x = createPolinom(c, e);
            if (br == 1) {
                if (x->c != 0)
                    sortInput(head1, x);
            }
            else if (br == 2) {
                if (x->c != 0)
                    sortInput(head2, x);
            }
            p = p + n;
        }
        if (br == 1) {
            printPolinom(head1);
            printf("\n");
        }
        else if (br == 2) {
            printPolinom(head2);
            printf("\n");
        }
        br++;
    }

    return 0;
}


int sortInput(Position head, Position x) {
    Position q = head;
    Position temp = NULL;

    if (x->c == 0)
        return 0;

    while (q != NULL) {
        if (q->next == NULL || (x->e) > (q->next->e)) {
            x->next = q->next;
            q->next = x;
            return 0;
        }
        else if (x->e == q->next->e) {
            q->next->c += x->c;
            if (q->next->c == 0) {
                temp = q->next;
                q->next = q->next->next;
                free(temp);
            }
            return 0;
        }
        q = q->next;
    }
    return -1;
}


int printPolinom(Position head) {
    Position x = head->next;
    while (x != NULL) {
        printf("%dx^%d  ", x->c, x->e);
        x = x->next;
    }
    return 0;
}

int sumOfPolinoms(Position pol1, Position pol2, Position sum) {
    Position P = NULL;
    int n = 0;

    while (pol1 != NULL || pol2 != NULL) {
        if (pol1 == NULL) {
            while (pol2 != NULL) {
                P = createPolinom(pol2->c, pol2->e);
                sortInput(sum, P);
                pol2 = pol2->next;
            }
        }
        else if (pol2 == NULL) {
            while (pol1 != NULL) {
                P = createPolinom(pol1->c, pol1->e);
                sortInput(sum, P);
                pol1 = pol1->next;
            }
        }
        else if (pol1->e > pol2->e) {
            P = createPolinom(pol1->c, pol1->e);
            sortInput(sum, P);
            pol1 = pol1->next;
        }
        else if (pol1->e < pol2->e) {
            P = createPolinom(pol2->c, pol2->e);
            sortInput(sum, P);
            pol2 = pol2->next;
        }
        else if (pol1->e == pol2->e) {
            n = pol1->c + pol2->c;

            if (n == 0) {
                pol1 = pol1->next;
                pol2 = pol2->next;
                continue;
            }
            else {
                P = createPolinom(n, pol1->e);
                sortInput(sum, P);
                pol1 = pol1->next;
                pol2 = pol2->next;
            }
        }
    }
    return 0;
}

int freeMemory(Position head, Position tempp) {
    while (head->next != NULL) {
        tempp = head->next;
        head->next = head->next->next;
        free(tempp);
    }
    return 0;
}

int productOfPolinoms(Position pol1, Position pol2, Position product) {
    Position temp1 = pol2;
    Position newEl = NULL;

    pol1 = pol1->next;
    pol2 = pol2->next;

    while (pol1 != NULL) {
        pol2 = temp1;
        while (pol2 != NULL) {
            newEl = createPolinom(pol1->c * pol2->c, pol1->e + pol2->e);
            sortInput(product, newEl);
            pol2 = pol2->next;
        }
        pol1 = pol1->next;
    }
    return 0;
}