
# HEAP SORT
```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct heap {
    int elem[MAX];
    int count;
} Heap;

// Initialize the heap
void Initialize(Heap *h) {
    h->count = 0;
}

// Insert element and maintain min-heap property
void Insert(Heap *h, int value) {
    if (h->count == MAX) {
        printf("Heap is full.\n");
        return;
    }
    
    h->elem[h->count] = value;
    h->count++;

    // Restore min-heap property by percolating up
    int index = h->count - 1;
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (h->elem[parent] <= h->elem[index])
            break;

        int temp = h->elem[parent];
        h->elem[parent] = h->elem[index];
        h->elem[index] = temp;
        index = parent;
    }
}

// Heapify subtree at given index
void MinHeapify(Heap *h, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < h->count && h->elem[left] < h->elem[smallest])
        smallest = left;
    if (right < h->count && h->elem[right] < h->elem[smallest])
        smallest = right;

    if (smallest != index) {
        int temp = h->elem[index];
        h->elem[index] = h->elem[smallest];
        h->elem[smallest] = temp;
        MinHeapify(h, smallest);
    }
}

// Delete minimum element (root) from heap
int DeleteMin(Heap *h) {
    if (h->count == 0) {
        printf("Heap is empty.\n");
        return -1;
    }

    int min = h->elem[0];
    h->elem[0] = h->elem[h->count - 1];
    h->count--;
    MinHeapify(h, 0);
    return min;
}

// Print heap elements
void PrintHeap(Heap *h) {
    printf("Heap elements: ");
    for (int i = 0; i < h->count; i++) {
        printf("%d ", h->elem[i]);
    }
    printf("\n");
}

// HeapSort using min-heap
void HeapSort(int arr[], int n) {
    Heap h;
    Initialize(&h);

    // Build heap by inserting elements
    for (int i = 0; i < n; i++)
        Insert(&h, arr[i]);

    // Print heap before sorting
    printf("Heap before HeapSort:\n");
    PrintHeap(&h);

    // Extract elements in sorted order
    for (int i = 0; i < n; i++)
        arr[i] = DeleteMin(&h);
}

int main() {
    int arr[] = {6, 7, 4, 3, 1, 2, 5, 8};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    HeapSort(arr, n);

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}

```

# MAX HEAP
```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 15

typedef struct heap {
    int elem[MAX];
    int count;
} Heap;

// Initialize heap
void Initialize(Heap *h) {
    h->count = 0;
    printf("==========================\n");
    printf("Initialized the MaxHeap.\n");
    printf("==========================\n");
}

// Display heap
void Display(Heap h) {
    printf("{");
    for (int i = 0; i < h.count; i++) {
        printf("%d%c", h.elem[i], (i == h.count - 1) ? '}' : ',');
    }
    printf("\n");
}

// Populate heap from array
void Populate(Heap *h, int values[], int size) {
    for (int i = 0; i < size; i++) {
        h->elem[i] = values[i];
        h->count++;
    }
    printf("Populated the MaxHeap.\n");
    printf("==========================\n");
}

// Insert a new element into MaxHeap
void InsertMax(Heap *h, int newData) {
    if (h->count >= MAX) {
        printf("Heap is full.\n");
        return;
    }

    int child = h->count++;
    int parent = (child - 1) / 2;
    h->elem[child] = newData;

    while (parent >= 0 && h->elem[parent] < h->elem[child]) {
        int temp = h->elem[parent];
        h->elem[parent] = h->elem[child];
        h->elem[child] = temp;

        child = parent;
        parent = (child - 1) / 2;
    }
    printf("Successfully inserted %d into MaxHeap!\n", newData);
}

// Heapify subtree rooted at parent
void HeapifyMax(Heap *h, int parent) {
    int LC = 2 * parent + 1;
    int RC = 2 * parent + 2;
    int largest = parent;

    if (LC < h->count && h->elem[LC] > h->elem[largest]) largest = LC;
    if (RC < h->count && h->elem[RC] > h->elem[largest]) largest = RC;

    if (largest != parent) {
        int temp = h->elem[parent];
        h->elem[parent] = h->elem[largest];
        h->elem[largest] = temp;
        HeapifyMax(h, largest);
    }
}

// Build MaxHeap from any array
void BuildMaxHeap(Heap *h) {
    for (int parent = (h->count - 2) / 2; parent >= 0; parent--) {
        HeapifyMax(h, parent);
    }
    printf("MaxHeap built successfully.\n");
}

// Preorder traversal
void Preorder(Heap h, int index) {
    if (index < h.count) {
        printf("%d ", h.elem[index]);
        Preorder(h, 2 * index + 1);
        Preorder(h, 2 * index + 2);
    }
}

int main() {
    int values[] = {6, 7, 4, 3, 1, 2, 5, 8};
    int n = sizeof(values) / sizeof(values[0]);

    Heap harryPOTter;
    Initialize(&harryPOTter);
    Populate(&harryPOTter, values, n);

    printf("Initial heap array:\n");
    Display(harryPOTter);

    InsertMax(&harryPOTter, 10);
    printf("After inserting 10:\n");
    Display(harryPOTter);

    BuildMaxHeap(&harryPOTter);
    printf("After building MaxHeap:\n");
    Display(harryPOTter);

    printf("Preorder traversal: ");
    Preorder(harryPOTter, 0);
    printf("\n");

    return 0;
}

```
# Heapsort
Example (Ascending Order using Max-Heap)

Array: [4, 10, 3, 5, 1]

Build max-heap → [10, 5, 3, 4, 1]

Swap root with last element → [1, 5, 3, 4, 10]

Heapify root → [5, 4, 3, 1, 10]

Swap root with last element → [1, 4, 3, 5, 10]

Heapify root → [4, 1, 3, 5, 10]

Continue until heap size = 1

Final sorted array: [1, 3, 4, 5, 10]

# MinHeapify
MinHeapify(h, i) fixes the heap from node i downward.

# BuildMinHeap
BuildMinHeap(h) calls MinHeapify for all non-leaf nodes from bottom to top, ensuring the entire array becomes a heap.

# Insert
Insert fixes the heap from the new element upward (percolate up).

# 1️⃣ Heapify fixes only one subtree

Suppose you call Heapify (or MinHeapify/MaxHeapify) at one node.

It only ensures the heap property for that node and its descendants.

It does not automatically fix other parts of the heap that might be invalid above it.

Think of it like pushing the wrong node down the tree until its subtree is correct.

# 2️⃣ BuildHeap calls heapify from bottom to top

When you first build a heap from an array, some elements may already satisfy the heap property, but parents may violate it.

So BuildHeap calls Heapify on all non-leaf nodes, starting from the last parent and moving up to the root.

This ensures the entire array becomes a valid heap.

# ✅ Analogy
Heapify(node) = make sure the box at this level is correctly placed relative to the boxes below it.

BuildHeap = start from the bottom rows and fix each box upward so the whole pyramid is stable.

HeapSort = repeatedly remove the top box, replace it with the last box, and fix the pyramid again.
