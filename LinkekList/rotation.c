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
int getLength(struct Node* head) {
    int length = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}
void leftRotate(struct Node** head, int k) {
    if (*head == NULL || k == 0) return;

    int length = getLength(*head);
    k = k % length; 

    if (k == 0) return;

    struct Node* temp = *head;
    int count = 1;
    while (count < k && temp != NULL) {
        temp = temp->next;
        count++;
    }

    struct Node* newHead = temp->next;
    temp->next = NULL;

    struct Node* tail = newHead;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }

    if (tail != NULL) {
        tail->next = *head;
    }

    *head = newHead;
}
void rightRotate(struct Node** head, int k) {
    if (*head == NULL || k == 0) return;

    int length = getLength(*head);
    k = k % length; 

    if (k == 0) return;

    leftRotate(head, length - k);
}

int main() {
    struct Node* head = NULL;
    int value, k, choice;
    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head, value);
    }
    printf("Original Linked List: ");
    displayList(head);
    printf("Enter the number of positions to rotate: ");
    scanf("%d", &k);

    printf("Choose rotation direction:\n1. Left Rotation\n2. Right Rotation\n");
    scanf("%d", &choice);

    if (choice == 1) {
        leftRotate(&head, k);
        printf("List after left rotation by %d positions: ", k);
    } else if (choice == 2) {
        rightRotate(&head, k);
        printf("List after right rotation by %d positions: ", k);
    } else {
        printf("Invalid choice.\n");
        return 0;
    }

    displayList(head);
    return 0;
}
