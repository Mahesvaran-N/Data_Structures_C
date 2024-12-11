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
int getLength(struct Node* head) {
    int length = 0;
    struct Node* current = head;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}
struct Node** splitList(struct Node* head, int k) {
    int length = getLength(head);
    int partSize = length / k;      
    int extraNodes = length % k;  

    struct Node** parts = (struct Node**)malloc(k * sizeof(struct Node*));
    struct Node* current = head;
    struct Node* previous = NULL;

    for (int i = 0; i < k; i++) {
        parts[i] = current; 
        int currentPartSize = partSize + (extraNodes > 0 ? 1 : 0);
        extraNodes--;
        for (int j = 0; j < currentPartSize && current != NULL; j++) {
            previous = current;
            current = current->next;
        }
        if (previous != NULL) {
            previous->next = NULL;
        }
    }

    return parts;
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
    struct Node* head = NULL;
    struct Node* tail = NULL;

    int n, value, k;
    printf("Enter the number of elements in the list: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        struct Node* newNode = createNode(value);
        if (head == NULL) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    printf("Enter the number of parts to split the list into (k): ");
    scanf("%d", &k);

    if (k <= 0) {
        printf("Invalid value of k. Must be greater than 0.\n");
        return 1;
    }
    struct Node** parts = splitList(head, k);
    printf("The linked list split into %d parts:\n", k);
    for (int i = 0; i < k; i++) {
        printf("Part %d: ", i + 1);
        printList(parts[i]);
    }
    free(parts);

    return 0;
}
