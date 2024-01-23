#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (256)

typedef struct _country* PositionCountry;
typedef struct _city* PositionCity;

typedef struct _city {
    char name[MAX_LINE];
    int people;
    PositionCity next;
} City;

typedef struct _country {
    char name[MAX_LINE];
    char filename[MAX_LINE];
    PositionCountry left;
    PositionCountry right;
    PositionCity head;
} Country;

PositionCountry newCountry(char* name, char* filename);
PositionCity newCity(char* name, int people);
PositionCountry insertCountry(PositionCountry root, PositionCountry country);
int inOrder(PositionCountry q);
int readCity(PositionCity head, char* filename);
int readFromFile(PositionCountry head, char* filename);
int cityCmp(City* c1, City* c2);
int sortInput(PositionCity head, PositionCity p);
int print(PositionCountry country);

int main() {
    char filename[MAX_LINE];
    Country root = {
      .name = {0},
      .filename = {0},
      .left = NULL,
      .right = NULL,
      .head = NULL
    };

    City head = {
      .name = {0},
      .people = 0,
      .next = NULL
    };
    printf("Insert filename: ");
    scanf(" %s", filename);
    readFromFile(&root, filename);
    inOrder(&root);

    return 0;
}

int readFromFile(PositionCountry root, char* filename) {
    PositionCountry country = NULL;
    int status = 0;
    char name[MAX_LINE] = { 0 };
    char txt[MAX_LINE] = { 0 };
    FILE* fp = fopen(filename, "r");

    if (!fp) {
        printf("Error: file '%s' not found", filename);
        return EXIT_FAILURE;
    }

    while (!feof(fp)) {
        status = fscanf(fp, " %s %s", name, txt);
        if (status != 2) {
            printf("Error: failed to scan '%s'.\n", filename);
            return EXIT_FAILURE;
        }
        country = newCountry(name, txt);
        root = insertCountry(root, country);

        readCity(country->head, txt);

    }

    return 0;
}

int readCity(PositionCity head, char* filename) {
    PositionCity city = NULL;
    FILE* fp = fopen(filename, "r");

    if (!fp) {
        printf("Error: file '%s' not found.\n", filename);
        return EXIT_FAILURE;
    }
    char name[MAX_LINE] = { 0 };
    int people = 0;
    int status = 0;

    while (!feof(fp)) {
        status = fscanf(fp, " %s %d", name, &people);

        if (status != 2) {
            printf("Error: failed to scan '%s'.\n", filename);
            return EXIT_FAILURE;
        }
        city = newCity(name, people);
        sortInput(head, city);
    }

    return EXIT_SUCCESS;
}

PositionCity newCity(char* name, int people) {
    PositionCity new = NULL;
    new = (City*)malloc(sizeof(City));
    if (!new) {
        printf("Error while allocating memory.\n");
        return NULL;
    }
    strcpy(new->name, name);
    new->people = people;
    new->next = NULL;
    return new;
}

PositionCountry newCountry(char* name, char* filename) {
    PositionCountry new = NULL;
    new = (Country*)malloc(sizeof(Country));
    if (!new) {
        printf("Error while allocating memory.\n");
        return NULL;
    }

    strcpy(new->name, name);
    strcpy(new->filename, filename);
    new->left = NULL;
    new->right = NULL;
    new->head = newCity("", 0);
    return new;
}

int sortInput(PositionCity head, PositionCity p) {
    PositionCity q = head;

    if (head == NULL) {
        return EXIT_SUCCESS;
    }

    while (q->next != NULL && cityCmp(p, q->next) > 0)
        q = q->next;

    p->next = q->next;
    q->next = p;
    return EXIT_SUCCESS;
}

PositionCountry insertCountry(PositionCountry c1, PositionCountry c2) {
    if (NULL == c1) {
        return c2;
    }
    if (strcmp(c1->name, c2->name) > 0) {
        c1->left = insertCountry(c1->left, c2);
    }
    else if (strcmp(c1->name, c2->name) < 0) {
        c1->right = insertCountry(c1->right, c2);
    }
    else {
        free(c2);
    }
    return c1;
}

int cityCmp(City* c1, City* c2) {
    int result = 0;
    result = c1->people - c2->people;

    if (result == 0)
        result = strcmp(c1->name, c2->name);

    return result;
}

int inOrder(PositionCountry p) {
    if (p == NULL) {
        return EXIT_SUCCESS;
    }
    inOrder(p->left);
    printf("%s\n", p->name);
    print(p);
    inOrder(p->right);
    return EXIT_SUCCESS;
}

int print(PositionCountry country) {
    PositionCity q = country->head;
    while (q != NULL) {
        if (q != country->head)
            printf("\t%s %d\n", q->name, q->people);
        q = q->next;
    }
    return EXIT_SUCCESS;
}