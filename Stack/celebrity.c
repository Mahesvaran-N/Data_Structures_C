#include <stdio.h>
#include <stdlib.h>
int knows(int M[][4], int a, int b) {
    return M[a][b] == 1;
}
int findCelebrity(int M[][4], int n) {
    int stack[n];
    int top = -1;
    for (int i = 0; i < n; i++) {
        stack[++top] = i;
    }
    while (top > 0) {
        int a = stack[top--];
        int b = stack[top];
        if (knows(M, a, b)) {
            stack[top] = b;
        } else {
            stack[top] = a;
        }
    }
    int candidate = stack[0];
    for (int i = 0; i < n; i++) {
        if (i != candidate && knows(M, candidate, i)) {
            return -1;
        }
        if (i != candidate && !knows(M, i, candidate)) {
            return -1;
        }
    }

    return candidate;
}

int main() {
    int M[4][4] = {
        {0, 1, 0, 0}, 
        {0, 0, 0, 0}, 
        {0, 1, 0, 1}, 
        {0, 1, 0, 0} 
    };

    int n = 4;

    int celebrity = findCelebrity(M, n);

    if (celebrity == -1) {
        printf("There is no celebrity.\n");
    } else {
        printf("Person %d is the celebrity.\n", celebrity);
    }

    return 0;
}
