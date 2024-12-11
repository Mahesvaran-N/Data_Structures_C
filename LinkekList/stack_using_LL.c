#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};
struct Stack {
    struct Node* top;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void initStack(struct Stack* stack) {
    stack->top = NULL;
}
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}
void push(struct Stack* stack, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
    printf("%d pushed onto stack\n", data);
}
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty, nothing to pop.\n");
        return -1; 
    }
    struct Node* temp = stack->top;
    int poppedValue = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return poppedValue;
}
int peek(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty, nothing to peek.\n");
        return -1; 
    }
    return stack->top->data;
}
void printStack(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty.\n");
        return;
    }
    struct Node* temp = stack->top;
    printf("Stack: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
int main() {
    struct Stack stack;
    initStack(&stack);

    int choice, data;

    while (1) {
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Print Stack\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to push: ");
                scanf("%d", &data);
                push(&stack, data);
                break;
            case 2:
                data = pop(&stack);
                if (data != -1) {
                    printf("%d popped from stack\n", data);
                }
                break;
            case 3:
                data = peek(&stack);
                if (data != -1) {
                    printf("Top element is: %d\n", data);
                }
                break;
            case 4:
                printStack(&stack);
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
