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
struct Node* reverseKNodes(struct Node* head, int k, int reverse) {
    if (head == NULL || k <= 0) {
        return head;
    }

    struct Node* current = head;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    int count = 0;

    if (reverse) {
        while (current != NULL && count < k) {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
            count++;
        }
        if (next != NULL) {
            head->next = reverseKNodes(next, k, 0); 
        }
        return prev; 
    } else {
        while (current != NULL && count < k) {
            prev = current;
            current = current->next;
            count++;
        }
        if (current != NULL) {
            prev->next = reverseKNodes(current, k, 1); 
        }
        return head;
    }
}
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
int main() {
    int n, k, data;
    struct Node* head = NULL;
    struct Node* tail = NULL;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the values of the nodes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        struct Node* newNode = createNode(data);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    printf("Enter the value of k: ");
    scanf("%d", &k);

    printf("Original list:\n");
    printList(head);

    head = reverseKNodes(head, k, 1);

    printf("Modified list (Reversed alternate k nodes):\n");
    printList(head);

    return 0;
}
