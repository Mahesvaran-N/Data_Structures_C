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
void append(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
        printf("Appended %d as the first node.\n", data);
        return;
    }

    struct Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->next = *head;
    printf("Appended %d to the list.\n", data);
}
void traverse(struct Node* head) {
    if (head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Node* temp = head;
    printf("List: ");

    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != head);

    printf("\n");
}
void deleteKthNode(struct Node** head, int k) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    struct Node* current = *head;
    struct Node* previous = NULL;
    if (k == 1) {
        while (current->next != *head) {
            current = current->next;
        }
        if (current == *head) {
            free(*head);
            *head = NULL;
            printf("Deleted the only node in the list.\n");
            return;
        }
        current->next = (*head)->next;
        struct Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("Deleted node at position %d (the head node).\n", k);
        return;
    }
    previous = *head;
    current = (*head)->next;
    int count = 2;

    while (current != *head && count < k) {
        previous = current;
        current = current->next;
        count++;
    }

    if (count == k && current != *head) {
        previous->next = current->next;
        free(current);
        printf("Deleted node at position %d.\n", k);
    } else if (current == *head && count == k) {
        previous->next = *head;
        free(current);
        printf("Deleted node at position %d (the last node).\n", k);
    } else {
        printf("Position %d does not exist in the list.\n", k);
    }
}
int main() {
    struct Node* head = NULL;
    int choice, value, position;

    while (1) {
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to append: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input. Operation aborted.\n");
                    break;
                }
                append(&head, value);
                break;

            case 2:
                printf("Enter the position (k) of the node to delete: ");
                if (scanf("%d", &position) != 1 || position < 1) {
                    printf("Invalid position. Operation aborted.\n");
                    break;
                }
                deleteKthNode(&head, position);
                break;

            case 3:
                traverse(head);
                break;

            case 4:
                printf("Exiting...\n");
                if (head != NULL) {
                    struct Node* temp = head->next;
                    while (temp != head) {
                        struct Node* next = temp->next;
                        free(temp);
                        temp = next;
                    }
                    free(head);
                }
                return 0;

            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    }

    return 0;
}
