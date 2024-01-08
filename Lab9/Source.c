#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EXIT_SUCCESS (0)
#define ERROR (-1)
#define min (10)
#define max (90)

typedef struct tree* Position;
typedef struct stack* PositionStack;
typedef struct tree {
    int el;
    Position left;
    Position right;
} Tree;

Position insert(Position p, Position q);
Position newNode(int el);
Position delete(Position p);
int replace(Position p);
int inOrder(Position p);
int generateRand();
int writeInFile(char* filename, Position p);
int inOrderFile(FILE* fp, Position p);
int main() {
    Position root = NULL;
    Position q = NULL;
    Position temp = NULL;
    char filename[256];
    int el, x;
    int sum = 0;
    printf("Filename: ");
    scanf(" %s", filename);
    root = insert(root, newNode(2));
    root = insert(root, newNode(5));
    root = insert(root, newNode(7));
    root = insert(root, newNode(8));
    root = insert(root, newNode(11));
    root = insert(root, newNode(1));
    root = insert(root, newNode(4));
    root = insert(root, newNode(2));
    root = insert(root, newNode(3));
    root = insert(root, newNode(7));

    inOrder(root);
    printf("\n");
    writeInFile(filename, root);

    replace(root);
    inOrder(root);
    printf("\n");
    writeInFile(filename, root);

    root = delete(root);

    //generiranje random broja:
    srand(time(0));
    for (int i = 0; i < 10; i++) {
        q = newNode(generateRand());
        if (i == 0) {
            root = q;
        }
        else {
            insert(root, q);
        }
    }

    inOrder(root);
    printf("\n");
    writeInFile(filename, root);

    replace(root);
    writeInFile(filename, root);
    inOrder(root);
    printf("\n");

    root = delete(root);

    return EXIT_SUCCESS;
}

int generateRand() {
    int x = rand() % (max - min + 1) + min;
    return x;
}

Position newNode(int el) {
    Position new = NULL;
    new = (Position)malloc(sizeof(Tree));
    if (!new) {
        printf("Memory allocation unsuccessful.\n");
        return NULL;
    }
    new->el = el;
    new->left = NULL;
    new->right = NULL;
    return new;
}


Position insert(Position p, Position q) {
    if (p == NULL) {
        return q;
    }
    if (p->el > q->el) {
        p->right = insert(p->right, q);
    }
    else if (p->el <= q->el) {
        p->left = insert(p->left, q);
    }
    else {
        free(q);
    }
    return p;
}

int inOrder(Position p) {
    if (p == NULL) {
        return EXIT_SUCCESS;
    }
    inOrder(p->left);
    printf("%d ", p->el);
    inOrder(p->right);
    return EXIT_SUCCESS;
}


int replace(Position p) {
    if (p == NULL)
        return EXIT_SUCCESS;
    int sum = p->el;
    p->el = replace(p->left) + replace(p->right);
    return (p->el + sum);
}

int writeInFile(char* filename, Position p) {
    FILE* fp = NULL;
    fp = fopen(filename, "a");
    if (!fp) {
        printf("Error while trying to open the file!\n");
        return ERROR;
    }
    inOrderFile(fp, p);
    fprintf(fp, "\n");
    fclose(fp);
    return EXIT_SUCCESS;
}

int inOrderFile(FILE* fp, Position p) {
    if (p == NULL)
        return EXIT_SUCCESS;
    inOrderFile(fp, p->left);
    fprintf(fp, "%d  ", p->el);
    inOrderFile(fp, p->right);
    return EXIT_SUCCESS;
}

Position delete(Position p) {
    if (p == NULL) {
        return NULL;
    }
    p->left = delete(p->left);
    p->right = delete(p->right);
    free(p);
    return NULL;
}