#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    const char* data;  
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

struct Node* createNode(const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(const char* data) {
    struct Node* newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

const char* dequeue() {
    if (front == NULL) {
        return NULL;
    }
    struct Node* temp = front;
    const char* data = temp->data;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
    return data;
}

int isEmpty() {
    return front == NULL;
}

void interleaveQueue() {
    if (front == NULL) {
        return;
    }

    
    struct Node* tempNode = front;
    int size = 0;

    
    while (tempNode != NULL) {
        size++;
        tempNode = tempNode->next;
    }

    
    int mid = size / 2;
    

    const char* firstHalf[mid];
    tempNode = front;
    for (int i = 0; i < mid; i++) {
        firstHalf[i] = dequeue();
    }

    
    const char* secondHalf[size - mid];
    for (int i = 0; i < size - mid; i++) {
        secondHalf[i] = dequeue();
    }

    
    for (int i = 0; i < mid; i++) {
        enqueue(firstHalf[i]);
        enqueue(secondHalf[i]);
    }

    
    if (size % 2 != 0) {
        enqueue(secondHalf[mid]);
    }
}

void printQueue() {
    struct Node* temp = front;
    while (temp != NULL) {
        printf("%s ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of elements in the queue: ");
    scanf("%d", &n);

    printf("Enter the elements of the queue (space-separated):\n");
    for (int i = 0; i < n; i++) {
        char temp[32];
        scanf("%s", temp);  
        enqueue(temp); 
    }

    
    printf("Original queue: ");
    printQueue();


    interleaveQueue();

    
    printf("Queue after interleaving: ");
    printQueue();

    return 0;
}
