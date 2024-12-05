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
int detectLoopAndFindLength(struct Node* head) {
    if (!head) return 0;
    
    struct Node* slow = head;
    struct Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;        
        fast = fast->next->next;  
        
        if (slow == fast) {
            break;
        }
    }

    if (slow != fast) {
        return 0;
    }

    int loopLength = 1;
    struct Node* temp = slow->next;
    while (temp != slow) {
        temp = temp->next;
        loopLength++;
    }
    
    return loopLength;
}
void createLoop(struct Node* head, int loopStartIndex) {
    struct Node* temp = head;
    struct Node* loopStartNode = NULL;
    int index = 0;
    
    while (temp->next) {
        if (index == loopStartIndex) {
            loopStartNode = temp;
        }
        temp = temp->next;
        index++;
    }

    if (loopStartNode) {
        temp->next = loopStartNode;
    }
}
void printList(struct Node* head) {
    struct Node* temp = head;
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    struct Node* head = createNode(1);
    head->next = createNode(2);
    head->next->next = createNode(3);
    head->next->next->next = createNode(4);
    head->next->next->next->next = createNode(5);
    createLoop(head, 2);
    int loopLength = detectLoopAndFindLength(head);
    
    if (loopLength > 0) {
        printf("Loop detected. Loop length: %d\n", loopLength);
    } else {
        printf("No loop detected.\n");
    }
    
    return 0;
}

