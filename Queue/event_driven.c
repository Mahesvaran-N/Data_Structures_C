#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum constants
#define MAX_QUEUES 5
#define MAX_EVENTS 100
#define MAX_TASKS 100

// Event types
typedef enum {
    EVENT_ARRIVAL,
    EVENT_COMPLETION
} EventType;

// Event structure
typedef struct {
    int time;        // Time of the event
    EventType type;  // Type of the event (arrival or completion)
    int queue_id;    // Queue ID for the event
} Event;

// Task structure
typedef struct {
    int id;          // Task ID
    int processing_time;  // Time required to process the task
} Task;

// Queue structure
typedef struct {
    Task tasks[MAX_TASKS];
    int front;
    int rear;
    int count;
} Queue;

// Event queue structure
typedef struct {
    Event events[MAX_EVENTS];
    int size;
} EventQueue;

// Function prototypes
void initQueue(Queue* queue);
int isQueueEmpty(Queue* queue);
void enqueueTask(Queue* queue, Task task);
Task dequeueTask(Queue* queue);

void initEventQueue(EventQueue* eq);
void addEvent(EventQueue* eq, Event event);
Event getNextEvent(EventQueue* eq);

void simulate(int simulation_time, int num_queues);

int main() {
    int simulation_time = 20; // Simulate for 20 time units
    int num_queues = 3;       // Number of queues in the system

    simulate(simulation_time, num_queues);

    return 0;
}

// Initialize a queue
void initQueue(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

// Check if a queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->count == 0;
}

// Enqueue a task into the queue
void enqueueTask(Queue* queue, Task task) {
    if (queue->count < MAX_TASKS) {
        queue->rear = (queue->rear + 1) % MAX_TASKS;
        queue->tasks[queue->rear] = task;
        queue->count++;
    }
}

// Dequeue a task from the queue
Task dequeueTask(Queue* queue) {
    Task task = {0, 0};
    if (!isQueueEmpty(queue)) {
        task = queue->tasks[queue->front];
        queue->front = (queue->front + 1) % MAX_TASKS;
        queue->count--;
    }
    return task;
}

// Initialize the event queue
void initEventQueue(EventQueue* eq) {
    eq->size = 0;
}

// Add an event to the event queue (sorted by time)
void addEvent(EventQueue* eq, Event event) {
    int i = eq->size - 1;
    while (i >= 0 && eq->events[i].time > event.time) {
        eq->events[i + 1] = eq->events[i];
        i--;
    }
    eq->events[i + 1] = event;
    eq->size++;
}

// Get the next event from the event queue
Event getNextEvent(EventQueue* eq) {
    return eq->events[--(eq->size)];
}

// Simulate the system
void simulate(int simulation_time, int num_queues) {
    Queue queues[MAX_QUEUES];
    EventQueue eventQueue;
    int current_time = 0;

    // Initialize queues and event queue
    for (int i = 0; i < num_queues; i++) {
        initQueue(&queues[i]);
    }
    initEventQueue(&eventQueue);

    // Generate initial events (random task arrivals)
    for (int i = 0; i < 10; i++) {
        int arrival_time = rand() % simulation_time;
        int queue_id = rand() % num_queues;
        Event event = {arrival_time, EVENT_ARRIVAL, queue_id};
        addEvent(&eventQueue, event);
    }

    // Simulation loop
    while (eventQueue.size > 0) {
        Event event = getNextEvent(&eventQueue);
        current_time = event.time;

        if (event.type == EVENT_ARRIVAL) {
            // Handle task arrival
            printf("Time %d: Task arrives at Queue %d\n", current_time, event.queue_id);

            Task task = {current_time, (rand() % 5) + 1}; // Task ID and processing time
            enqueueTask(&queues[event.queue_id], task);

            // Schedule a processing completion event if the queue was empty
            if (queues[event.queue_id].count == 1) {
                Event completion_event = {current_time + task.processing_time, EVENT_COMPLETION, event.queue_id};
                addEvent(&eventQueue, completion_event);
            }
        } else if (event.type == EVENT_COMPLETION) {
            // Handle task completion
            Task task = dequeueTask(&queues[event.queue_id]);
            printf("Time %d: Task completed at Queue %d (Task ID: %d)\n", current_time, event.queue_id, task.id);

            // Schedule next task in the queue, if any
            if (!isQueueEmpty(&queues[event.queue_id])) {
                Task next_task = queues[event.queue_id].tasks[queues[event.queue_id].front];
                Event completion_event = {current_time + next_task.processing_time, EVENT_COMPLETION, event.queue_id};
                addEvent(&eventQueue, completion_event);
            }
        }
    }

    printf("Simulation complete.\n");
}
