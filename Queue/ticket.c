#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100
struct Queue {
    int tickets[MAX_QUEUE_SIZE]; 
    int front;
    int rear;
};

void initQueue(struct Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
}

int isEmpty(struct Queue* queue) {
    return queue->front > queue->rear;
}

void enqueue(struct Queue* queue, int tickets) {
    if (queue->rear < MAX_QUEUE_SIZE - 1) {
        queue->rear++;
        queue->tickets[queue->rear] = tickets;
    }
}

int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        return -1;
    }
    int ticket = queue->tickets[queue->front];
    queue->front++;
    return ticket;
}
int front(struct Queue* queue) {
    if (isEmpty(queue)) {
        return -1; 
    }
    return queue->tickets[queue->front];
}
int timeToBuyTickets(int* tickets, int n, int k) {
    struct Queue queue;
    initQueue(&queue);


    for (int i = 0; i < n; i++) {
        enqueue(&queue, tickets[i]);
    }

    int time = 0;
    
    while (1) {

        int currentTickets = dequeue(&queue);
        

        time++;
        
        
        if (currentTickets - 1 == 0 && queue.front == k) {
            break;
        }

        
        if (currentTickets > 1) {
            enqueue(&queue, currentTickets - 1);
        }
    }

    return time;
}

int main() {
    int n, k;
    printf("Enter the number of people in the queue: ");
    scanf("%d", &n);
    printf("Enter the position (0-based) of the person: ");
    scanf("%d", &k);
    
    int tickets[n];
    printf("Enter the number of tickets each person needs: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tickets[i]);
    }

    int result = timeToBuyTickets(tickets, n, k);
    printf("Time needed for the person at position %d to buy tickets: %d\n", k, result);

    return 0;
}
