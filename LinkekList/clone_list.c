#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
    struct Node* random;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->random = NULL;
    return newNode;
}
void printInterleavedList(struct Node* head) {
    struct Node* current = head;
    while (current) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
void cloneNodes(struct Node* head) {
    struct Node* current = head;
    while (current) {
        struct Node* clone = createNode(current->data);
        clone->next = current->next;
        current->next = clone;
        current = clone->next;
    }
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);

    printf("Original List:\n");
    printInterleavedList(head);
    cloneNodes(head);

    printf("After Adding Cloned Nodes:\n");
    printInterleavedList(head);

    return 0;
}


