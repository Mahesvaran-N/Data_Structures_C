#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct Stack {
    char pages[MAX_SIZE][50];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}
void push(Stack *stack, const char *page) {
    if (isFull(stack)) {
        printf("Stack overflow. Cannot push '%s'\n", page);
        return;
    }
    strcpy(stack->pages[++stack->top], page);
}
char *pop(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->pages[stack->top--];
}

char *peek(Stack *stack) {
    if (isEmpty(stack)) {
        return NULL;
    }
    return stack->pages[stack->top];
}

int main() {
    Stack backStack, forwardStack;
    initStack(&backStack);
    initStack(&forwardStack);

    char currentPage[50] = "home"; 
    int choice;

    printf("Browser Navigation Simulation\n");
    printf("Current Page: %s\n", currentPage);

    while (1) {
        printf("\nOptions:\n");
        printf("1. Visit a new page\n");
        printf("2. Go Back\n");
        printf("3. Go Forward\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char newPage[50];

        switch (choice) {
            case 1:
                printf("Enter the new page URL: ");
                scanf("%s", newPage);
                push(&backStack, currentPage); 
                initStack(&forwardStack);     
                strcpy(currentPage, newPage); 
                printf("Current Page: %s\n", currentPage);
                break;

            case 2:
                if (isEmpty(&backStack)) {
                    printf("No previous page to go back to.\n");
                } else {
                    push(&forwardStack, currentPage);  
                    strcpy(currentPage, pop(&backStack)); 
                    printf("Current Page: %s\n", currentPage);
                }
                break;

            case 3:
                
                if (isEmpty(&forwardStack)) {
                    printf("No forward page to go to.\n");
                } else {
                    push(&backStack, currentPage);  
                    strcpy(currentPage, pop(&forwardStack)); 
                    printf("Current Page: %s\n", currentPage);
                }
                break;

            case 4:
                
                printf("Exiting browser simulation.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
