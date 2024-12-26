#include <stdio.h>
#include <stdlib.h>


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
void findSubarrays(int arr[], int n, int target);

int main() {
    
    int arr[] = {2, 1, 4, 3, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 7;

    printf("Subarrays with sum greater than %d are:\n", target);
    findSubarrays(arr, n, target);

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
    if (queue->front == NULL) {
        return -1;
    }
    struct QueueNode* temp = queue->front;
    int index = temp->index;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return index;
}

int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}


void findSubarrays(int arr[], int n, int target) {
    struct Queue* queue = createQueue();
    int currentSum = 0;

    for (int end = 0; end < n; end++) {
        currentSum += arr[end];
        enqueue(queue, end);

        
        while (currentSum > target && !isEmpty(queue)) {
            
            struct QueueNode* temp = queue->front;
            printf("[ ");
            for (; temp != NULL; temp = temp->next) {
                printf("%d ", arr[temp->index]);
            }
            printf("]\n");

            
            int frontIndex = dequeue(queue);
            currentSum -= arr[frontIndex];
        }
    }
}
