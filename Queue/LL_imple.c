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

void enqueue(struct Queue* q, int element) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed! Cannot enqueue %d\n", element);
        return;
    }
    newNode->data = element;
    newNode->next = NULL;

    if (q->rear == NULL) { 
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    printf("Enqueued: %d\n", element);
}
int dequeue(struct Queue* q) {
    if (q->front == NULL) { 
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }

    struct Node* temp = q->front;
    int dequeuedElement = temp->data;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return dequeuedElement;
}
void display(struct Queue* q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }

    struct Node* current = q->front;
    printf("Queue: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
int main() {
    struct Queue q;
    initializeQueue(&q);

    int choice, element;

    while (1) {
        printf("\nQueue Operations:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
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
                element = dequeue(&q);
                if (element != -1) {
                    printf("Dequeued: %d\n", element);
                }
                break;
            case 3:
                display(&q);
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