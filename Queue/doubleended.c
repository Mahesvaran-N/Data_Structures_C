#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct DEPQ {
    struct Node* head;  
    struct Node* tail;  
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

void initializeDEPQ(struct DEPQ* depq) {
    depq->head = depq->tail = NULL;
}

void insert(struct DEPQ* depq, int data) {
    struct Node* newNode = createNode(data);
    

    if (depq->head == NULL) {
        depq->head = depq->tail = newNode;
        return;
    }


    if (data <= depq->head->data) {
        newNode->next = depq->head;
        depq->head->prev = newNode;
        depq->head = newNode;
        return;
    }

    
    if (data >= depq->tail->data) {
        newNode->prev = depq->tail;
        depq->tail->next = newNode;
        depq->tail = newNode;
        return;
    }

    
    struct Node* temp = depq->head;
    while (temp != NULL && temp->data < data) {
        temp = temp->next;
    }
    
    
    newNode->prev = temp->prev;
    newNode->next = temp;
    if (temp->prev != NULL) {
        temp->prev->next = newNode;
    }
    temp->prev = newNode;
}

int getMax(struct DEPQ* depq) {
    if (depq->tail != NULL) {
        return depq->tail->data;
    }
    return -1;  
}

int getMin(struct DEPQ* depq) {
    if (depq->head != NULL) {
        return depq->head->data;
    }
    return -1;
}

int removeMax(struct DEPQ* depq) {
    if (depq->tail == NULL) {
        return -1;  
    }

    int maxData = depq->tail->data;
    struct Node* temp = depq->tail;
    depq->tail = depq->tail->prev;
    
    if (depq->tail != NULL) {
        depq->tail->next = NULL;
    } else {
        depq->head = NULL;  
    }
    
    free(temp);
    return maxData;
}


int removeMin(struct DEPQ* depq) {
    if (depq->head == NULL) {
        return -1;  
    }

    int minData = depq->head->data;
    struct Node* temp = depq->head;
    depq->head = depq->head->next;

    if (depq->head != NULL) {
        depq->head->prev = NULL;
    } else {
        depq->tail = NULL; 
    }
    
    free(temp);
    return minData;
}

void display(struct DEPQ* depq) {
    struct Node* temp = depq->head;
    printf("Queue: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct DEPQ depq;
    initializeDEPQ(&depq);

    int n, value;
    
    printf("Enter the number of elements: ");
    scanf("%d", &n);


    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        insert(&depq, value);
    }

    display(&depq);


    printf("Maximum element: %d\n", getMax(&depq));
    printf("Minimum element: %d\n", getMin(&depq));

    
    printf("Removed maximum element: %d\n", removeMax(&depq));
    printf("Removed minimum element: %d\n", removeMin(&depq));

    
    display(&depq);

    return 0;
}
