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

struct Node* mergeSortedLists(struct Node* list1, struct Node* list2) {
    struct Node* dummy = createNode(0);
    struct Node* current = dummy;
    while (list1 != NULL && list2 != NULL) {
        if (list1->data <= list2->data) {
            current->next = list1;
            list1 = list1->next;
        } else {
            current->next = list2;
            list2 = list2->next;
        }
        current = current->next;
    }
    if (list1 != NULL) {
        current->next = list1;
    } else {
        current->next = list2;
    }

    struct Node* mergedList = dummy->next;
    free(dummy);
    return mergedList;
}

int main() {
    struct Node* list1 = NULL;
    struct Node* list2 = NULL;
    int choice, value;
    printf("Enter elements for the first sorted linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&list1, value);
    }
    printf("Enter elements for the second sorted linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&list2, value);
    }
    struct Node* mergedList = mergeSortedLists(list1, list2);
    printf("Merged Sorted List: ");
    displayList(mergedList);

    return 0;
}
