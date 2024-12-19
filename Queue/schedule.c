#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TaskNode {
    char task[100];
    struct TaskNode* next;
};

struct TaskQueue {
    struct TaskNode* front;
    struct TaskNode* rear;
};

void initQueue(struct TaskQueue* queue) {
    queue->front = queue->rear = NULL;
}

struct TaskNode* createTaskNode(char* task) {
    struct TaskNode* newNode = (struct TaskNode*)malloc(sizeof(struct TaskNode));
    strcpy(newNode->task, task);
    newNode->next = NULL;
    return newNode;
}


void enqueue(struct TaskQueue* queue, char* task) {
    struct TaskNode* newNode = createTaskNode(task);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

void dequeue(struct TaskQueue* queue) {
    if (queue->front == NULL) {
        printf("No tasks to execute.\n");
        return;
    }
    struct TaskNode* temp = queue->front;
    printf("Executing task: %s\n", temp->task);
    queue->front = queue->front->next;


    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
}

int isQueueEmpty(struct TaskQueue* queue) {
    return queue->front == NULL;
}

int main() {
    struct TaskQueue queue;
    initQueue(&queue);

    int n;
    printf("Enter the number of tasks to schedule: ");
    scanf("%d", &n);
    getchar(); 

    
    for (int i = 0; i < n; i++) {
        char task[100];
        printf("Enter task %d: ", i + 1);
        fgets(task, sizeof(task), stdin);
        task[strcspn(task, "\n")] = '\0'; 
        enqueue(&queue, task);
    }

    
    printf("\nProcessing tasks:\n");
    while (!isQueueEmpty(&queue)) {
        dequeue(&queue);
    }

    return 0;
}
