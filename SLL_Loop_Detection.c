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

void displayList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int detectLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return 1;
        }
    }
    return 0;
}

void removeLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;
    if (!detectLoop(head)) {
        printf("No loop detected.\n");
        return;
    }
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        
        if (slow == fast) {
            break;
        }
    }
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    struct Node* loopStart = slow;
    while (fast->next != loopStart) {
        fast = fast->next;
    }
    fast->next = NULL;
    printf("Loop removed.\n");
}

int main() {
    struct Node* head = NULL;
    int choice, value, position;
    printf("Enter elements for the linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head, value);
    }
    printf("Linked List: ");
    displayList(head);
    printf("Enter position to create a loop (0-based index, -1 for no loop): ");
    scanf("%d", &position);
    if (position != -1) {
        struct Node* temp = head;
        struct Node* loopNode = NULL;
        int i = 0;

        while (temp->next != NULL) {
            if (i == position) {
                loopNode = temp;
            }
            temp = temp->next;
            i++;
        }
        if (loopNode != NULL) {
            temp->next = loopNode;
            printf("Loop created at position %d.\n", position);
        }
    }
    removeLoop(head);
    printf("Modified List: ");
    displayList(head);

    return 0;
}
