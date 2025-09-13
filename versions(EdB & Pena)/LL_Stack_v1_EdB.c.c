/*************************************************************
 *  Stack - Linked List - MR. EDWIN BARTLETT
 *  Author: Gabieta, Mark anthony
 *  Description: variation 1 of task on LL Stack(https://docs.google.com/document/d/1_WIU29-mjL6CG7RVyqoHnA2JGZfeRqP7Xk5ze5VLtLw/edit?tab=t.t3auwgq2s2xn)
 *  Course: BSIS -2
 *  Date:   13/09/25
 *************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct Node{
    int data;
    struct Node* next;
}Node;

typedef struct Stack{
    Node * top;
}Stack;

Stack* initialize();//
bool isFull(Stack* s);//
bool isEmpty(Stack* s);//
void push(Stack* s, int value);//
int pop(Stack* s);//
int peek(Stack* s);
void display(Stack* s);


int main(){
    
    Stack * ok = initialize();
    
    push(ok, 32);
    push(ok, 23);
    push(ok, 5);
    push(ok, 45);
    push(ok, 76);
    int result = peek(ok);
    printf("result: %d\n", result);
    result = pop(ok);
    printf("result: %d\n", result);

    push(ok, 2);
    
    display(ok);
    
    return 0;
}





Stack * initialize(){
    Stack * LL_stack = malloc(sizeof(Stack));
    LL_stack->top = NULL;
    
    return LL_stack;
}

bool isFull(Stack* s){
    return false; //bc its never full
}

bool isEmpty(Stack* s){
    return s->top == NULL;
}

void push(Stack* s, int value){
    Node * newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = s->top;
    s->top = newNode;
}

int pop(Stack* s){
    if(isEmpty(s)){
        printf("stack underflow");
        return -1;
    }
    
    Node * temp = s->top;
    int data = s->top->data;
    s->top = temp->next;
    free(temp);
    
    return data;
}

int peek(Stack* s){
    if(isEmpty(s)){
        printf("stack underflow");
        return -1;
    } 
    else{
        return s->top->data;
    }
}

void display(Stack* s){
    if(isEmpty(s)){
        printf("stack underflow");
    } 
    else{
        Node * temp = s->top;
        while(temp != NULL){
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}
