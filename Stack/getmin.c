#include <stdio.h>
#include <limits.h>

#define MAX_CAPACITY 1000

struct Stack {
    int arr[MAX_CAPACITY];
    int top;
    int minValue;
};

void initializeStack(struct Stack *stack) {
    stack->top = -1;
    stack->minValue = INT_MAX;
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

int isFull(struct Stack *stack) {
    return stack->top == MAX_CAPACITY - 1;
}

void push(struct Stack *stack, int x) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }

    if (isEmpty(stack)) {
        stack->arr[++stack->top] = x;
        stack->minValue = x;
    } else {
        if (x >= stack->minValue) {
            stack->arr[++stack->top] = x;
        } else {
            stack->arr[++stack->top] = 2 * x - stack->minValue;
            stack->minValue = x;
        }
    }
}
int getMin(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty\n");
        return INT_MIN;
    }
    return stack->minValue;
}

int main() {
    struct Stack stack;
    initializeStack(&stack);

    int n, element;
    printf("Enter the size of the stack: ");
    scanf("%d", &n);

    if (n > MAX_CAPACITY) {
        printf("Stack size exceeds maximum capacity (%d).\n", MAX_CAPACITY);
        return 1;
    }

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &element);
        push(&stack, element);
    }
    printf("Minimum value after all pushes: %d\n", getMin(&stack));
    

    return 0;
}
