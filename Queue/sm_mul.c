#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Queue {
    char** items;
    int front;
    int rear;
    int capacity;
};

struct Queue* createQueue(int capacity);
void enqueue(struct Queue* queue, const char* value);
char* dequeue(struct Queue* queue);
int isQueueEmpty(struct Queue* queue);
int mod(const char* num, int n);

char* findSmallestMultiple(int n);

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    char* result = findSmallestMultiple(n);
    printf("The smallest multiple of %d that contains only 0 and 1 is: %s\n", n, result);

    free(result);
    return 0;
}

struct Queue* createQueue(int capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->items = (char**)malloc(capacity * sizeof(char*));
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    return queue;
}

void enqueue(struct Queue* queue, const char* value) {
    queue->rear++;
    queue->items[queue->rear] = strdup(value);
}

char* dequeue(struct Queue* queue) {
    return queue->items[queue->front++];
}

int isQueueEmpty(struct Queue* queue) {
    return queue->front > queue->rear;
}

int mod(const char* num, int n) {
    int result = 0;
    for (int i = 0; num[i] != '\0'; i++) {
        result = (result * 10 + (num[i] - '0')) % n;
    }
    return result;
}

char* findSmallestMultiple(int n) {
    struct Queue* queue = createQueue(10000);
    int* visited = (int*)calloc(n, sizeof(int));
    char* result = NULL;

    enqueue(queue, "1");

    while (!isQueueEmpty(queue)) {
        char* current = dequeue(queue);

        int remainder = mod(current, n);
        if (remainder == 0) {
            result = strdup(current);
            free(current);
            break;
        }

        if (!visited[remainder]) {
            visited[remainder] = 1;

            char* next0 = (char*)malloc(strlen(current) + 2);
            char* next1 = (char*)malloc(strlen(current) + 2);
            sprintf(next0, "%s0", current);
            sprintf(next1, "%s1", current);

            enqueue(queue, next0);
            enqueue(queue, next1);

            free(next0);
            free(next1);
        }

        free(current);
    }

    for (int i = queue->front; i <= queue->rear; i++) {
        free(queue->items[i]);
    }
    free(queue->items);
    free(queue);
    free(visited);

    return result;
}
