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
int evaluatePostfix(char* expr) {
    struct Node* top= NULL; 
    
    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];
        if (isdigit(ch)) {
            push(&top, ch - '0');
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int operand2 = pop(&top);
            int operand1 = pop(&top);
            int result;
            switch(ch) {
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
    char expr[100];
    printf("Enter a postfix expression: ");
    scanf("%s", expr);
    int result = evaluatePostfix(expr);
    printf("Result: %d\n", result);

    return 0;
}
