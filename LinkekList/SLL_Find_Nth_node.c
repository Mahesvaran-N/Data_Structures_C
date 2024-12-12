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
struct Node* findNthFromEnd(struct Node* head, int n) {
    struct Node* first = head;
    struct Node* second = head;
    for (int i = 0; i < n; i++) {
        if (first == NULL) {
            return NULL; 
        }
        first = first->next;
    }
    while (first != NULL) {
        first = first->next;
        second = second->next;
    }
return second;
}

int main() {
    struct Node* head = NULL;
    int choice, value, n;
    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head, value);
    }
    printf("Linked List: ");
    displayList(head);
    printf("Enter n to find the nth node from the end: ");
    scanf("%d", &n);

    struct Node* nthNode = findNthFromEnd(head, n);
    if (nthNode != NULL) {
        printf("The %dth node from the end is: %d\n", n, nthNode->data);
    } else {
        printf("The list has fewer than %d nodes.\n", n);
    }

    return 0;
}
