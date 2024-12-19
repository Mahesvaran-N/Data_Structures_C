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

void generateBinaryNumbers(int n) {
    enqueue("1");
    for (int i = 1; i <= n; i++) {
        const char* current = dequeue();  
        printf("%s\n", current);

        
        char next1[32], next2[32];
        
        
        strcpy(next1, current);
        strcat(next1, "0");
        
        
        strcpy(next2, current);
        strcat(next2, "1");

        enqueue(next1);
        enqueue(next2);
    }
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);

    printf("Binary numbers from 1 to %d:\n", n);
    generateBinaryNumbers(n);

    return 0;
}
