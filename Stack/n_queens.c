#include <stdio.h>
#include <stdlib.h>

#define MAX_N 20

struct Stack {
    int arr[MAX_N];
    int top;
};
void initializeStack(struct Stack *stack) {
    stack->top = -1;
}
void push(struct Stack *stack, int value) {
    if (stack->top >= MAX_N - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->arr[++stack->top] = value;
}
int pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->arr[stack->top--];
}
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

int isValid(struct Stack *stack, int row, int col) {
    for (int i = 0; i <= stack->top; i++) {
        int queenCol = stack->arr[i];
        if (queenCol == col ||                       
            abs(queenCol - col) == row - i) {        
            return 0;
        }
    }
    return 1;
}

void printSolution(struct Stack *stack, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (stack->arr[i] == j) {
                printf("Q ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void solveNQueens(int n) {
    struct Stack stack;
    initializeStack(&stack);

    int row = 0;
    int solutions = 0;

    while (1) {
        int found = 0;
        for (int col = (isEmpty(&stack) ? 0 : stack.arr[stack.top] + 1); col < n; col++) {
            if (isValid(&stack, row, col)) {
                push(&stack, col);
                found = 1;
                break;
            }
        }

        if (!found) {
            if (isEmpty(&stack)) break;
            pop(&stack);
            row--;
        } else {
            row++;
            if (row == n) {
                printf("Solution %d:\n", ++solutions);
                printSolution(&stack, n);
                pop(&stack);
                row--;
            }
        }
    }

    if (solutions == 0) {
        printf("No solutions exist for %d queens.\n", n);
    } else {
        printf("Total solutions: %d\n", solutions);
    }
}

int main() {
    int n;
    printf("Enter the number of queens: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX_N) {
        printf("Invalid input. Please enter a value between 1 and %d.\n", MAX_N);
        return 1;
    }

    solveNQueens(n);
    return 0;
}
