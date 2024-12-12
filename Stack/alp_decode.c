#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1000

char* decodeString(char* s) {
    char* stack = (char*)malloc(MAX * sizeof(char));
    int top = -1; 
    int len = strlen(s);
    int i = 0;
    int num = 0;

    for (i = 0; i < len; i++) {
        if (isdigit(s[i])) {
            num = num * 10 + (s[i] - '0');
        } else if (s[i] == '[') {
        
            stack[++top] = num;
            num = 0; 
            stack[++top] = '['; 
        } else if (s[i] == ']') {
            char temp[MAX];
            int j = 0;
            while (stack[top] != '[') {
                temp[j++] = stack[top--];
            }
            top--;  
            temp[j] = '\0'; 
            for (int k = 0; k < j / 2; k++) {
                char tempChar = temp[k];
                temp[k] = temp[j - k - 1];
                temp[j - k - 1] = tempChar;
            }
            int repeatCount = stack[top--];
            
        
            for (int k = 0; k < repeatCount; k++) {
                for (int m = 0; m < j; m++) {
                    stack[++top] = temp[m];
                }
            }
        } else {
        
            stack[++top] = s[i];
        }
    }


    char* result = (char*)malloc((top + 1) * sizeof(char));
    for (int i = 0; i <= top; i++) {
        result[i] = stack[i];
    }
    result[top + 1] = '\0';

    
    free(stack);

    return result;
}

int main() {
    char str[MAX];
    
    printf("Enter the encoded string: ");
    scanf("%s", str);  // Using scanf to take the input string
    
    char* decodedStr = decodeString(str);
    printf("Decoded string: %s\n", decodedStr);
    free(decodedStr); // Free the memory allocated for the decoded string
    
    return 0;
}
