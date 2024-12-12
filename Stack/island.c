#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5
int rowDir[] = {-1, 1, 0, 0}; 
int colDir[] = {0, 0, -1, 1};

struct Stack {
    int arr[ROWS * COLS][2];  
    int top;
};
void initializeStack(struct Stack *stack) {
    stack->top = -1;
}
void push(struct Stack *stack, int row, int col) {
    stack->arr[++stack->top][0] = row;
    stack->arr[stack->top][1] = col;
}
void pop(struct Stack *stack, int *row, int *col) {
    *row = stack->arr[stack->top][0];
    *col = stack->arr[stack->top][1];
    stack->top--;
}
int isValid(int row, int col, int grid[ROWS][COLS], int visited[ROWS][COLS]) {
    return (row >= 0 && row < ROWS && col >= 0 && col < COLS &&
            grid[row][col] == 1 && visited[row][col] == 0);
}
int dfs(int row, int col, int grid[ROWS][COLS], int visited[ROWS][COLS]) {
    struct Stack stack;
    initializeStack(&stack);
    push(&stack, row, col);
    visited[row][col] = 1;

    int area = 0;

    while (stack.top != -1) {
        int r, c;
        pop(&stack, &r, &c);
        area++; 
        for (int i = 0; i < 4; i++) {
            int newRow = r + rowDir[i];
            int newCol = c + colDir[i];

            if (isValid(newRow, newCol, grid, visited)) {
                visited[newRow][newCol] = 1;
                push(&stack, newRow, newCol);
            }
        }
    }

    return area;
}

int maxAreaOfIsland(int grid[ROWS][COLS]) {
    int visited[ROWS][COLS] = {0}; 
    int maxArea = 0;


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (grid[i][j] == 1 && visited[i][j] == 0) {
                
                int area = dfs(i, j, grid, visited);
                maxArea = (area > maxArea) ? area : maxArea;
            }
        }
    }

    return maxArea;
}

int main() {
    int grid[ROWS][COLS] = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0}
    };

    int result = maxAreaOfIsland(grid);
    printf("Maximum area of island: %d\n", result);

    return 0;
}
