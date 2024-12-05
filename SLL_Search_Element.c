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

int countNodes(struct Node* head) {
    int count = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int searchNode(struct Node* head, int value) {
    struct Node* temp = head;
    while (temp != NULL) {
        if (temp->data == value) {
            return 1;  // Value found
        }
        temp = temp->next;
    }
    return 0;  // Value not found
}

int main() {
    struct Node* head = NULL;
    int choice, value;

    while (1) {
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to append: ");
                scanf("%d", &value);
                appendNode(&head, value);
                break;
            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (searchNode(head, value)) {
                    printf("Value %d found in the list.\n", value);
                } else {
                    printf("Value %d not found in the list.\n", value);
                }
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
