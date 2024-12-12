#include <stdio.h>
#define MAX_CAPACITY 1000
struct Stack {
    int arr[MAX_CAPACITY];  
    int increment[MAX_CAPACITY];  
    int top; 
};

void initializeStack(struct Stack *stack) {
    stack->top = -1; 
    for (int i = 0; i < MAX_CAPACITY; i++) {
        stack->increment[i] = 0;  
    }
}
int isFull(struct Stack *stack) {
    return stack->top == MAX_CAPACITY - 1;
}
void push(struct Stack *stack, int x) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }

    stack->arr[++stack->top] = x; 
    stack->increment[stack->top] = 0; 
}

void increment(struct Stack *stack, int k, int val) {
    int limit = k < stack->top + 1 ? k : stack->top + 1; 
    for (int i = 0; i < limit; i++) {
        stack->increment[i] += val;  
    }
}
void printStack(struct Stack *stack) {
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->arr[i] + stack->increment[i]);
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    initializeStack(&stack);

    int n, element, incrementValue;
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
    printf("Enter the increment value: ");
    scanf("%d", &incrementValue);
    increment(&stack, 3, incrementValue);
    printf("Modified stack: ");
    printStack(&stack);

    return 0;
}
