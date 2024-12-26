#include <stdio.h>
#include <stdlib.h>


struct QueueNode {
    int floor;
    struct QueueNode* next;
};


struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};


struct Queue* createQueue();
void enqueue(struct Queue* queue, int floor);
int dequeue(struct Queue* queue);
int isEmpty(struct Queue* queue);
void manageElevator(struct Queue* queue, int currentFloor);

int main() {
    struct Queue* requestQueue = createQueue();
    int currentFloor = 1;  

    printf("Elevator Simulation\n");
    printf("1. Add floor request\n");
    printf("2. Process requests\n");
    printf("3. Exit\n");

    while (1) {
        int choice, floor;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the floor number to request (1-10): ");
                scanf("%d", &floor);
                if (floor < 1 || floor > 10) {
                    printf("Invalid floor number. Please enter a floor between 1 and 10.\n");
                } else {
                    enqueue(requestQueue, floor);
                    printf("Floor %d request added.\n", floor);
                }
                break;
            case 2:
                manageElevator(requestQueue, currentFloor);
                currentFloor = 1; 
                break;
            case 3:
                printf("Exiting simulation.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}


struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}


void enqueue(struct Queue* queue, int floor) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->floor = floor;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}


int dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return -1;
    }
    struct QueueNode* temp = queue->front;
    int floor = temp->floor;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return floor;
}

int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}


void manageElevator(struct Queue* queue, int currentFloor) {
    printf("\nProcessing requests:\n");
    while (!isEmpty(queue)) {
        int requestedFloor = dequeue(queue);
        printf("Elevator moving from floor %d to floor %d...\n", currentFloor, requestedFloor);
        currentFloor = requestedFloor;
        printf("Elevator reached floor %d.\n", currentFloor);
    }
    printf("All requests processed. Elevator returning to ground floor.\n");
}
