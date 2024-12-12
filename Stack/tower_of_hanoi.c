#include <stdio.h>
#include <stdlib.h>

#define MAX_DISKS 100

struct Stack {
    int arr[MAX_DISKS];
    int top;
};
void initializeStack(struct Stack *stack) {
    stack->top = -1;
}

int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

void push(struct Stack *stack, int value) {
    if (stack->top == MAX_DISKS - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack->arr[++stack->top] = value;
}
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack->arr[stack->top--];
}
void moveDisk(struct Stack *src, struct Stack *dest, const char *srcName, const char *destName) {
    int disk = pop(src);
    push(dest, disk);
    printf("Move disk %d from %s to %s\n", disk, srcName, destName);
}
void towerOfHanoi(int n, struct Stack *src, struct Stack *dest, struct Stack *aux, const char *srcName, const char *destName, const char *auxName) {
    if (n == 1) {
        moveDisk(src, dest, srcName, destName);
        return;
    }
    towerOfHanoi(n - 1, src, aux, dest, srcName, auxName, destName);
    moveDisk(src, dest, srcName, destName);
    towerOfHanoi(n - 1, aux, dest, src, auxName, destName, srcName);
}

int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);

    if (n > MAX_DISKS) {
        printf("Number of disks exceeds maximum capacity (%d).\n", MAX_DISKS);
        return 1;
    }
    struct Stack src, dest, aux;
    initializeStack(&src);
    initializeStack(&dest);
    initializeStack(&aux);
    for (int i = n; i >= 1; i--) {
        push(&src, i);
    }
    printf("Steps to solve Tower of Hanoi for %d disks:\n", n);
    towerOfHanoi(n, &src, &dest, &aux, "A", "C", "B");

    return 0;
}
