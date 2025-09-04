#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct{
	int items[MAX];
	int top;
}Stack;

Stack * initialize();
void push(Stack* s, int value);
int pop(Stack* s);
int peek(Stack* s);
void display(Stack* s);



int main(){
	
	Stack* S = initialize();

	push(S, 66);
	push(S, 26);
	push(S, 63);
	push(S, 32);
	pop(S);
	peek(S);
	display(S);

}

Stack * initialize(){
	Stack * hello = malloc(sizeof(Stack));
	hello->top = -1;
	
	return hello;
}

void push(Stack* s, int value){
	if(s->top == MAX-1){
		printf("Stack Overflow! Cannot push %d\n", value);
        return;
	}

	s->items[++(s->top)] = value;
    printf("%d pushed to stack\n", value);
}

int pop(Stack* s){
	if(s->top == -1){
		printf("Stack EMPTY\n");
		return -1;
	}

	return s->items[(s->top)--];
}

int peek(Stack* s){

	if(s->top ==-1){
		printf("Stack EMPTY\n");
	}

	return s->items[s->top];
}

void display(Stack* s){
	if(s->top ==-1){
		printf("Stack EMPTY\n");
	}

	printf("\nStack: ");
	for(int i= s->top; i>=0; i--){
		printf("%d ", s->items[i]);
	}

}