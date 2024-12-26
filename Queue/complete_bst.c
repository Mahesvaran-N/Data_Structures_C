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


struct TreeNode* createNode(int data);
struct Queue* createQueue();
void enqueue(struct Queue* queue, struct TreeNode* treeNode);
struct TreeNode* dequeue(struct Queue* queue);
int isEmpty(struct Queue* queue);
int isCompleteBinaryTree(struct TreeNode* root);

int main() {
    
    struct TreeNode* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);

    
    if (isCompleteBinaryTree(root)) {
        printf("The binary tree is a complete binary tree.\n");
    } else {
        printf("The binary tree is not a complete binary tree.\n");
    }

    return 0;
}

struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(struct Queue* queue, struct TreeNode* treeNode) {
    struct QueueNode* newQueueNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newQueueNode->treeNode = treeNode;
    newQueueNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = newQueueNode;
        queue->rear = newQueueNode;
    } else {
        queue->rear->next = newQueueNode;
        queue->rear = newQueueNode;
    }
}

struct TreeNode* dequeue(struct Queue* queue) {
    if (queue->front == NULL) {
        return NULL;
    }
    struct QueueNode* temp = queue->front;
    struct TreeNode* treeNode = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return treeNode;
}

int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}


int isCompleteBinaryTree(struct TreeNode* root) {
    if (root == NULL) {
        return 1; 
    }

    struct Queue* queue = createQueue();
    enqueue(queue, root);
    int flag = 0;

    while (!isEmpty(queue)) {
        struct TreeNode* currentNode = dequeue(queue);

        
        if (currentNode->left) {
            if (flag) {
                
                return 0;
            }
            enqueue(queue, currentNode->left);
        } else {
        
            flag = 1;
        }

    
        if (currentNode->right) {
            if (flag) {
                
                return 0;
            }
            enqueue(queue, currentNode->right);
        } else {
        
            flag = 1;
        }
    }

    return 1; 
}
