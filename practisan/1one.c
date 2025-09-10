/***************************************************************
 *  Author:  Mark anthony gabieta
 *  Date:    10/9/25
 *
 *  Description:
 *  This program solves LeetCode Problem 946: Validate Stack Sequences.
 *  Given two integer arrays (pushed and popped) with distinct values,
 *  the function validateStackSequences() determines whether the
 *  sequence in "popped" can be obtained by performing push and pop
 *  operations on an initially empty stack, following the order in "pushed".
 *
 *  
 *
 ***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000

typedef struct{
    int arr[MAX];
    int top;
} Stack;

Stack * initialize();

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize);
void push(Stack *s, int val);

void push(Stack *s, int val);

void pop(Stack *s);

bool isEmpty(Stack * s);

int peek(Stack * s);

Stack * initialize();



int main(){
    

    
    int pushed1[] = {1,2,3,4,5};
    int popped1[] = {4,5,3,2,1};
    int size1 = 5;
    
    int pushed2[] = {1,2,3,4,5};
    int popped2[] = {4,3,5,1,2};
    int size2 = 5;
    
    printf("Example 1: %s\n", validateStackSequences(pushed1, size1, popped1, size1) ? "true" : "false");
    printf("Example 1: %s\n", validateStackSequences(pushed2, size2, popped2, size2) ? "true" : "false");

    
    return 0;
    
}




void push(Stack *s, int val){
    s->arr[++s->top] = val;
}

void pop(Stack *s){
    s->arr[s->top--];
}

bool isEmpty(Stack * s){
    return s->top == -1;
}

int peek(Stack * s){
    return s->arr[s->top];
}

Stack * initialize(){
    Stack * one = malloc(sizeof(Stack));
    one->top = -1;
    return one;
}

bool validateStackSequences(int* pushed, int pushedSize, int* popped, int poppedSize){
    
    Stack * s = initialize();
    
    if(s->top == -1){
        printf("ok");
    }
    
    int j = 0;
    for (int i = 0; i < pushedSize; i++) {
        push(s, pushed[i]);

       while(!isEmpty(s) && j<poppedSize && peek(s) == popped[j]){
           pop(s);
           j++;
       }
    }

    return isEmpty(s);
    
}