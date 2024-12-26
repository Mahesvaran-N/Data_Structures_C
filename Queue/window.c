#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 1000

typedef struct {
    int data[MAX_HEAP_SIZE];
    int size;
} Heap;


void initHeap(Heap* heap);
void insertHeap(Heap* heap, int value, int isMaxHeap);
int removeRoot(Heap* heap, int isMaxHeap);
int peekRoot(Heap* heap);
void balanceHeaps(Heap* maxHeap, Heap* minHeap);


void slidingWindowMedian(int* nums, int n, int k, double* result);

int main() {
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    int k = 3;
    double result[n - k + 1];

    slidingWindowMedian(nums, n, k, result);

    printf("Sliding Window Median:\n");
    for (int i = 0; i < n - k + 1; i++) {
        printf("%.1f ", result[i]);
    }
    printf("\n");

    return 0;
}

void initHeap(Heap* heap) {
    heap->size = 0;
}

void insertHeap(Heap* heap, int value, int isMaxHeap) {
    heap->data[heap->size] = value;
    int i = heap->size;
    heap->size++;

    
    while (i > 0) {
        int parent = (i - 1) / 2;
        if ((isMaxHeap && heap->data[i] > heap->data[parent]) ||
            (!isMaxHeap && heap->data[i] < heap->data[parent])) {
            int temp = heap->data[i];
            heap->data[i] = heap->data[parent];
            heap->data[parent] = temp;
            i = parent;
        } else {
            break;
        }
    }
}


int removeRoot(Heap* heap, int isMaxHeap) {
    if (heap->size == 0) return -1;
    int root = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int swapIdx = i;

        if (left < heap->size &&
            ((isMaxHeap && heap->data[left] > heap->data[swapIdx]) ||
             (!isMaxHeap && heap->data[left] < heap->data[swapIdx]))) {
            swapIdx = left;
        }

        if (right < heap->size &&
            ((isMaxHeap && heap->data[right] > heap->data[swapIdx]) ||
             (!isMaxHeap && heap->data[right] < heap->data[swapIdx]))) {
            swapIdx = right;
        }

        if (swapIdx == i) break;

        int temp = heap->data[i];
        heap->data[i] = heap->data[swapIdx];
        heap->data[swapIdx] = temp;
        i = swapIdx;
    }

    return root;
}

int peekRoot(Heap* heap) {
    return heap->size > 0 ? heap->data[0] : -1;
}

void balanceHeaps(Heap* maxHeap, Heap* minHeap) {
    if (maxHeap->size > minHeap->size + 1) {
        insertHeap(minHeap, removeRoot(maxHeap, 1), 0);
    } else if (minHeap->size > maxHeap->size) {
        insertHeap(maxHeap, removeRoot(minHeap, 0), 1);
    }
}

void slidingWindowMedian(int* nums, int n, int k, double* result) {
    Heap maxHeap, minHeap;
    initHeap(&maxHeap);
    initHeap(&minHeap);

    for (int i = 0; i < n; i++) {
        
        if (maxHeap.size == 0 || nums[i] <= peekRoot(&maxHeap)) {
            insertHeap(&maxHeap, nums[i], 1);
        } else {
            insertHeap(&minHeap, nums[i], 0);
        }

        balanceHeaps(&maxHeap, &minHeap);

        
        if (i >= k) {
            int toRemove = nums[i - k];
            if (toRemove <= peekRoot(&maxHeap)) {
                removeRoot(&maxHeap, 1);
            } else {
                removeRoot(&minHeap, 0);
            }
            balanceHeaps(&maxHeap, &minHeap);
        }

        
        if (i >= k - 1) {
            if (maxHeap.size > minHeap.size) {
                result[i - k + 1] = (double)peekRoot(&maxHeap);
            } else {
                result[i - k + 1] = ((double)peekRoot(&maxHeap) + peekRoot(&minHeap)) / 2.0;
            }
        }
    }
}
