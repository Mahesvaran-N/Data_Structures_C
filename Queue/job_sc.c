#include <stdio.h>
#include <stdlib.h>


struct PrintJob {
    int jobId;       
    int priority;   
    struct PrintJob* next;
};


struct PriorityQueue {
    struct PrintJob* front;
};


struct PriorityQueue* createQueue();
void enqueue(struct PriorityQueue* queue, int jobId, int priority);
struct PrintJob* dequeue(struct PriorityQueue* queue);
int isQueueEmpty(struct PriorityQueue* queue);
void displayQueue(struct PriorityQueue* queue);

int main() {
    struct PriorityQueue* jobQueue = createQueue();
    int choice, jobId, priority;

    printf("Print Job Scheduler with Priority\n");
    printf("1. Add print job\n");
    printf("2. Process next job\n");
    printf("3. View pending jobs\n");
    printf("4. Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter job ID: ");
                scanf("%d", &jobId);
                printf("Enter job priority (1-10, where 1 is highest): ");
                scanf("%d", &priority);
                if (priority < 1 || priority > 10) {
                    printf("Invalid priority. Please enter a value between 1 and 10.\n");
                } else {
                    enqueue(jobQueue, jobId, priority);
                    printf("Job %d with priority %d added to the queue.\n", jobId, priority);
                }
                break;
            case 2:
                if (isQueueEmpty(jobQueue)) {
                    printf("No jobs to process. Queue is empty.\n");
                } else {
                    struct PrintJob* job = dequeue(jobQueue);
                    printf("Processing job %d with priority %d.\n", job->jobId, job->priority);
                    free(job);
                }
                break;
            case 3:
                if (isQueueEmpty(jobQueue)) {
                    printf("No jobs in the queue.\n");
                } else {
                    printf("Pending jobs in the queue:\n");
                    displayQueue(jobQueue);
                }
                break;
            case 4:
                printf("Exiting scheduler.\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}


struct PriorityQueue* createQueue() {
    struct PriorityQueue* queue = (struct PriorityQueue*)malloc(sizeof(struct PriorityQueue));
    queue->front = NULL;
    return queue;
}

void enqueue(struct PriorityQueue* queue, int jobId, int priority) {
    struct PrintJob* newJob = (struct PrintJob*)malloc(sizeof(struct PrintJob));
    newJob->jobId = jobId;
    newJob->priority = priority;
    newJob->next = NULL;

    
    if (queue->front == NULL || queue->front->priority > priority) {
        newJob->next = queue->front;
        queue->front = newJob;
    } else {
        struct PrintJob* temp = queue->front;
        while (temp->next != NULL && temp->next->priority <= priority) {
            temp = temp->next;
        }
        newJob->next = temp->next;
        temp->next = newJob;
    }
}


struct PrintJob* dequeue(struct PriorityQueue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    struct PrintJob* job = queue->front;
    queue->front = queue->front->next;
    return job;
}

int isQueueEmpty(struct PriorityQueue* queue) {
    return queue->front == NULL;
}


void displayQueue(struct PriorityQueue* queue) {
    struct PrintJob* temp = queue->front;
    while (temp != NULL) {
        printf("Job ID: %d, Priority: %d\n", temp->jobId, temp->priority);
        temp = temp->next;
    }
}
