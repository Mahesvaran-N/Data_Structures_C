#include <stdio.h>
#include <stdlib.h>

void findNextGreaterElement(int* arr, int n, int* result) {
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1; 
    for (int i = n - 1; i >= 0; i--) {
        while (top != -1 && stack[top] <= arr[i]) {
            top--;
        }
        if (top == -1) {
            result[i] = -1;
        } else {
            result[i] = stack[top];
        }
        stack[++top] = arr[i];
    }

    
}

int main() {
    int n;
    printf("Enter the size of the array: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    int* result = (int*)malloc(n * sizeof(int));
    printf("Enter the elements of the array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    findNextGreaterElement(arr, n, result);
    printf("Next Greater Elements:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> %d\n", arr[i], result[i]);
    }
    

    return 0;
}
