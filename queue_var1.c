#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
    int items[MAX];
    int count;
}List;

typedef struct{
    List list;
    int front;
    int rear;
} Queue;

Queue* initialize();
void enqueue(Queue* q, int value);
void display(Queue* q);
int dequeue(Queue* q);
int front(Queue* q);




int main(){
    
    Queue* q = initialize();
    enqueue(q, 11);
    enqueue(q, 12);
    enqueue(q, 12);
    enqueue(q, 23);
    
    int re = dequeue(q);
    printf("dequed: %d\n", re);
    
    re = front(q);
    printf("front: %d\n", re);


    display(q);
}





Queue* initialize(){
    
    Queue * abc = malloc(sizeof(Queue));
    abc->list.count = 0;
    abc->front = -1;
    abc->rear = -1;
    
    return abc;
}


void enqueue(Queue* q, int value){
    
    if(q->list.count == MAX){
        return;
        //this is FULL
    }
    else if(q->list.count == 0){
        q->front = 0;
        q->rear = 0;
        // EMPTY
    }
    else{
        q->rear = (q->rear+1) % MAX;
    }
    q->list.items[q->rear] = value;
    q->list.count++;
}



int dequeue(Queue* q){
    
    int front = q->list.items[q->front];
    
    if(q->list.count == 0){
        return -1;
        //this is FULL
    }
    else if(q->list.count == 1){
        q->front = -1;
        q->rear = -1;
        //last element
    }
    else{
        q->front = (q->front+1) % MAX;
    }
    q->list.count--;
    
    return front;
    
}
int front(Queue* q){
    if(q->list.count == 0){
        return -1;
        //this is FULL
    }
    return q->list.items[q->front];
    
}




void display(Queue* q){
    
    printf("Queue List: ");
    int j = q->front;
    for(int i = 0; i<q->list.count; i++){
        printf("%d ", q->list.items[j]);
        j = (j+1)%MAX;
    }
    
}

