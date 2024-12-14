#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_POOL_SIZE 1024  
#define MAX_ALLOCATIONS 100  

typedef struct {
    void *address;  
    size_t size;   
} Allocation;

typedef struct {
    Allocation allocations[MAX_ALLOCATIONS];
    int top;  
    char memoryPool[MEMORY_POOL_SIZE];  
    size_t used; 
} MemoryStack;

void initMemoryStack(MemoryStack *stack) {
    stack->top = -1;
    stack->used = 0;
}

void *allocate(MemoryStack *stack, size_t size) {
    if (stack->used + size > MEMORY_POOL_SIZE) {
        printf("Memory allocation failed: Not enough space in the memory pool.\n");
        return NULL;
    }
    if (stack->top == MAX_ALLOCATIONS - 1) {
        printf("Memory allocation failed: Allocation stack overflow.\n");
        return NULL;
    }

    
    void *block = stack->memoryPool + stack->used;
    stack->used += size;

    
    stack->allocations[++stack->top] = (Allocation){block, size};
    printf("Allocated %zu bytes at address %p.\n", size, block);

    return block;
}

void freeMemory(MemoryStack *stack) {
    if (stack->top == -1) {
        printf("Memory free failed: Allocation stack underflow.\n");
        return;
    }

    
    Allocation alloc = stack->allocations[stack->top--];
    stack->used -= alloc.size;
    printf("Freed %zu bytes from address %p.\n", alloc.size, alloc.address);
}

void displayMemoryUsage(MemoryStack *stack) {
    printf("\nCurrent Memory Usage:\n");
    printf("Used: %zu bytes | Free: %zu bytes\n", stack->used, MEMORY_POOL_SIZE - stack->used);
    if (stack->top == -1) {
        printf("No active allocations.\n");
    } else {
        printf("Active allocations:\n");
        for (int i = 0; i <= stack->top; i++) {
            printf("  Allocation %d: Address %p, Size %zu bytes\n",
                   i + 1, stack->allocations[i].address, stack->allocations[i].size);
        }
    }
    printf("\n");
}

int main() {
    MemoryStack stack;
    initMemoryStack(&stack);

    int choice;
    size_t size;
    void *address;

    printf("Stack-Based Memory Allocation System\n");
    while (1) {
        printf("\nOptions:\n");
        printf("1. Allocate memory\n");
        printf("2. Free memory\n");
        printf("3. Display memory usage\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter size of memory to allocate (in bytes): ");
                scanf("%zu", &size);
                allocate(&stack, size);
                break;

            case 2:
                freeMemory(&stack);
                break;

            case 3:
                displayMemoryUsage(&stack);
                break;

            case 4:
                printf("Exiting memory allocation system.\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
