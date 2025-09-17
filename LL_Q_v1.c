#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure for the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue structure with front and rear pointers
typedef struct Queue {
    Node* front;  // Points to the first node of the list
    Node* rear;   // Points to the last node of the list
} Queue;

// Initialize the queue
Queue* initialize() {
    // Allocate memory for the queue structure
    Queue* q = (Queue*)malloc(sizeof(Queue));
    
    // Initialize both front and rear pointers to NULL
    q->front = NULL;
    q->rear = NULL;
    
    // Return the pointer to the new queue
    return q;
}

// Check if queue is empty
bool isEmpty(Queue* q) {
    // Queue is empty if the front pointer is NULL
    return q->front == NULL;
}

// Check if queue is full
bool isFull(Queue* q) {
    // Return false (linked list can never be full)
    return false;
}

// Add element to the queue (enqueue)
void enqueue(Queue* q, int value) {
    // Allocate memory for a new node
    Node* newNode = (Node*)malloc(sizeof(Node));
    
    // Set the data of the new node and set its next pointer to NULL
    newNode->data = value;
    newNode->next = NULL;
    
    // Check if the queue is currently empty
    if (isEmpty(q)) {
        // If the queue is empty, the new node is both the front and the rear
        q->front = newNode;
        q->rear = newNode;
    } else {
        // If the queue is not empty, link the current rear to the new node
        q->rear->next = newNode;
        // Then, update the rear pointer to the new node
        q->rear = newNode;
    }
}

// Remove element from the queue (dequeue)
int dequeue(Queue* q) {
    // Check if the queue is empty before attempting to dequeue
    if (isEmpty(q)) {
        printf("Queue is empty! Cannot dequeue.\n");
        return -1; // Return error value
    }
    
    // Store a temporary pointer to the front node
    Node* temp = q->front;
    
    // Store the data of the front node
    int value = temp->data;
    
    // Move the front pointer to the next node
    q->front = q->front->next;
    
    // If the queue becomes empty after this operation, update the rear pointer to NULL
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    // Free the memory of the old front node
    free(temp);
    
    // Return the stored value
    return value;
}

// Get the front element without removing it
int front(Queue* q) {
    // Check if the queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty! No front element.\n");
        return -1; // Return error value
    }
    
    // Otherwise, return the data of the front
    return q->front->data;
}

// Display all elements in the queue
void display(Queue* q) {
    // Check if the queue is empty
    if (isEmpty(q)) {
        printf("Queue is empty!\n");
        return;
    }
    
    printf("Queue: ");
    // Create a temporary pointer to traverse the queue
    Node* temp = q->front;
    
    // Loop through the list until the end (NULL) is reached
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Free the entire queue
void freeQueue(Queue* q) {
    while (!isEmpty(q)) {
        dequeue(q);
    }
    free(q);
}

// Main function for testing
int main() {
    // Initialize queue
    Queue* Q = initialize();
    
    // Test operations
    printf("Is queue empty? %s\n", isEmpty(Q) ? "Yes" : "No");
    printf("Is queue full? %s\n", isFull(Q) ? "Yes" : "No");
    
    // Enqueue some elements
    enqueue(Q, 1);
    enqueue(Q, 3);
    enqueue(Q, 5);
    display(Q);
    
    // Enqueue another element (as shown in the example)
    enqueue(Q, 4);
    display(Q);
    
    // Get front element
    printf("Front element: %d\n", front(Q));
    
    // Dequeue an element
    int value = dequeue(Q);
    printf("Dequeued: %d\n", value);
    display(Q);
    
    // Free the queue
    freeQueue(Q);
    
    return 0;
}
