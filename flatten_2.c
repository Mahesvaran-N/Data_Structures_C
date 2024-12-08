#include <stdio.h>
#include <stdlib.h>
struct Node {
    int data;
    struct Node* next;
    struct Node* child;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->child = NULL;
    return newNode;
}
struct Node* mergeLists(struct Node* a, struct Node* b) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    struct Node* result = NULL;

    if (a->data < b->data) {
        result = a;
        result->child = mergeLists(a->child, b);
    } else {
        result = b;
        result->child = mergeLists(a, b->child);
    }

    return result;
}
struct Node* flattenList(struct Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    head->next = flattenList(head->next);
    head = mergeLists(head, head->next);

    return head;
}
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->child;
    }
    printf("NULL\n");
}
struct Node* createUserList() {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    int num, data;

    printf("Enter the number of nodes in the main list: ");
    scanf("%d", &num);

    for (int i = 0; i < num; i++) {
        printf("Enter data for node %d in the main list: ", i + 1);
        scanf("%d", &data);
        struct Node* newNode = createNode(data);

        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        int childCount;
        printf("Enter the number of child nodes for node %d: ", i + 1);
        scanf("%d", &childCount);

        struct Node* childHead = NULL;
        struct Node* childTail = NULL;
        for (int j = 0; j < childCount; j++) {
            printf("Enter data for child node %d of node %d: ", j + 1, i + 1);
            scanf("%d", &data);
            struct Node* childNode = createNode(data);

            if (childHead == NULL) {
                childHead = childTail = childNode;
            } else {
                childTail->child = childNode;
                childTail = childNode;
            }
        }
        newNode->child = childHead;
    }

    return head;
}
int main() {
    printf("Create a linked list with child pointers.\n");
    struct Node* head = createUserList();
    struct Node* flattenedList = flattenList(head);
    printf("\nFlattened linked list:\n");
    printList(flattenedList);

    return 0;
}
