#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

void smallestString(char *pattern) {
    int n = strlen(pattern);
    char result[MAX_LEN] = "";  
    int stack[MAX_LEN];         
    int top = -1;               
    int num = 1;              
    for (int i = 0; i <= n; i++) {
        
        stack[++top] = num++;
        if (i == n || pattern[i] == 'I') {
            
            while (top >= 0) {
                char buffer[5];
                sprintf(buffer, "%d", stack[top--]);
                strcat(result, buffer);
            }
        }
    }

    
    printf("Smallest string: %s\n", result);
}

int main() {
    char pattern[MAX_LEN];

    printf("Enter the pattern (I for increasing, D for decreasing): ");
    scanf("%s", pattern);

    smallestString(pattern);

    return 0;
}
