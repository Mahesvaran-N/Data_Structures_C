#include <stdio.h>
#include <stdlib.h>
struct ListNode {
    int data;
    struct ListNode* next;
};
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct ListNode* createListNode(int data) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}
struct ListNode* findMiddle(struct ListNode* head) {
    if (!head) return NULL;
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct TreeNode* sortedListToBST(struct ListNode** head) {
    if (*head == NULL) {
        return NULL;
    }
    struct ListNode* mid = findMiddle(*head);
    struct TreeNode* root = createTreeNode(mid->data);
    if (*head == mid) {
        *head = (*head)->next;
    }
    root->left = sortedListToBST(head);
    root->right = sortedListToBST(&(mid->next));

    return root;
}
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}
void push(struct ListNode** head, int data) {
    struct ListNode* newNode = createListNode(data);
    newNode->next = *head;
    *head = newNode;
}
void createLinkedList(struct ListNode** head) {
    int n, value;
    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);
    printf("Enter the elements (in sorted order): \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        push(head, value); 
    }
}
int main() {
    struct ListNode* head = NULL;
    createLinkedList(&head);

    printf("Original Linked List: ");
    struct ListNode* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
    struct TreeNode* root = sortedListToBST(&head);
    printf("Inorder Traversal of the BST: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
