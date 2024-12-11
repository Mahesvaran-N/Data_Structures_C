#include <stdio.h>
#include <stdlib.h>
struct Stack {
    int* arr;
    int top;
    int capacity;
};
struct Stack* createStack(int capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

int isFull(struct Stack* stack) {
    return stack->top == stack->capacity - 1;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}
void push(struct Stack* stack, int value) {
    if (isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}
int pop(struct Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}
struct Queue {
    struct Stack* stack1;
    struct Stack* stack2;
};
struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->stack1 = createStack(capacity);
    queue->stack2 = createStack(capacity);
    return queue;
}
void enqueue(struct Queue* queue, int value) {
    push(queue->stack1, value);
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue->stack1) && isEmpty(queue->stack2)) {
        printf("Queue is empty\n");
        return -1;
    }
    if (isEmpty(queue->stack2)) {
        while (!isEmpty(queue->stack1)) {
            push(queue->stack2, pop(queue->stack1));
        }
    }
    return pop(queue->stack2);
}

int main() {
    int capacity = 5;
    struct Queue* queue = createQueue(capacity);
    int choice, value;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Enqueue\n2. Dequeue\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                printf("Enter a value to enqueue: ");
                scanf("%d", &value);
                enqueue(queue, value);
                printf("%d enqueued to the queue.\n", value);
                break;

            case 2: 
                value = dequeue(queue);
                if (value != -1) {
                    printf("Dequeued %d from the queue.\n", value);
                }
                break;

            case 3: 
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
