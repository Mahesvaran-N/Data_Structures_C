#include <stdio.h>
#include <stdlib.h>
void calculateSpan(int prices[], int n) {
    int* span = (int*)malloc(n * sizeof(int)); 
    int* stack = (int*)malloc(n * sizeof(int));
    int top = -1;
    for (int i = 0; i < n; i++) {
        while (top >= 0 && prices[stack[top]] <= prices[i]) {
            top--;
        }
        if (top == -1) {
            span[i] = i + 1;
        } else {
            span[i] = i - stack[top];
        }
        stack[++top] = i;
    }
    printf("Stock span values: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", span[i]);
    }
    printf("\n");
}

int main() {
    int prices[] = {100, 80, 60, 70, 60, 75, 85};
    int n = sizeof(prices) / sizeof(prices[0]);
    calculateSpan(prices, n);

    return 0;
}
