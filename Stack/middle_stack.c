#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Stack {
    struct Node* top;
    struct Node* middle;
    int size;
};
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void initializeStack(struct Stack* stack) {
    stack->top = NULL;
    stack->middle = NULL;
    stack->size = 0;
}
void push(struct Stack* stack, int data) {
    struct Node* newNode = createNode(data);
    
    if (stack->top == NULL) {
        stack->top = newNode;
        stack->middle = newNode;
    } else {
        newNode->next = stack->top;
        stack->top = newNode;
        stack->size++;
        if (stack->size % 2 == 0) {
            stack->middle = stack->middle->next;
        }
    }
    stack->size++;
    printf("Pushed %d onto the stack.\n", data);
}
int pop(struct Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is empty!\n");
        return -1; 
    }
    
    struct Node* temp = stack->top;
    int poppedData = temp->data;
    stack->top = stack->top->next;
    stack->size--;
    if (stack->size % 2 != 0) {
        stack->middle = stack->middle->next;
    }
    
    free(temp);
    printf("Popped %d from the stack.\n", poppedData);
    return poppedData;
}
int getMiddle(struct Stack* stack) {
    if (stack->middle == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->middle->data;
}
int deleteMiddle(struct Stack* stack) {
    if (stack->middle == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }

    struct Node* temp = stack->top;
    if (stack->size == 1) {
        free(temp);
        stack->top = NULL;
        stack->middle = NULL;
        stack->size = 0;
        printf("Deleted the only element from the stack.\n");
        return temp->data;
    }
    struct Node* prev = NULL;
    while (temp != stack->middle) {
        prev = temp;
        temp = temp->next;
    }
    if (prev != NULL) {
        prev->next = temp->next;
    }
    int deletedData = temp->data;
    free(temp);
    stack->size--;
    if (stack->size % 2 != 0) {
        stack->middle = stack->middle->next;
    }

    printf("Deleted the middle element: %d\n", deletedData);
    return deletedData;
}
void displayStack(struct Stack* stack) {
    struct Node* current = stack->top;
    printf("Stack elements: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    initializeStack(&stack);

    int choice, value;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Push\n2. Pop\n3. Get Middle\n4. Delete Middle\n5. Display Stack\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&stack, value);
                break;

            case 2:
                pop(&stack);
                break;

            case 3:
                value = getMiddle(&stack);
                if (value != -1) {
                    printf("Middle element is %d.\n", value);
                }
                break;

            case 4:
                deleteMiddle(&stack);
                break;

            case 5:
                displayStack(&stack);
                break;

            case 6:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    }

    return 0;
}
