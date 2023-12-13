#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define EXIT_SUCCESS 0
#define EXIT_FAILURE -1


typedef struct dir* Position;
typedef struct stack* PositionStack;
typedef struct dir {
    char name[MAX];
    Position sibling;
    Position child;
}Dir;

typedef struct stack {
    Position el;
    PositionStack next;
}Stack;

int makeDir(Position, char*);
int Push(PositionStack, Position);
int printDir(Position);
int terminal(PositionStack, Position);
Position changeDir(Position, char*, PositionStack);
Position changeToParentDir(Position, PositionStack);
Position Pop(PositionStack);
Position newDir();
Position delete(Position);



int main() {
    Position temp = NULL;
    char name[MAX] = { 0 };
    Dir root = {
    .name = "C:",
    .sibling = NULL,
    .child = NULL
    };

    Stack head = {
      .el = NULL,
      .next = NULL
    };
    Push(&head, &root);
    terminal(&head, &root);
    delete(root.child);
}

Position newDir() {
    Position new = NULL;
    new = (Position)malloc(sizeof(Dir));
    if (!new) {
        printf("Memory allocation unsuccessful.\n");
        return NULL;
    }
    new->child = NULL;
    new->sibling = NULL;
    return new;
}


int makeDir(Position current, char* name) {
    Position new = NULL;
    Position p = current->child;
    Position temp = NULL;
    Position prev = NULL;
    new = newDir();
    strcpy(new->name, name);
    if (p == NULL) {
        current->child = new;
        return EXIT_SUCCESS;
    }

    else if (strcmp(p->name, new->name) > 0) {
        new->sibling = p;
        current->child = new;
        return EXIT_SUCCESS;
    }

    while (p != NULL && (strcmp(p->name, new->name) < 0)) {
        prev = p;
        p = p->sibling;
    }

    prev->sibling = new;
    new->sibling = p;

    return EXIT_SUCCESS;
}

int Push(PositionStack stack, Position dir) {
    PositionStack p = stack;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = (PositionStack)malloc(sizeof(Stack));
    p->next->next = NULL;
    p->next->el = dir;

    return EXIT_SUCCESS;
}

Position Pop(PositionStack stack) {
    PositionStack p = stack;
    PositionStack temp = NULL;
    Position dir = NULL;

    if (stack->next == NULL) {
        return NULL;
    }

    while (p->next->next != NULL) {
        p = p->next;
    }

    temp = p->next;
    dir = temp->el;
    p->next = NULL;
    free(temp);

    return dir;
}

Position changeDir(Position current, char* name, PositionStack stack) {
    Position p = current->child;
    if (!current->child) {
        printf("\nThe system cannot find the path specified.\n");
        return current;
    }
    while (p != NULL && strcmp(p->name, name) != 0) {
        p = p->sibling;
    }
    if (!p) {
        printf("\nThe system cannot find the path specified.\n");
        return current;
    }
    Push(stack, p);
    return p;
}

Position changeToParentDir(Position current, PositionStack stack) {
    Pop(stack);
    current = Pop(stack);
    Push(stack, current);
    return current;
}

int printDir(Position current) {
    if (!current->child) {
        printf("Directory is empty!\n");
    }
    else {
        Position p = current->child;
        while (p != NULL) {
            printf("\t%s\n", p->name);
            p = p->sibling;
        }
    }
    return EXIT_SUCCESS;
}

int terminal(PositionStack stack, Position current) {
    char input[MAX] = { 0 };
    char cmd[MAX] = { 0 };
    char name[MAX] = { 0 };
    PositionStack p = stack->next;
    do {
        while (p != NULL) {
            printf("%s\\", p->el->name);
            p = p->next;
        }
        printf(">");
        fgets(input, MAX, stdin);
        sscanf(input, " %s %[^\n]", cmd, name);
        if (strcmp(cmd, "md") == 0) {
            makeDir(current, name);
        }
        else if (strcmp(cmd, "cd..") == 0) {
            current = changeToParentDir(current, stack);
        }
        else if (strcmp(cmd, "cd") == 0) {
            current = changeDir(current, name, stack);
        }
        else if (strcmp(cmd, "dir") == 0) {
            printDir(current);
        }
        else if (strcmp(cmd, "exit") == 0) {
            break;
        }
        else {
            printf("'%s' is not recognized as an internal or external command, operable program or batch file.\n", cmd);
        }
        p = stack->next;
        printf("\n");
    } while (strcmp(input, "exit") != 0);
    return EXIT_SUCCESS;
}

Position delete(Position current) {
    if (current == NULL) {
        return NULL;
    }
    current->sibling = delete(current->sibling);
    current->child = delete(current->child);
    free(current);
    return NULL;
}
