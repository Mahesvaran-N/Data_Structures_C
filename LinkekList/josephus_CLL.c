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
struct Node* createCircularList(int N) {
    struct Node* head = NULL;
    struct Node* temp = NULL;

    for (int i = 1; i <= N; i++) {
        struct Node* newNode = createNode(i);
        if (head == NULL) {
            head = newNode;
            head->next = head;
        } else {
            temp->next = newNode;
            newNode->next = head; 
        }
        temp = newNode;
    }
    return head;
}
int josephusProblem(struct Node** head, int k) {
    struct Node* current = *head;
    struct Node* previous = NULL;
    while (current->next != current) {
        for (int i = 1; i < k; i++) {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
        printf("Eliminated: %d\n", current->data);
        free(current);
        current = previous->next; 
    }
    *head = current;
    return current->data;
}
int main() {
    int N, k;

    printf("Enter the number of people (N): ");
    scanf("%d", &N);
    printf("Enter the step rate (k): ");
    scanf("%d", &k);
    struct Node* head = createCircularList(N);
    int survivor = josephusProblem(&head, k);
    printf("The survivor is: %d\n", survivor);
    free(head);

    return 0;
}
