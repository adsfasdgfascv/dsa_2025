#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int front;
    int rear;
} Queue;


Queue* initialize();
int isEmpty(Queue* q);
int isFull(Queue* q);
void enqueue(Queue* q, int value);
void display(Queue* q);
int dequeue(Queue* q);
int front(Queue* q);



int main(){
    
    Queue* q = initialize();
    enqueue(q, 23);
    enqueue(q, 32);
    enqueue(q, 22);
    enqueue(q, 11);
    enqueue(q, 43);
    enqueue(q, 2);
    int re = dequeue(q);
    printf("dequed: %d\n", re);
     re = front(q);
    printf("front: %d\n", re);
    display(q);
}



Queue* initialize(){
    
    Queue * init = malloc(sizeof(Queue));
    init->front = 1;
    init->rear = 0;
    
    return init;
}

int isFull(Queue* q){
    if(q->front == (q->rear+2)%MAX){
      return -1;  
    }
}

int isEmpty(Queue* q){
    if(q->front == (q->rear+1)%MAX){
        return -1;
    }
}


void enqueue(Queue* q, int value){
    if(isFull(q)){
        return;
    }
    q->rear = (q->rear +1)%MAX;
    q->items[q->rear] = value;
}

int dequeue(Queue* q){
    if(isEmpty(q)){
        return -1;
    }
    int front = q->items[q->front];
    q->front = (q->front+1)%MAX;
    
    return front;
}

int front(Queue* q){
    if(isEmpty(q)){
        return -1;
    }
    return q->items[q->front];
}



void display(Queue* q){
    
    if(q->front == (q->rear+1)%MAX){
        return;
    }
    else{
        int i = q->front;
        while(i != (q->rear +1)%MAX){
            printf("%d ", q->items[i]);
            i = (i+1)%MAX;
        }
    }
}



