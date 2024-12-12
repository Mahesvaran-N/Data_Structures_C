#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100
struct Stack {
    int arr[MAX_SIZE];
    int top;
};
void initializeStack(struct Stack *stack) {
    stack->top = -1;
}
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}
void push(struct Stack *stack, int value) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}
int evaluatePrefix(char *exp) {
    struct Stack stack;
    initializeStack(&stack);
    
    int len = strlen(exp);
    for (int i = len - 1; i >= 0; i--) {
        if (exp[i] == ' ') continue;
        if (isdigit(exp[i])) {
            int num = 0;
            while (i >= 0 && isdigit(exp[i])) {
                num = num * 10 + (exp[i] - '0');
                i--;
            }
            i++; 
            push(&stack, num);
        }
        else {
            int operand1 = pop(&stack);
            int operand2 = pop(&stack);
            int result;
            switch (exp[i]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    if (operand2 == 0) {
                        printf("Division by zero is not allowed.\n");
                        return -1;
                    }
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator\n");
                    return -1;
            }
            push(&stack, result);
        }
    }
    return pop(&stack);
}

int main() {
    char expression[MAX_SIZE];
    printf("Enter a prefix expression: ");
    scanf("%[^\n]s", expression); 
    
    int result = evaluatePrefix(expression);
    printf("Result: %d\n", result);

    return 0;
}
