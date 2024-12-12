#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void appendNode(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

void removeDuplicates(struct Node* head) {
    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* temp = NULL;
    bool seen[1000] = {0}; 
    
    while (current != NULL) {
        if (seen[current->data]) {
            prev->next = current->next;
            free(current);
        } else {
            seen[current->data] = 1;
            prev = current;
        }
        current = prev->next;
    }
}

int main() {
    struct Node* head = NULL;
    int value;
    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head, value);
    }
    printf("Linked List before removing duplicates: ");
    displayList(head);
    removeDuplicates(head);
    printf("Linked List after removing duplicates: ");
    displayList(head);

    return 0;
}
