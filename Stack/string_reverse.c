#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        printf("Stack underflow! Cannot pop.\n");
        return '\0';
    }
    return stack->data[stack->top--];
}
void reverseString(char* str) {
    int n = strlen(str);
    Stack stack;
    initializeStack(&stack, n);
    for (int i = 0; i < n; i++) {
        push(&stack, str[i]);
    }
    for (int i = 0; i < n; i++) {
        str[i] = pop(&stack);
    }
}

int main() {
    char str[100];
    scanf("%s", str);
    reverseString(str);
    printf("Reversed string: %s\n", str);

    return 0;
}
