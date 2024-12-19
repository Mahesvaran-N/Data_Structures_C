#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHAR_COUNT 256

struct Node {
    char data;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(char data) {
    struct Node* newNode = createNode(data);
    if (rear == NULL) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

char dequeue() {
    if (front == NULL) {
        return '\0';
    }
    struct Node* temp = front;
    char data = temp->data;
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

void firstNonRepeating(char* stream) {
    int count[CHAR_COUNT] = {0};
    for (int i = 0; stream[i] != '\0'; i++) {
        char ch = stream[i];
        enqueue(ch);
        count[ch]++;
        
        while (!isEmpty() && count[front->data] > 1) {
            dequeue();
        }

        if (!isEmpty()) {
            printf("First non-repeating character so far: %c\n", front->data);
        } else {
            printf("No non-repeating character so far\n");
        }
    }
}

int main() {
    char stream[100];
    printf("Enter the stream of characters: ");
    scanf("%s", stream);
    firstNonRepeating(stream);
    return 0;
}
