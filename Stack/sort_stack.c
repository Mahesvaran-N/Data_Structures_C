#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Node {
    int data;
    struct Node* next;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void push(struct Node** top, int value) {
    struct Node* newNode = createNode(value);
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

int peek(struct Node* top) {
    return (top != NULL) ? top->data : INT_MIN;
}

int isEmpty(struct Node* top) {
    return top == NULL;
}

void sortedInsert(struct Node** stack, int value) {
    if (isEmpty(*stack) || value > peek(*stack)) {
        push(stack, value);
        return;
    }

    int temp = pop(stack);
    sortedInsert(stack, value);
    push(stack, temp);
}
void sortStack(struct Node** stack) {
    if (!isEmpty(*stack)) {
        int temp = pop(stack);
        sortStack(stack);
        sortedInsert(stack, temp);
    }
}

void printStack(struct Node* top) {
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->next;
    }
    printf("\n");
}

int main() {
    struct Node* stack = NULL;
    int n, value;
    printf("Enter the number of elements in the stack: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        push(&stack, value);
    }

    printf("Original Stack:\n");
    printStack(stack);
    sortStack(&stack);
    printf("\nSorted Stack:\n");
    printStack(stack);

    return 0;
}
