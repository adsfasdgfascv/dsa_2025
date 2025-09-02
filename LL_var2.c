#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node * next;
} Node;

typedef struct{
    Node * head;
    int count;
} List;

List* initialize(); //
void empty(List *list); //
void insertFirst(List *list, int data); //
void insertLast(List *list, int data); //
void insertPos(List *list, int data, int index); // 
void deleteStart(List *list);//
void deleteLast(List *list);//
void deletePos(List *list, int index);//
int retrieve(List *list, int index);
int locate(List *list, int data);
void display(List *list);

int main(){

    List *newList = initialize();

    if(newList){
        printf("successful!");
    }

    empty(newList);

    insertFirst(newList, 7);
    insertFirst(newList, 2);
    insertFirst(newList, 7);
        printf("\nInsertFirst: ");
        display(newList);

    insertLast(newList, 99);
        printf("\nInsertLast: ");
        display(newList);

    insertPos(newList, 123, 1);
        printf("\nInsertPos: ");
        display(newList);

    deleteStart(newList);
        printf("\ndeleteStart: ");
        display(newList);

    deleteLast(newList);
        printf("\ndeleteLast: ");
        display(newList);

    deletePos(newList, 2);
        printf("\ndeletePos: ");
        display(newList);

    int data_1 = retrieve(newList, 2);
        printf("\nretrieve = %d", data_1);

    int loc= locate(newList, 99);
        printf("\nlocate = %d", loc);

    printf("\nFinal List: ");
    display(newList);

    return 0;
}

List* initialize(){
    List * hello = malloc(sizeof(List));

    if(!hello){
        printf("unsuccessful");
        return NULL;
    }

    hello->head = NULL;
    hello->count = 0;

    return hello;
}

void empty(List *list){
    
    Node * current = list->head;
    Node * tempDelete;

    while( current != NULL){
        tempDelete = current;
        current= current->next;
        free(tempDelete);
    }  

    //question: is it neccesary to set the main link to null?
    list->head = NULL;
    list->count = 0;
}

void insertFirst(List *list, int data){

    
    Node * newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = list->head;

    
    list->head = newNode;
    list->count++;
}

void insertLast(List *list, int data){

    Node * current = list->head;
    Node * newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next =NULL;

    if(list->head == NULL){
        list->head = newNode;
    }

    
    while(current->next != NULL){
        current = current->next;
    }

    current->next = newNode;
    list->count++;
}


void insertPos(List *list, int data, int index){

    if (index< 0){
        return;
    }
    else if (index == 0){
        insertFirst(list,data);
    }
    else if (index == list->count){
        insertLast(list, data);
    }
    else{
        Node * newNode = malloc(sizeof(Node));
        newNode->data = data;
        newNode->next = NULL;

        Node * current = list->head;
        for(int i = 0; i<index-1; i++){
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;

        list->count++;
    }

}


void deleteStart(List *list){

    Node * current = list->head;
    list->head = current->next;
    free(current);
    list->count--;
}

void deleteLast(List *list){

    if(list->head->next == NULL){
        free(list->head);
    }
    else{
        Node * current = list->head;
        while(current->next->next != NULL){
            current = current->next;
        }
        free(current->next);
        current->next = NULL;

        list->count--;
    }
}



void deletePos(List *list, int index){

    if(index == 0){
        deleteStart(list);
    }
    else{
        Node * current = list->head;
        for(int i=0; i<index-1; i++){
            current = current->next;
        }
        Node * temp = current->next;
        current->next = temp->next;
        free(temp);
        list->count--;
    }

}


int retrieve(List *list, int index){
    if(index > list->count){
        return 0;
    }
    
    Node * current = list->head;
    for(int i= 0;i< index; i++){
        current = current->next;
    }

    return current->data;
}



int locate(List *list, int data){
    
    if(list->head == NULL){
        return -1;
    }

    Node * current = list->head;

    int index = 0;
    while(current!= NULL){
        if(current->data == data){
            break;
        }
        index++;
        current = current->next;
    }

    return index;
}


void display(List *list){

    Node * current = list->head;
    while(current != NULL){
        printf("%d ", current->data);
        current = current->next;
        
    }
}





