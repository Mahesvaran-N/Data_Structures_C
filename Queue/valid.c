#include <stdio.h>
#include <string.h>
int isValidSequence(const char* operations) {
    int enqueueCount = 0; 
    int dequeueCount = 0; 

    for (int i = 0; operations[i] != '\0'; i++) {
        if (operations[i] == 'E') {
            enqueueCount++; 
        } else if (operations[i] == 'D') {
            dequeueCount++; 
            if (dequeueCount > enqueueCount) {
                return 0; 
            }
        } else {
            return 0;  
        }
    }
    return dequeueCount <= enqueueCount;
}

int main() {
    char operations[100];

    printf("Enter the sequence of operations (E for enqueue, D for dequeue): ");
    scanf("%s", operations);

    if (isValidSequence(operations)) {
        printf("The sequence is valid for a queue.\n");
    } else {
        printf("The sequence is invalid for a queue.\n");
    }

    return 0;
}
