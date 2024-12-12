#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void insertAtHead(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}
struct Node* addLargeNumbers(struct Node* num1, struct Node* num2) {
    struct Node* result = NULL;
    int carry = 0;

    while (num1 != NULL || num2 != NULL || carry > 0) {
        int sum = carry;

        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }

        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        insertAtHead(&result, sum);
    }

    return result;
}
void printList(struct Node* head) {
    struct Node* current = head;
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
    }
    printf("\n");
}
struct Node* createListFromString(char* number) {
    struct Node* head = NULL;
    int length = strlen(number);

    for (int i = 0; i < length; i++) {
        insertAtHead(&head, number[i] - '0');
    }

    return head;
}
int main() {
    char num1[1000], num2[1000];

    printf("Enter the first large number: ");
    scanf("%s", num1);

    printf("Enter the second large number: ");
    scanf("%s", num2);

    struct Node* list1 = createListFromString(num1);
    struct Node* list2 = createListFromString(num2);
    list1 = reverseList(list1);
    list2 = reverseList(list2);
    struct Node* result = addLargeNumbers(list1, list2);
    printf("The sum is: ");
    printList(result);

    return 0;
}
