#include <stdio.h>
#include <stdlib.h>


struct GasStation {
    int petrol;
    int distance; 
};


struct QueueNode {
    int index; 
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct Queue* createQueue();
void enqueue(struct Queue* queue, int index);
int dequeue(struct Queue* queue);
int isEmpty(struct Queue* queue);
int circularTour(struct GasStation stations[], int n);

int main() {
    
    struct GasStation stations[] = {
        {4, 6}, {6, 5}, {7, 3}, {4, 5}
    };
    int n = sizeof(stations) / sizeof(stations[0]);

    int start = circularTour(stations, n);

    if (start != -1) {
        printf("The starting point of the circular tour is: %d\n", start);
    } else {
        printf("No possible circular tour exists.\n");
    }

    return 0;
}
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue* queue, int index) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->index = index;
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
    if (queue->front == NULL) return -1;

    struct QueueNode* temp = queue->front;
    int index = temp->index;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;

    free(temp);
    return index;
}


int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

int circularTour(struct GasStation stations[], int n) {
    struct Queue* queue = createQueue();
    int totalPetrol = 0, totalDistance = 0;
    int currentPetrol = 0, start = 0;

    for (int i = 0; i < n; i++) {
        enqueue(queue, i);
        totalPetrol += stations[i].petrol;
        totalDistance += stations[i].distance;

        currentPetrol += stations[i].petrol - stations[i].distance;

        
        while (currentPetrol < 0 && !isEmpty(queue)) {
            int dropped = dequeue(queue);
            currentPetrol -= stations[dropped].petrol - stations[dropped].distance;
            start = (dropped + 1) % n;
        }
    }


    if (totalPetrol < totalDistance) {
        return -1;
    }

    return start;
}
