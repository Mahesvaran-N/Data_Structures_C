#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front; 
    struct Node* rear; 
};
void initializeQueue(struct Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

int isQueueEmpty(struct Queue* q) {
    return q->front == NULL;
}
void enqueue(struct Queue* q, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot enqueue %d.\n", element);
        return;
    }
    newNode->data = element;
    newNode->next = NULL;

    if (isQueueEmpty(q)) {
        q->front = newNode;
    } else {
        q->rear->next = newNode;
    }
    q->rear = newNode;
}

int countElements(struct Queue* q) {
    if (isQueueEmpty(q)) {
        return 0; 
    }

    int count = 0;
    struct Node* current = q->front;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

int main() {
    struct Queue q;
    initializeQueue(&q);

    int choice, element;

    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Count Elements\n");
        printf("3. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &element);
                enqueue(&q, element);
                break;
            case 2:
                printf("Number of elements in the queue: %d\n", countElements(&q));
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
