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
void printFirstKElements(struct Queue* q, int k) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty! No elements to display.\n");
        return;
    }

    struct Node* current = q->front;
    int count = 0;

    printf("First %d elements: ", k);
    while (current != NULL && count < k) {
        printf("%d ", current->data);
        current = current->next;
        count++;
    }
    printf("\n");
}

void displayQueue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }

    printf("Queue: ");
    struct Node* current = q->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Queue q;
    initializeQueue(&q);

    int choice, element, k;

    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Display Queue\n");
        printf("3. Print First K Elements\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &element);
                enqueue(&q, element);
                break;
            case 2:
                displayQueue(&q);
                break;
            case 3:
                printf("Enter the number of elements to display (k): ");
                scanf("%d", &k);
                printFirstKElements(&q, k);
                break;
            case 4:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
