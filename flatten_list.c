#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
    struct Node* child;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    newNode->child = NULL;
    return newNode;
}
struct Node* flatten(struct Node* head) {
    struct Node* current = head;

    while (current) {
        if (current->child) {
            struct Node* child = flatten(current->child);
            struct Node* next = current->next;
            current->next = child;
            child->prev = current;
            current->child = NULL;
            struct Node* tail = child;
            while (tail->next) {
                tail = tail->next;
            }
            if (next) {
                tail->next = next;
                next->prev = tail;
            }
        }

        current = current->next;
    }

    return head;
}
void displayList(struct Node* head) {
    while (head) {
        printf("%d ", head->data);
        if (head->child) {
            printf("(child: %d) ", head->child->data);
        }
        head = head->next;
    }
    printf("\n");
}
int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->prev = head;
    head->next->next = createNode(3);
    head->next->next->prev = head->next;
    head->next->child = createNode(4);
    head->next->child->next = createNode(5);
    head->next->child->next->prev = head->next->child;
    printf("Original list:\n");
    displayList(head);
    head = flatten(head);
    printf("Flattened list:\n");
    displayList(head);

    return 0;
}
