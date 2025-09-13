/*************************************************************
 *  Stack - Linked List - MRS. PENA version
 *  Author: Gabieta, Mark anthony
 *  Description: variation 1 of task on LL Stack(https://docs.google.com/document/d/1_WIU29-mjL6CG7RVyqoHnA2JGZfeRqP7Xk5ze5VLtLw/edit?tab=t.t3auwgq2s2xn)
 *  Course: BSIS -2
 *  Date:   13/09/25
 *************************************************************/
 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
} Tops, *Top;

Top initialize();//
bool isEmpty(Top s);//
void push(Top* s, int data);//
int pop(Top* s);//
int peek(Top s);
void display(Top s);

int main(){
    
    Top s = initialize();
    
    push(&s, 32);
    push(&s, 23);
    push(&s, 5);
    push(&s, 45);
    push(&s, 76);
    int result = peek(s);
    printf("result: %d\n", result);
    result = pop(&s);
    printf("popped: %d\n", result);

    push(&s, 2);
    
    display(s);
    
    return 0;
}

Top initialize(){
    Top s = malloc(sizeof(Tops));
    s = NULL;
    return s;
}

void push(Top *s, int data){
    Top n_Node = malloc(sizeof(Tops));
    n_Node->data = data;
    n_Node->next = *s;
    *s = n_Node;
}

int pop(Top* s){
    if(isEmpty(*s)){
        printf("Stack underflow");
        return -1;
    }
    
    Top temp = *s;
    int data = temp->data;
    *s = temp->next;
    free(temp);
    
    return data;
}


bool isEmpty(Top s){
    return s == NULL;
}

int peek(Top s){
    return s->data;
}

void display(Top s){
    while(s != NULL){
        printf("%d ", s->data);
        s = s->next;
    }
    
}



