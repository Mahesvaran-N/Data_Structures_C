#include <stdio.h>
#include <string.h>

void removeKDigits(char *num, int k) {
    int n = strlen(num);
    char stack[n];
    int top = -1; 
    for (int i = 0; i < n; i++) {
        while (top >= 0 && stack[top] > num[i] && k > 0) {
            top--;
            k--;
        }
        
        stack[++top] = num[i];
    }

    
    top -= k;

    
    int start = 0;
    while (start <= top && stack[start] == '0') {
        start++;
    }

    
    if (start > top) {
        printf("0\n");
    } else {

        for (int i = start; i <= top; i++) {
            printf("%c", stack[i]);
        }
        printf("\n");
    }
}

int main() {
    char num[100];
    int k;

    printf("Enter the number: ");
    scanf("%s", num);
    printf("Enter the number of digits to remove (k): ");
    scanf("%d", &k);

    printf("Smallest number after removing %d digits: ", k);
    removeKDigits(num, k);

    return 0;
}
