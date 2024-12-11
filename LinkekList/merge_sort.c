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
struct Node* getMiddle(struct Node* head) {
    if (!head || !head->next) {
        return head;
    }
    struct Node* slow = head;
    struct Node* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct Node* mergeSortedLists(struct Node* left, struct Node* right) {
    if (!left) return right;
    if (!right) return left;

    struct Node* result = NULL;
    if (left->data <= right->data) {
        result = left;
        result->next = mergeSortedLists(left->next, right);
    } else {
        result = right;
        result->next = mergeSortedLists(left, right->next);
    }
    return result;
}
struct Node* mergeSort(struct Node* head) {
    if (!head || !head->next) {
        return head;
    }
    struct Node* middle = getMiddle(head);
    struct Node* nextHalf = middle->next;
    middle->next = NULL;
    struct Node* left = mergeSort(head);
    struct Node* right = mergeSort(nextHalf);
    return mergeSortedLists(left, right);
}
void printList(struct Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
int main() {
    struct Node* head = createNode(4);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(3);

    printf("Original list:\n");
    printList(head);
    head = mergeSort(head);

    printf("Sorted list:\n");
    printList(head);

    return 0;
}
