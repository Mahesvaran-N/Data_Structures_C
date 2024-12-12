#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* stack[100];
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        struct TreeNode* node = stack[top--];
        printf("%d ", node->val);
        if (node->right) stack[++top] = node->right;
        if (node->left) stack[++top] = node->left;
    }
    printf("\n");
}
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* stack[100]; 
    int top = -1;
    struct TreeNode* current = root;

    while (top >= 0 || current != NULL) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->val);
        current = current->right;
    }
    printf("\n");
}
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL) return;

    struct TreeNode* stack1[100];
    struct TreeNode* stack2[100];
    int top1 = -1, top2 = -1;

    stack1[++top1] = root;

    while (top1 >= 0) {
        struct TreeNode* node = stack1[top1--];
        stack2[++top2] = node;
        if (node->left) stack1[++top1] = node->left;
        if (node->right) stack1[++top1] = node->right;
    }
    while (top2 >= 0) {
        struct TreeNode* node = stack2[top2--];
        printf("%d ", node->val);
    }
    printf("\n");
}
struct TreeNode* createTree() {
    int value;
    printf("Enter value for root node: ");
    scanf("%d", &value);

    struct TreeNode* root = createNode(value);
    printf("Enter value for left child of %d (Enter -1 for NULL): ", root->val);
    int leftValue;
    scanf("%d", &leftValue);
    if (leftValue != -1) {
        root->left = createNode(leftValue);
    }

    printf("Enter value for right child of %d (Enter -1 for NULL): ", root->val);
    int rightValue;
    scanf("%d", &rightValue);
    if (rightValue != -1) {
        root->right = createNode(rightValue);
    }

    return root;
}

int main() {
    struct TreeNode* root = createTree();
    int choice;
    while (1) {
        printf("\nChoose a traversal to perform:\n");
        printf("1. Preorder Traversal\n");
        printf("2. Inorder Traversal\n");
        printf("3. Postorder Traversal\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Preorder Traversal: ");
                preorderTraversal(root);
                break;

            case 2:
                printf("Inorder Traversal: ");
                inorderTraversal(root);
                break;

            case 3:
                printf("Postorder Traversal: ");
                postorderTraversal(root);
                break;

            case 4:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
