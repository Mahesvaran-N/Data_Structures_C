#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 100
typedef struct Stack {
    char* data[MAX_HISTORY];
    int top;
} Stack;


void initStack(Stack* stack) {
    stack->top = -1;
}

void push(Stack* stack, const char* state) {
    if (stack->top < MAX_HISTORY - 1) {
        stack->data[++(stack->top)] = strdup(state); 
    }
}


char* pop(Stack* stack) {
    if (stack->top == -1) return NULL;
    return stack->data[(stack->top)--];
}

char* peek(Stack* stack) {
    if (stack->top == -1) return NULL;
    return stack->data[stack->top];
}

void freeStack(Stack* stack) {
    for (int i = 0; i <= stack->top; i++) {
        free(stack->data[i]);
    }
}
void editString(Stack* undoStack, Stack* redoStack, char* str, const char* newState) {

    push(undoStack, str);
    
    
    strcpy(str, newState);
    

    redoStack->top = -1;
}
void undo(Stack* undoStack, Stack* redoStack, char* str) {
    char* lastState = pop(undoStack);
    if (lastState) {
        
        push(redoStack, str);

        strcpy(str, lastState);
        free(lastState);  
        printf("Undo successful. Current string: %s\n", str);
    } else {
        printf("No more undo operations available.\n");
    }
}
void redo(Stack* undoStack, Stack* redoStack, char* str) {
    char* redoState = pop(redoStack);
    if (redoState) {
        
        push(undoStack, str);
        strcpy(str, redoState);
        free(redoState); 
        printf("Redo successful. Current string: %s\n", str);
    } else {
        printf("No more redo operations available.\n");
    }
}

int main() {
    Stack undoStack, redoStack;
    char str[100]; 
    
    
    initStack(&undoStack);
    initStack(&redoStack);
    
    
    printf("Enter the initial string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0'; 
    
    
    printf("Current string: %s\n", str);
    
    int choice;
    char newState[100];
    
    while (1) {
        printf("\nChoose an option:\n");
        printf("1. Edit string\n");
        printf("2. Undo\n");
        printf("3. Redo\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); 
        
        switch (choice) {
            case 1:
                printf("Enter new string: ");
                fgets(newState, sizeof(newState), stdin);
                newState[strcspn(newState, "\n")] = '\0';
                editString(&undoStack, &redoStack, str, newState);
                printf("String after edit: %s\n", str);
                break;
            case 2:
                undo(&undoStack, &redoStack, str);
                break;
            case 3:
                redo(&undoStack, &redoStack, str);
                break;
            case 4:
                printf("Exiting...\n");
                freeStack(&undoStack);
                freeStack(&redoStack);
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}
