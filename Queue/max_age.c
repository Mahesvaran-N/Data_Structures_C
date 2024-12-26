#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int age;
} Person;

// Queue structure
typedef struct {
    Person* people; // Array of people in the queue
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Function prototypes
void initQueue(Queue* queue, int capacity);
int isQueueEmpty(Queue* queue);
void enqueue(Queue* queue, Person person);
Person dequeue(Queue* queue);
void printQueue(Queue* queue);
int countPeopleOlderThanX(Queue* queue, int x);

int main() {
    // Create a queue with capacity for 10 people
    Queue queue;
    initQueue(&queue, 10);

    // Add some people to the queue
    enqueue(&queue, (Person){25});
    enqueue(&queue, (Person){30});
    enqueue(&queue, (Person){18});
    enqueue(&queue, (Person){40});
    enqueue(&queue, (Person){22});

    // Set the age threshold
    int ageThreshold = 25;

    // Find the number of people older than the threshold
    int count = countPeopleOlderThanX(&queue, ageThreshold);

    printf("Number of people with age greater than %d: %d\n", ageThreshold, count);

    // Clean up
    free(queue.people);
    return 0;
}

// Initialize the queue
void initQueue(Queue* queue, int capacity) {
    queue->capacity = capacity;
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->people = (Person*)malloc(capacity * sizeof(Person));
}

// Check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->size == 0;
}

// Add a person to the queue
void enqueue(Queue* queue, Person person) {
    if (queue->size < queue->capacity) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->people[queue->rear] = person;
        queue->size++;
    }
}

// Remove a person from the queue
Person dequeue(Queue* queue) {
    Person person = {0};
    if (!isQueueEmpty(queue)) {
        person = queue->people[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
    }
    return person;
}

// Print the queue (for debugging purposes)
void printQueue(Queue* queue) {
    for (int i = queue->front; i < queue->front + queue->size; i++) {
        int idx = i % queue->capacity;
        printf("Age: %d\n", queue->people[idx].age);
    }
}

// Count the number of people older than a given age
int countPeopleOlderThanX(Queue* queue, int x) {
    int count = 0;
    for (int i = queue->front; i < queue->front + queue->size; i++) {
        int idx = i % queue->capacity;
        if (queue->people[idx].age > x) {
            count++;
        }
    }
    return count;
}
