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
int getListLength(struct Node* head) {
    int length = 0;
    struct Node* temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}
struct Node* findIntersection(struct Node* head1, struct Node* head2) {
    int len1 = getListLength(head1);
    int len2 = getListLength(head2);
    struct Node* temp1 = head1;
    struct Node* temp2 = head2;
    if (len1 > len2) {
        for (int i = 0; i < len1 - len2; i++) {
            temp1 = temp1->next;
        }
    } else if (len2 > len1) {
        for (int i = 0; i < len2 - len1; i++) {
            temp2 = temp2->next;
        }
    }
    while (temp1 != NULL && temp2 != NULL) {
        if (temp1 == temp2) {
            return temp1;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return NULL;  
}

struct Node* getNodeAtPosition(struct Node* head, int position) {
    struct Node* temp = head;
    int count = 0;
    while (temp != NULL && count < position) {
        temp = temp->next;
        count++;
    }
    return temp;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    int value, pos, intersectionPos;
    printf("Enter elements for the first linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head1, value);
    }

    
    printf("Enter elements for the second linked list (enter -1 to stop):\n");
    while (1) {
        printf("Enter value: ");
        scanf("%d", &value);
        if (value == -1) break;
        appendNode(&head2, value);
    }

    
    printf("Enter the position for intersection (enter -1 for no intersection): ");
    scanf("%d", &intersectionPos);

    
    if (intersectionPos != -1) {
        struct Node* intersectionNode = getNodeAtPosition(head1, intersectionPos);
        if (intersectionNode != NULL) {
            struct Node* temp = head2;
        
            while (temp->next != NULL) {
                temp = temp->next;
            }
            
            temp->next = intersectionNode;
        } else {
            printf("Invalid position for intersection.\n");
        }
    }


    printf("List 1: ");
    displayList(head1);
    printf("List 2: ");
    displayList(head2);

    
    struct Node* intersection = findIntersection(head1, head2);
    if (intersection != NULL) {
        printf("Intersection at node with value: %d\n", intersection->data);
    } else {
        printf("No intersection\n");
    }

    return 0;
}
