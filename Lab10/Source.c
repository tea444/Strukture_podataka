#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE (256)

typedef struct _country* PositionCountry;
typedef struct _city* PositionCity;

typedef struct _city {
    char name[MAX_LINE];
    int people;
    PositionCity left;
    PositionCity right;
} City;

typedef struct _country {
    char name[MAX_LINE];
    char filename[MAX_LINE];
    PositionCountry next;
    PositionCity root;
} Country;

PositionCountry newCountry(char* name, char* filename);
PositionCountry findCountry(PositionCountry p, char* name);
PositionCity newCity(char* name, int people);
PositionCity insertCity(PositionCity root, PositionCity city);
int findCity(PositionCity p, int people);
int inOrder(PositionCity q);
int readCity(PositionCountry country, char* filename);
int readFromFile(PositionCountry head, char* filename);
int cityCmp(City* c1, City* c2);
int sortInput(PositionCountry head, PositionCountry p);
int print(PositionCountry head);

int main() {
    char filename[MAX_LINE], country[MAX_LINE];
    int people;
    PositionCountry temp = NULL;
    Country head = {
      .name = {0},
      .filename = {0},
      .next = NULL,
      .root = NULL
    };
    printf("Insert filename: ");
    scanf(" %s", filename);
    readFromFile(&head, filename);
    print(&head);

    printf("Country: ");
    scanf(" %s", country);
    printf("Number of people: ");
    scanf(" %d", &people);
    temp = findCountry(&head, country);
    findCity(temp->root, people);

    return 0;
}

int readFromFile(PositionCountry head, char* filename) {
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
        sortInput(head, country);
        readCity(country, txt);

    }

    return 0;
}

int readCity(PositionCountry country, char* filename) {
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
        country->root = insertCity(country->root, city);
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
    new->left = NULL;
    new->right = NULL;
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
    new->next = NULL;
    new->root = NULL;
    return new;
}

int sortInput(PositionCountry head, PositionCountry p) {
    PositionCountry q = head;


    while (q->next != NULL && strcmp(p->name, q->next->name) > 0)
        q = q->next;

    p->next = q->next;
    q->next = p;
    return EXIT_SUCCESS;
}

PositionCity insertCity(PositionCity city1, PositionCity city2) {
    if (NULL == city1) {
        return city2;
    }
    if (cityCmp(city1, city2) > 0) {
        city1->left = insertCity(city1->left, city2);
    }
    else if (cityCmp(city1, city2) < 0) {
        city1->right = insertCity(city1->right, city2);
    }
    else {
        free(city2);
    }
    return city1;
}

int cityCmp(City* c1, City* c2) {
    int result = 0;
    result = c1->people - c2->people;

    if (result == 0)
        result = strcmp(c1->name, c2->name);

    return result;
}

int inOrder(PositionCity p) {
    if (p == NULL) {
        return EXIT_SUCCESS;
    }
    inOrder(p->left);
    printf("\t%s %d\n", p->name, p->people);
    inOrder(p->right);
    return EXIT_SUCCESS;
}

int print(PositionCountry head) {
    head = head->next;
    while (head != NULL) {
        printf("%s\n", head->name);
        inOrder(head->root);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

PositionCountry findCountry(PositionCountry p, char* name) {
    while (p != NULL) {
        if (strcmp(p->name, name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

int findCity(PositionCity p, int b) {
    if (p == NULL)
        return EXIT_SUCCESS;

    if (b >= p->people)
        findCity(p->right, b);
    else {
        findCity(p->right, b);
        findCity(p->left, b);
        printf("%s %d\n", p->name, p->people);
    }
    return EXIT_SUCCESS;
}