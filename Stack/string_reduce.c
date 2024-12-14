#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000 
int canBeReducedToEmpty(const char *str) {
    char stack[MAX_SIZE]; 
    int top = -1;         

    for (int i = 0; str[i] != '\0'; i++) {
        if (top >= 0 && stack[top] == str[i]) {
            top--;
        } else {
            stack[++top] = str[i];
        }
    }
    return top == -1;
}

int main() {
    char input[MAX_SIZE];
    printf("Enter the string: ");
    scanf("%s", input);
    if (canBeReducedToEmpty(input)) {
        printf("The string can be reduced to an empty string.\n");
    } else {
        printf("The string cannot be reduced to an empty string.\n");
    }

    return 0;
}

