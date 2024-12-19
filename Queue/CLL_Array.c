#include <stdio.h>
#include <stdlib.h>

#define MAX 100 
struct CircularQueue {
    int front;
    int rear;
    int size;
    int queue[MAX];
};

void initializeQueue(struct CircularQueue* q, int size) {
    q->front = -1;
    q->rear = -1;
    q->size = size;
}

int isEmpty(struct CircularQueue* q) {
    return q->front == -1;
}
int isFull(struct CircularQueue* q) {
    return (q->rear + 1) % q->size == q->front;
}
void enqueue(struct CircularQueue* q, int element) {
    if (isFull(q)) {
        printf("Queue Overflow! Cannot enqueue %d\n", element);
        return;
    }
    if (isEmpty(q)) {
        q->front = 0; 
    }
    q->rear = (q->rear + 1) % q->size; 
    q->queue[q->rear] = element;
    printf("Enqueued: %d\n", element);
}

int dequeue(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue Underflow! Cannot dequeue.\n");
        return -1;
    }
    int dequeuedElement = q->queue[q->front];
    if (q->front == q->rear) { 
        q->front = -1; 
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % q->size; 
    }
    return dequeuedElement;
}


void display(struct CircularQueue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->queue[i]);
        if (i == q->rear) {
            break;
        }
        i = (i + 1) % q->size; 
    }
    printf("\n");
}

int main() {
    struct CircularQueue q;
    int size, choice, element;

    printf("Enter the size of the circular queue (max %d): ", MAX);
    scanf("%d", &size);

    if (size > MAX) {
        printf("Size exceeds maximum limit of %d.\n", MAX);
        return 1;
    }

    initializeQueue(&q, size);

    while (1) {
        printf("\nCircular Queue Operations:\n");
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
