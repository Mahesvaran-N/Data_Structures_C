#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024

struct Node {
    char data[MAX_PATH_LENGTH];
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

void initQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}


struct Node* createNode(const char* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;
    return newNode;
}


void enqueue(struct Queue* queue, const char* data) {
    struct Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}


char* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    struct Node* temp = queue->front;
    char* data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}


void simplifyPath(char* path) {
    struct Queue queue;
    initQueue(&queue);
    
    char* token = strtok(path, "/");
    while (token != NULL) {
        if (strcmp(token, ".") == 0 || strlen(token) == 0) {
            
            token = strtok(NULL, "/");
            continue;
        } else if (strcmp(token, "..") == 0) {
            
            if (queue.front != NULL) {
                dequeue(&queue);
            }
        } else {
            
            enqueue(&queue, token);
        }
        token = strtok(NULL, "/");
    }

    
    if (queue.front == NULL) {
        printf("/\n");
        return;
    }


    struct Node* current = queue.front;
    while (current != NULL) {
        printf("/%s", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    char path[MAX_PATH_LENGTH];


    printf("Enter the file system path: ");
    scanf("%s", path); 
    simplifyPath(path);

    return 0;
}
