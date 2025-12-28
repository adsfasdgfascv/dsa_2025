#include <stdio.h>
#include <stdlib.h>

#define MAX 10

//min heap

typedef struct heap {
    int elem[MAX];
    int count;
} Heap;

void Insert(Heap *h, int value);
void MinHeapifyNDX(Heap *h, int index);
int DeleteMin(Heap *h);

int main() {
    int arr[] = {6, 7, 4, 3, 1, 2, 5, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    Heap hephephoray;
    //Initialize
    hephephoray.count = 0;
    
    for(int i=0;i<n; i++){
        Insert(&hephephoray, arr[i]);
    }
    

    printf("Original array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    
    //sorts at a specific index
    for(int i=0;i<n; i++){
        MinHeapifyNDX(&hephephoray, 0);
    }

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", hephephoray.elem[i]);
    printf("\n");
    
    
    int del = DeleteMin(&hephephoray);
    printf("array after deletion:\n");
    for (int i = 0; i < hephephoray.count; i++)
        printf("%d ", hephephoray.elem[i]);
    printf("\n");

    return 0;
}

void Insert(Heap *h, int value){
    
    
    //find dupes
    for(int i= 0;i<h->count; i++){
        if(h->elem[i] == value) return;
    }
    
    int cNdx = h->count;
        h->count++; // accomodate for the new elem by giving extra space int hte Heap

    int pNdx = (cNdx -1) /2;
    while(cNdx > 0 && h->elem[pNdx] > value){
        h->elem[cNdx] = h->elem[pNdx];
        cNdx = pNdx;
        pNdx =(cNdx -1)/2;
    }
    h->elem[cNdx] = value; 
}

void MinHeapifyNDX(Heap *h, int index){
    int smallest = index;
    int left = 2 * index +1; //left child of index
    int right = 2 * index +2;//right child of index
    
    if(left < h->count && h->elem[left] < h->elem[smallest]) smallest = left; //check existence of left node
    if(right < h->count && h->elem[right] < h->elem[smallest]) smallest = right; //check existence of right node and check if it min to arr[ndx]
    
    //swap it
    if(smallest != index){
        int temp = h->elem[index];
        h->elem[index] = h->elem[smallest];
        h->elem[smallest] = temp;
        MinHeapifyNDX(h, smallest); //recursion
    }
}

// --- MIN HEAP DELETE (Down-Heapify, Optimized Shifting Method) ---
int DeleteMin(Heap *h) {
    if (h->count == 0) {
        printf("Heap is empty.\n");
        return -1;
    }
    
    int min = h->elem[0];
    h->elem[0] = h->elem[h->count-1];
    h->count--;
    
    // restore min heap
    if(h->count >0){
        MinHeapifyNDX(h, 0);
    }
    return min;
}

