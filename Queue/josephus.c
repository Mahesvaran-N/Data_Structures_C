#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(int data) {
    struct Node* newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}


int dequeue() {
    if (front == NULL) {
        return -1;
    }
    struct Node* temp = front;
    int data = front->data;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
    return data;
}

int josephus(int n, int k) {
    
    for (int i = 1; i <= n; i++) {
        enqueue(i);
    }

    while (front != NULL && front != rear) {
    
        for (int i = 1; i < k; i++) {
            int person = dequeue();
            enqueue(person);
        }

        
        dequeue();
    }


    return front->data;
}

int main() {
    int n, k;
    printf("Enter the number of people (n): ");
    scanf("%d", &n);
    printf("Enter the step count (k): ");
    scanf("%d", &k);

    int result = josephus(n, k);
    printf("The winner is person %d\n", result);

    return 0;
}
