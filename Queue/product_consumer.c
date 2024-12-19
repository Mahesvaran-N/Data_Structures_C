#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
    int maxSize;
    int currentSize;
};


void initQueue(struct Queue* queue, int maxSize) {
    queue->front = queue->rear = NULL;
    queue->maxSize = maxSize;
    queue->currentSize = 0;
}

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(struct Queue* queue, int data) {
    if (queue->currentSize == queue->maxSize) {
        printf("Queue is full! Producer is waiting...\n");
        return;  
    }
    struct Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->currentSize++;
    printf("Produced: %d\n", data);
}

int dequeue(struct Queue* queue) {
    if (queue->currentSize == 0) {
        printf("Queue is empty! Consumer is waiting...\n");
        return -1; 
    }
    struct Node* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    queue->currentSize--;
    return data;
}


void delay(int seconds) {
    for (int i = 0; i < seconds * 1000000; i++) {
        
    }
}

void producer(struct Queue* queue, int itemsToProduce) {
    for (int i = 0; i < itemsToProduce; i++) {
        enqueue(queue, i);  
        delay(1);  
    }
}

void consumer(struct Queue* queue, int itemsToConsume) {
    for (int i = 0; i < itemsToConsume; i++) {
        int item = dequeue(queue);  
        if (item != -1) { 
            printf("Consumed: %d\n", item);
        }
        delay(2);  
    }
}

int main() {
    struct Queue queue;
    int maxSize = 5; 
    int itemsToProduce = 10;  
    int itemsToConsume = 10;  

    
    initQueue(&queue, maxSize);


    printf("Starting Producer-Consumer Simulation...\n");
    producer(&queue, itemsToProduce);
    consumer(&queue, itemsToConsume);

    return 0;
}
