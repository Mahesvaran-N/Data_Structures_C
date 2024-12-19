#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    char data;
    struct Node* next;
};


struct Queue {
    struct Node* front;
    struct Node* rear;
};


struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}


void initQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}

void enqueue(struct Queue* queue, char data) {
    struct Node* newNode = createNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

char dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return '\0';
    }
    struct Node* temp = queue->front;
    char data = queue->front->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return data;
}

char* decodeString(char* s) {
    struct Queue queue;
    initQueue(&queue);
    char numStr[10];
    int numIndex = 0;
    char* result = (char*)malloc(1000 * sizeof(char));
    int resultIndex = 0;

    for (int i = 0; i < strlen(s); i++) {
        char c = s[i];
        
        if (isdigit(c)) {
        
            numStr[numIndex++] = c;
        } else if (c == '[') {
            
            numStr[numIndex] = '\0';
            for (int j = 0; j < numIndex; j++) {
                enqueue(&queue, numStr[j]);
            }
            enqueue(&queue, c); 
            numIndex = 0;
        } else if (c == ']') {
            
            char segment[1000];
            int segmentIndex = 0;
            
            
            while (queue.front != NULL && queue.front->data != '[') {
                segment[segmentIndex++] = dequeue(&queue);
            }
            
            
            dequeue(&queue);
            
    
            int repeatCount = 0;
            int multiplier = 1;
            while (queue.front != NULL && isdigit(queue.front->data)) {
                repeatCount += (dequeue(&queue) - '0') * multiplier;
                multiplier *= 10;
            }
            
    
            for (int j = 0; j < repeatCount; j++) {
                for (int k = 0; k < segmentIndex; k++) {
                    enqueue(&queue, segment[k]);
                }
            }
        } else {
            
            enqueue(&queue, c);
        }
    }
    while (queue.front != NULL) {
        result[resultIndex++] = dequeue(&queue);
    }
    result[resultIndex] = '\0';
    
    return result;
}

int main() {
    char s[100];
    printf("Enter the encoded string: ");
    scanf("%s", s);

    char* decoded = decodeString(s);
    printf("Decoded string: %s\n", decoded);

    free(decoded);
    return 0;
}
