#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

void push(Stack* stack, int value) {
    if (stack->top < MAX - 1) {
        stack->data[++(stack->top)] = value;
    } else {
        printf("Stack overflow\n");
    }
}

int pop(Stack* stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        return -1; 
    }
    return stack->data[(stack->top)--];
}


int operate(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;  
        case '%': return a % b;
        default: return 0;
    }
}

int main() {
    Stack stack;
    initStack(&stack);

    int num1, num2;
    char op;

    printf("Enter first integer: ");
    scanf("%d", &num1);
    printf("Enter second integer: ");
    scanf("%d", &num2);
    printf("Enter an operator (+, -, *, /, %%): ");
    scanf(" %c", &op);  
    push(&stack, num1);
    push(&stack, num2);
    int b = pop(&stack);
    int a = pop(&stack);
    int result = operate(a, b, op);
    printf("Result of %d %c %d = %d\n", a, op, b, result);

    return 0;
}
