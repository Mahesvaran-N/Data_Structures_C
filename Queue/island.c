#include <stdio.h>
#include <stdlib.h>

struct Point {
    int row;
    int col;
};


struct QueueNode {
    struct Point point;
    struct QueueNode* next;
};

struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};

struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

int isQueueEmpty(struct Queue* q) {
    return q->front == NULL;
}

void enqueue(struct Queue* q, int row, int col) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->point.row = row;
    newNode->point.col = col;
    newNode->next = NULL;
    if (q->rear) {
        q->rear->next = newNode;
    }
    q->rear = newNode;
    if (!q->front) {
        q->front = newNode;
    }
}


struct Point dequeue(struct Queue* q) {
    if (isQueueEmpty(q)) {
        struct Point invalid = {-1, -1};
        return invalid;
    }
    struct QueueNode* temp = q->front;
    struct Point point = temp->point;
    q->front = q->front->next;
    if (!q->front) {
        q->rear = NULL;
    }
    free(temp);
    return point;
}
int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void bfs(int** grid, int rows, int cols, int startRow, int startCol) {
    struct Queue* q = createQueue();
    enqueue(q, startRow, startCol);
    grid[startRow][startCol] = 0; 

    while (!isQueueEmpty(q)) {
        struct Point current = dequeue(q);
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + directions[i][0];
            int newCol = current.col + directions[i][1];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == 1) {
                grid[newRow][newCol] = 0; 
                enqueue(q, newRow, newCol);
            }
        }
    }

    
    free(q);
}


int numIslands(int** grid, int rows, int cols) {
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == 1) {
                count++;
                bfs(grid, rows, cols, i, j);
            }
        }
    }

    return count;
}


int** createGrid(int rows, int cols) {
    int** grid = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)malloc(cols * sizeof(int));
    }
    return grid;
}

int main() {
    int rows, cols;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    int** grid = createGrid(rows, cols);

    printf("Enter the grid values (0 for water, 1 for land):\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int result = numIslands(grid, rows, cols);
    printf("Number of Islands: %d\n", result);

    
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}
