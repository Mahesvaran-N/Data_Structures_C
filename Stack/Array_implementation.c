#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100 

typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;
void initializeStack(Stack *stack) {
    stack->top = -1;
}
int isEmpty(Stack *stack) {
    return stack->top == -1;
}
int isFull(Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}
void push(Stack *stack, int value) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push %d\n", value);
        return;
    }
    stack->data[++(stack->top)] = value;
    printf("Pushed %d onto the stack.\n", value);
}
int pop(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop.\n");
        return -1;
    }
    return stack->data[(stack->top)--];
}
int peek(Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty! Cannot peek.\n");
        return -1;
    }
    return stack->data[stack->top];
}

int main() {
    Stack stack;
    initializeStack(&stack);

    int choice, value;

    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Check if Empty\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter a value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;
            case 2:
                value = pop(&stack);
                if (value != -1) {
                    printf("Popped %d from the stack.\n", value);
                }
                break;
            case 3:
                value = peek(&stack);
                if (value != -1) {
                    printf("Top element is %d.\n", value);
                }
                break;
            case 4:
                if (isEmpty(&stack)) {
                    printf("Stack is empty.\n");
                } else {
                    printf("Stack is not empty.\n");
                }
                break;
            case 5:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
