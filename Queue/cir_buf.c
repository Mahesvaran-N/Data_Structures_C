#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
    int size;
    int capacity;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

struct Queue* createQueue(int capacity) {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

int isFull(struct Queue* q) {
    return q->size == q->capacity;
}


int isEmpty(struct Queue* q) {
    return q->size == 0;
}

void enqueue(struct Queue* q, int data) {
    if (isFull(q)) {
        
        struct Node* temp = q->front;
        q->front = q->front->next;
        free(temp);  

        
        q->size--;
    }

    
    struct Node* newNode = createNode(data);

    
    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        
        q->rear->next = newNode;
        q->rear = newNode;
    }

    
    q->size++;
}

int dequeue(struct Queue* q) {
    if (isEmpty(q)) {
        return -1;  
    }

    
    struct Node* temp = q->front;
    int data = temp->data;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }


    free(temp);


    q->size--;

    return data;
}


void printQueue(struct Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node* temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int capacity, n, value;

    
    printf("Enter the capacity of the circular buffer: ");
    scanf("%d", &capacity);

    
    struct Queue* q = createQueue(capacity);

    
    printf("Enter the number of elements to enqueue: ");
    scanf("%d", &n);

    
    for (int i = 0; i < n; i++) {
        printf("Enter value to enqueue: ");
        scanf("%d", &value);
        enqueue(q, value);
    }


    printf("Queue after enqueuing elements:\n");
    printQueue(q);

    printf("Enqueuing more elements:\n");
    enqueue(q, 100);
    enqueue(q, 200);
    enqueue(q, 300);


    printf("Queue after overwriting old elements:\n");
    printQueue(q);

    return 0;
}
