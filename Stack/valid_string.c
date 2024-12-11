#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct Stack {
    char *data;
    int top;
    int capacity;
};
struct Stack* createStack(int capacity) {
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->data = (char *)malloc(capacity * sizeof(char));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}
int isFull(struct Stack *stack) {
    return stack->top == stack->capacity - 1;
}
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}
void push(struct Stack *stack, char ch) {
    if (!isFull(stack)) {
        stack->data[++stack->top] = ch;
    }
}
char pop(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return '\0';
}
char peek(struct Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return '\0';
}
int isValidNumber(const char *str) {
    int n = strlen(str);
    struct Stack *stack = createStack(n);
    int i = 0;
    int hasDigit = 0, hasDot = 0, hasExp = 0;
    while (str[i] == ' ') i++;
    if (str[i] == '+' || str[i] == '-') {
        push(stack, str[i]);
        i++;
    }
    while (str[i] != '\0') {
        char ch = str[i];

        if (isdigit(ch)) {
            hasDigit = 1;
            push(stack, ch);
        }
        else if (ch == '.' && !hasDot && !hasExp) {
            hasDot = 1;
            push(stack, ch);
        }
        else if ((ch == 'e' || ch == 'E') && hasDigit && !hasExp) {
            hasExp = 1;
            hasDigit = 0; 
            push(stack, ch);

            i++;
            if (str[i] == '+' || str[i] == '-') {
                push(stack, str[i]);
                i++;
            }
            if (!isdigit(str[i])) {
                free(stack->data);
                free(stack);
                return 0;
            }
            while (isdigit(str[i])) {
                hasDigit = 1;
                push(stack, str[i]);
                i++;
            }

            continue; 
        }
        else if (ch == ' ') {
            break;
        }
        else{
            break;
        }
        i++;
    }
    while (str[i] == ' ') i++;
    int isValid = hasDigit && str[i] == '\0';

    return isValid;
}
int main() {
    char str[100];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }
    str[strcspn(str, "\n")] = '\0'; 

    if (isValidNumber(str)) {
        printf("The string is a valid number.\n");
    } else {
        printf("The string is not a valid number.\n");
    }

    return 0;
}
