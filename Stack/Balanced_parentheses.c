#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char* data;
    int top;
    int capacity;
} Stack;

void initializeStack(Stack* stack, int capacity) {
    stack->data = (char*)malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
}

void push(Stack* stack, char ch) {
    if (stack->top == stack->capacity - 1) {
        printf("Stack overflow! Cannot push '%c'.\n", ch);
        return;
    }
    stack->data[++stack->top] = ch;
}

char pop(Stack* stack) {
    if (stack->top == -1) {
        return '\0'; 
    }
    return stack->data[stack->top--];
}

bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

bool isOpening(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}

bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

bool isBalanced(char* expr) {
    int n = 0;
    while (expr[n] != '\0') n++; 

    Stack stack;
    initializeStack(&stack, n);

    for (int i = 0; i < n; i++) {
        char ch = expr[i];

        if (isOpening(ch)) {
            push(&stack, ch); 
        } else if (ch == ')' || ch == '}' || ch == ']') {
            char top = pop(&stack);  
            if (!isMatchingPair(top, ch)) {
                free(stack.data);
                return false;  
            }
        }
    }

    bool balanced = isEmpty(&stack); 
    free(stack.data);  
    return balanced;
}

int main() {
    char expr[100];

    printf("Enter an expression: ");
    scanf("%s", expr);

    if (isBalanced(expr)) {
        printf("The expression is balanced.\n");
    } else {
        printf("The expression is not balanced.\n");
    }

    return 0;
}
