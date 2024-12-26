#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};


struct Queue {
    int* items;
    int front;
    int rear;
    int capacity;
};

struct Queue* createQueue(int capacity);
void enqueue(struct Queue* queue, int value);
int dequeue(struct Queue* queue);
int isQueueEmpty(struct Queue* queue);

void addEdge(struct Node** adjList, int u, int v);
void topologicalSort(int vertices, struct Node** adjList, int* inDegree);

int main() {
    int vertices = 6; 
    struct Node** adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    for (int i = 0; i < vertices; i++) {
        adjList[i] = NULL;
    }

    
    addEdge(adjList, 5, 2);
    addEdge(adjList, 5, 0);
    addEdge(adjList, 4, 0);
    addEdge(adjList, 4, 1);
    addEdge(adjList, 2, 3);
    addEdge(adjList, 3, 1);

    
    int* inDegree = (int*)calloc(vertices, sizeof(int));
    for (int i = 0; i < vertices; i++) {
        struct Node* temp = adjList[i];
        while (temp) {
            inDegree[temp->vertex]++;
            temp = temp->next;
        }
    }


    printf("Topological Sorting of Tasks:\n");
    topologicalSort(vertices, adjList, inDegree);

    
    for (int i = 0; i < vertices; i++) {
        struct Node* temp = adjList[i];
        while (temp) {
            struct Node* toFree = temp;
            temp = temp->next;
            free(toFree);
        }
    }
    free(adjList);
    free(inDegree);

    return 0;
}

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->items = (int*)malloc(capacity * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}


void enqueue(struct Queue* queue, int value) {
    queue->items[++queue->rear] = value;
}


int dequeue(struct Queue* queue) {
    return queue->items[queue->front++];
}

int isQueueEmpty(struct Queue* queue) {
    return queue->front > queue->rear;
}

void addEdge(struct Node** adjList, int u, int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;
}


void topologicalSort(int vertices, struct Node** adjList, int* inDegree) {
    struct Queue* queue = createQueue(vertices);

    
    for (int i = 0; i < vertices; i++) {
        if (inDegree[i] == 0) {
            enqueue(queue, i);
        }
    }

    
    int count = 0;
    while (!isQueueEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);
        count++;

    
        struct Node* temp = adjList[current];
        while (temp) {
            inDegree[temp->vertex]--;
            if (inDegree[temp->vertex] == 0) {
                enqueue(queue, temp->vertex);
            }
            temp = temp->next;
        }
    }

    
    if (count != vertices) {
        printf("\nThe graph has a cycle. Topological sorting is not possible.\n");
    }

    free(queue->items);
    free(queue);
}
