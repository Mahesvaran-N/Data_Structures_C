#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COLS 1000
int largestRectangleArea(int* heights, int n) {
    int maxArea = 0;
    int stack[MAX_COLS];
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        while (top >= 0 && heights[stack[top]] > heights[i]) {
            int h = heights[stack[top--]];  
            int w = (top == -1) ? i : i - stack[top] - 1;
            maxArea = (maxArea > h * w) ? maxArea : h * w;          }
        stack[++top] = i;
    }
    
    while (top >= 0) {
        int h = heights[stack[top--]];
        int w = (top == -1) ? n : n - stack[top] - 1;
        maxArea = (maxArea > h * w) ? maxArea : h * w;
    }
    
    return maxArea;
}
int maximalRectangle(char** matrix, int rows, int cols) {
    int* heights = (int*)calloc(cols, sizeof(int));
    int maxArea = 0;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
        
            if (matrix[i][j] == '1') {
                heights[j]++;
            } else {
                heights[j] = 0;
            }
        }
        
        
        maxArea = (maxArea > largestRectangleArea(heights, cols)) ? maxArea : largestRectangleArea(heights, cols);
    }
    
    free(heights);
    return maxArea;
}

int main() {
    int rows, cols;
    

    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);
    char** matrix = (char**)malloc(rows * sizeof(char*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (char*)malloc((cols + 1) * sizeof(char));
    }
    
    printf("Enter the binary matrix row by row (only '0' and '1'):\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d: ", i + 1);
        scanf("%s", matrix[i]);
    }
    int result = maximalRectangle(matrix, rows, cols);
    printf("The maximal rectangle area is: %d\n", result);
    

    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    
    return 0;
}
