#include <stdio.h>
#include <stdlib.h>
int maxArea(int height[], int n) {
    int *stack = (int *)malloc(n * sizeof(int)); 
    int top = -1; 
    int max_area = 0; 
    int area, i;
    for (i = 0; i < n;) {
        if (top == -1 || height[stack[top]] <= height[i]) {
            stack[++top] = i++;
        } else {
            int tp = stack[top--];
            area = height[tp] * (top == -1 ? i : i - stack[top] - 1);
            if (area > max_area) {
                max_area = area;
            }
        }
    }
    while (top != -1) {
        int tp = stack[top--];
        area = height[tp] * (top == -1 ? i : i - stack[top] - 1);
        if (area > max_area) {
            max_area = area;
        }
    }
    return max_area;
}
int main() {
    int n;
    printf("Enter the number of bars in the histogram: ");
    scanf("%d", &n);
    int *height = (int *)malloc(n * sizeof(int)); 
    printf("Enter the heights of the histogram bars:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &height[i]);
    }

    int result = maxArea(height, n);
    printf("The largest rectangular area is: %d\n", result);
    return 0;
}
