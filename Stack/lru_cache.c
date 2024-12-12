#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAPACITY 100

typedef struct {
    int key;
    int value;
} CacheItem;

typedef struct {
    CacheItem stack[MAX_CAPACITY];  
    int top;                        
    int capacity;                   
    int size;                       
    CacheItem *hashMap[MAX_CAPACITY];
} LRUCache;

void initializeCache(LRUCache *cache, int capacity) {
    cache->top = -1;
    cache->capacity = capacity;
    cache->size = 0;
    memset(cache->hashMap, 0, sizeof(cache->hashMap));
}
int hashFunction(int key) {
    return key % MAX_CAPACITY;
}

int findInStack(LRUCache *cache, int key) {
    for (int i = 0; i <= cache->top; i++) {
        if (cache->stack[i].key == key) {
            return i;
        }
    }
    return -1;
}
void moveToTop(LRUCache *cache, int index) {
    CacheItem temp = cache->stack[index];
    for (int i = index; i < cache->top; i++) {
        cache->stack[i] = cache->stack[i + 1];
    }
    cache->stack[cache->top] = temp;
}
void put(LRUCache *cache, int key, int value) {
    int hashIndex = hashFunction(key);
    if (cache->hashMap[hashIndex] != NULL && cache->hashMap[hashIndex]->key == key) {
        cache->hashMap[hashIndex]->value = value;
        int stackIndex = findInStack(cache, key);
        moveToTop(cache, stackIndex);
        return;
    }
    if (cache->size == cache->capacity) {
        CacheItem lru = cache->stack[0];
        int lruHashIndex = hashFunction(lru.key);
        cache->hashMap[lruHashIndex] = NULL;

        for (int i = 0; i < cache->top; i++) {
            cache->stack[i] = cache->stack[i + 1];
        }
        cache->top--;
        cache->size--;
    }

    cache->top++;
    cache->stack[cache->top].key = key;
    cache->stack[cache->top].value = value;
    cache->hashMap[hashIndex] = &cache->stack[cache->top];
    cache->size++;
}

int get(LRUCache *cache, int key) {
    int hashIndex = hashFunction(key);
    if (cache->hashMap[hashIndex] != NULL && cache->hashMap[hashIndex]->key == key) {
        int stackIndex = findInStack(cache, key);
        moveToTop(cache, stackIndex);
        return cache->hashMap[hashIndex]->value;
    }
    return -1;
}
void printCache(LRUCache *cache) {
    printf("Cache state (top to bottom):\n");
    for (int i = cache->top; i >= 0; i--) {
        printf("Key: %d, Value: %d\n", cache->stack[i].key, cache->stack[i].value);
    }
    printf("\n");
}

int main() {
    LRUCache cache;
    int capacity;
    printf("Enter the capacity of the LRU cache: ");
    scanf("%d", &capacity);

    initializeCache(&cache, capacity);

    int choice, key, value;
    while (1) {
        printf("\n1. Put\n2. Get\n3. Print Cache\n4. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key and value: ");
            scanf("%d %d", &key, &value);
            put(&cache, key, value);
            break;
        case 2:
            printf("Enter key: ");
            scanf("%d", &key);
            value = get(&cache, key);
            if (value != -1) {
                printf("Value: %d\n", value);
            } else {
                printf("Key not found in cache.\n");
            }
            break;
        case 3:
            printCache(&cache);
            break;
        case 4:
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
