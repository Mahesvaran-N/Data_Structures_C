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
struct Node* reverseKGroup(struct Node* head, int k) {
    if (!head || k <= 1) return head;

    struct Node *current = head, *prev = NULL, *next = NULL;
    int count = 0;
    struct Node* temp = head;
    for (count = 0; temp && count < k; count++) {
        temp = temp->next;
    }
    if (count < k) return head;
    count = 0;
    while (current && count < k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        count++;
    }
    if (next) {
        head->next = reverseKGroup(next, k);
    }
    return prev;
}
void printList(struct Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
struct Node* createList(int n) {
    struct Node* head = createNode(1);
    struct Node* current = head;

    for (int i = 2; i <= n; i++) {
        current->next = createNode(i);
        current = current->next;
    }

    return head;
}

int main() {
    int n = 7;
    struct Node* head = createList(n);

    printf("Original List:\n");
    printList(head);

    int k = 3;
    head = reverseKGroup(head, k);

    printf("Reversed in Groups of %d:\n", k);
    printList(head);

    return 0;
}

