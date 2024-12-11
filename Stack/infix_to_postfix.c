#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
        return -1;
    }
    struct Node* temp = *top;
    int poppedValue = temp->data;
    *top = (*top)->next;
    free(temp);
    return poppedValue;
}

int peek(struct Node* top) {
    if (top == NULL) {
        return -1;  
    }
    return top->data;
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    struct Node* stack = NULL;
    int k = 0; 

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            postfix[k++] = ch; 
        }
        else if (ch == '(') {
            push(&stack, ch);  
        }
        else if (ch == ')') {
            while (peek(stack) != '(') {
                postfix[k++] = pop(&stack);
            }
            pop(&stack); 
        }
        else {
            while (stack != NULL && precedence(peek(stack)) >= precedence(ch)) {
                postfix[k++] = pop(&stack);
            }
            push(&stack, ch); 
        }
    }
    while (stack != NULL) {
        postfix[k++] = pop(&stack);
    }
    postfix[k] = '\0'; 
}

int evaluatePostfix(char* expr) {
    struct Node* top = NULL;

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        if (isdigit(ch)) {
            push(&top, ch - '0');
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int operand2 = pop(&top);
            int operand1 = pop(&top);
            int result;

            switch (ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                default: result = 0; break;
            }

            push(&top, result);
        }
    }

    return pop(&top); 
}

int main() {
    char infix[100], postfix[100];

    printf("Enter an infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);
    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}
