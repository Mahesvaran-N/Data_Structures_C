#include <stdio.h>
#include <stdlib.h>
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct QueueNode {
    struct TreeNode* treeNode;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct QueueNode* createQueueNode(struct TreeNode* treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    if (!newNode) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}


struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    if (!q) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isQueueEmpty(struct Queue* q) {
    return q->front == NULL;
}


void enqueue(struct Queue* q, struct TreeNode* treeNode) {
    struct QueueNode* newNode = createQueueNode(treeNode);
    if (q->rear) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (!q->front) {
        q->front = newNode;
    }
}

struct TreeNode* dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Queue underflow\n");
        return NULL;
    }
    struct QueueNode* temp = q->front;
    struct TreeNode* treeNode = temp->treeNode;
    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }

    return treeNode;
}

void levelOrderTraversal(struct TreeNode* root) {
    if (!root) {
        return;
    }

    struct Queue* q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        struct TreeNode* current = dequeue(q);
        printf("%d ", current->data);

        if (current->left) {
            enqueue(q, current->left);
        }
        if (current->right) {
            enqueue(q, current->right);
        }
    }

}


struct TreeNode* buildTree() {
    printf("Enter root node value (-1 for NULL): ");
    int data;
    scanf("%d", &data);
    if (data == -1) {
        return NULL;
    }

    struct TreeNode* root = createTreeNode(data);
    struct Queue* q = createQueue();
    enqueue(q, root);

    while (!isQueueEmpty(q)) {
        struct TreeNode* current = dequeue(q);

        printf("Enter left child of %d (-1 for NULL): ", current->data);
        scanf("%d", &data);
        if (data != -1) {
            current->left = createTreeNode(data);
            enqueue(q, current->left);
        }

        printf("Enter right child of %d (-1 for NULL): ", current->data);
        scanf("%d", &data);
        if (data != -1) {
            current->right = createTreeNode(data);
            enqueue(q, current->right);
        }
    }
    return root; 
}

int main() {
    printf("Build the binary tree:\n");
    struct TreeNode* root = buildTree();

    printf("\nLevel Order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    return 0;
}
