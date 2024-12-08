#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};
struct DLLNode {
    int data;
    struct DLLNode* prev;
    struct DLLNode* next;
};
struct  TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct  TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
struct TreeNode* createBinaryTree() {
    int data;
    printf("Enter node value (-1 to indicate NULL node): ");
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    struct TreeNode* root = createTreeNode(data);
    printf("Enter left child of %d\n", data);
    root->left = createBinaryTree();

    printf("Enter right child of %d\n", data);
    root->right = createBinaryTree();

    return root;
}
void convertToDLL(struct TreeNode* root, struct DLLNode** head, struct DLLNode** prev) {
    if (root == NULL) {
        return;
    }
    convertToDLL(root->left, head, prev);
    struct DLLNode* current = (struct DLLNode*)malloc(sizeof(struct DLLNode));
    current->data = root->data;
    current->prev = NULL;
    current->next = NULL;

    
    if (*head == NULL) {
        *head = current;
    }
    if (*prev != NULL) {
        (*prev)->next = current;
        current->prev = *prev;
    }
    *prev = current;
    convertToDLL(root->right, head, prev);
}
void printDLL(struct DLLNode* head) {
    struct DLLNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
int main() {
    printf("Create the binary tree:\n");
    struct TreeNode* root = createBinaryTree();

    struct DLLNode* head = NULL;
    struct DLLNode* prev = NULL;
    convertToDLL(root, &head, &prev);

    
    printf("Doubly Linked List:\n");
    printDLL(head);

    return 0;
}
