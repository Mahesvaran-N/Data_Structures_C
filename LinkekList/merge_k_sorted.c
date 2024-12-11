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
struct Node* mergeTwoLists(struct Node* list1, struct Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    struct Node* result = NULL;

    if (list1->data < list2->data) {
        result = list1;
        result->next = mergeTwoLists(list1->next, list2);
    } else {
        result = list2;
        result->next = mergeTwoLists(list1, list2->next);
    }

    return result;
}
struct Node* mergeKLists(struct Node* lists[], int k) {
    if (k == 0) return NULL;
    if (k == 1) return lists[0];
    int mid = k / 2;
    struct Node* left = mergeKLists(lists, mid);
    struct Node* right = mergeKLists(lists + mid, k - mid);

    return mergeTwoLists(left, right);
}
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}
struct Node* createUserList() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int n, data;

    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter data for element %d: ", i + 1);
        scanf("%d", &data);
        struct Node* newNode = createNode(data);

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    return head;
}
int main() {
    int k;
    printf("Enter the number of sorted linked lists (k): ");
    scanf("%d", &k);

    struct Node* lists[k];

    for (int i = 0; i < k; i++) {
        printf("Creating sorted linked list %d:\n", i + 1);
        lists[i] = createUserList();
    }

    printf("\nMerging all sorted linked lists...\n");
    struct Node* mergedList = mergeKLists(lists, k);

    printf("Merged sorted linked list:\n");
    printList(mergedList);

    return 0;
}
