#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    int min;
    struct Node* next;
};
struct Node* createNode(int data, int min) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->min = min;
    newNode->next = NULL;
    return newNode;
}
void push(struct Node** top, int value) {
    int min = (*top == NULL) ? value : (value < (*top)->min ? value : (*top)->min);
    struct Node* newNode = createNode(value, min);
    newNode->next = *top;
    *top = newNode;
}

int pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack underflow!\n");
        return INT_MIN;
    }
    struct Node* temp = *top;
    int poppedValue = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedValue;
}
int top(struct Node* top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return INT_MIN;
    }
    return top->data;
}
int getMin(struct Node* top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return INT_MIN;
    }
    return top->min;
}

int main() {
    struct Node* stack = NULL;
    int choice, value;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Push\n2. Pop\n3. Top\n4. Get Minimum\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter a value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                printf("Pushed %d onto the stack.\n", value);
                break;

            case 2: 
                value = pop(&stack);
                if (value != INT_MIN) {
                    printf("Popped %d from the stack.\n", value);
                }
                break;

            case 3: 
                value = top(stack);
                if (value != INT_MIN) {
                    printf("Top of the stack is %d.\n", value);
                }
                break;

            case 4:  
                value = getMin(stack);
                if (value != INT_MIN) {
                    printf("Minimum value in the stack is %d.\n", value);
                }
                break;

            case 5: 
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
