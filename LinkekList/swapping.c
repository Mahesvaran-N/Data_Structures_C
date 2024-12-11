#include <stdio.h>
#include <stdlib.h>

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

void swapNodes(struct Node** head, int x, int y) {
    if (x == y) return;  

    struct Node *prevX = NULL, *currX = *head;
    struct Node *prevY = NULL, *currY = *head;
    while (currX != NULL && currX->data != x) {
        prevX = currX;
        currX = currX->next;
    }
    while (currY != NULL && currY->data != y) {
        prevY = currY;
        currY = currY->next;
    }
    if (currX == NULL || currY == NULL) {
        printf("One or both nodes not found.\n");
        return;
    }
    if (prevX != NULL) {
        prevX->next = currY;
    } else {  
        *head = currY;
    }
    if (prevY != NULL) {
        prevY->next = currX;
    } else {  
        *head = currX;
    }
    struct Node* temp = currX->next;
    currX->next = currY->next;
    currY->next = temp;
}

int main() {
    struct Node* head = NULL;
    int value, x, y;
    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head, value);
    }
    printf("Original Linked List: ");
    displayList(head);
    printf("Enter two values to swap: ");
    scanf("%d %d", &x, &y);
    swapNodes(&head, x, y);
    printf("Linked List after swapping nodes %d and %d: ", x, y);
    displayList(head);

    return 0;
}
