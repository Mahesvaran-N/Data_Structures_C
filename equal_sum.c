#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
void append(struct Node** head, int data) {
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
    newNode->prev = temp;
}
void findPairsWithSum(struct Node* head, int target) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    struct Node* left = head;
    int found = 0;
    while (left != NULL) {
        struct Node* right = left->next; 
        while (right != NULL) {
            if (left->data + right->data == target) {
                printf("(%d, %d)\n", left->data, right->data);
                found = 1;
            }
            right = right->next;
        }
        left = left->next;
    }

    if (!found) {
        printf("No pairs found with sum %d\n", target);
    }
}
void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
int main() {
    struct Node* head = NULL;
    int n, value, targetSum;

    printf("Enter the number of elements in the doubly linked list: ");
    scanf("%d", &n);

    printf("Enter the elements of the list:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        append(&head, value);
    }

    printf("Enter the target sum: ");
    scanf("%d", &targetSum);

    printf("Doubly Linked List:\n");
    display(head);

    printf("Pairs with sum %d:\n", targetSum);
    findPairsWithSum(head, targetSum);

    return 0;
}
