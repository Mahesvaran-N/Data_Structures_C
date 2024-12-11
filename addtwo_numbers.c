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
void printList(struct Node* head) {
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
struct Node* addTwoLists(struct Node* l1, struct Node* l2) {
    struct Node* result = NULL; 
    struct Node** current = &result;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = carry;
        if (l1) {
            sum += l1->data;
            l1 = l1->next;
        }
        if (l2) {
            sum += l2->data;
            l2 = l2->next;
        }
        int digit = sum % 10;
        carry = sum / 10;
        *current = createNode(digit);
        current = &((*current)->next);
    }

    return result;
}
int main() {
    struct Node* num1 = NULL;
    struct Node* num2 = NULL;

    appendNode(&num1, 2);
    appendNode(&num1, 4);
    appendNode(&num1, 3);

    appendNode(&num2, 5);
    appendNode(&num2, 6);
    appendNode(&num2, 4);

    printf("First number: ");
    printList(num1);
    printf("Second number: ");
    printList(num2);
    struct Node* result = addTwoLists(num1, num2);

    printf("Sum: ");
    printList(result);

    return 0;
}

