#include <stdio.h>
#include <stdlib.h>
#define MAX 50

typedef struct{
    int elem[MAX];
    int count;
} List;

List initialize(List L);
List insertPos(List L, int data, int position);
List deletePos(List L, int position);
int locate(List L, int data);
List insertSorted(List L, int data);
void display(List L);


int main(){
    List L = {{1,2,3,4,5}, 5};
    List huh;


    huh = initialize(L);
    if(huh.count == 0){
        printf("waw bery gud, zero ung count sana di din 0 ang score");
    }

    printf("\n\nInserT:\n");
    huh = insertPos(L, 69, 3);
    display(huh);

    printf("\n\ndel\n");
    huh =  deletePos(huh, 3);
    display(huh);


    printf("\n\n-1:\n");
    int result = locate(L, 4);
    if(result == -1){
        printf("waw bery gud, -1 ung count sana di din -1 ang score");
    }

    printf("\n\ninsertSort\n");
    huh = insertSorted(huh, 2);
    display(huh);


    return 0;
}

List initialize(List L){
    L.count = 0;

    return L;
}

List insertPos(List L, int data, int position){

    for(int i=L.count; i> position; i--){
        L.elem[i] = L.elem[i-1];
    }
    L.elem[position] = data;
    L.count++;

    return L;
}



List deletePos(List L, int position){
    for(int i = position; i < L.count; i++){
        L.elem[i] = L.elem[i+1];
    }

    L.count--;
    return L;
}

int locate(List L, int data){

    int re =0;
    for(int i=0; L.elem[i] != data; i++){
        if(L.elem[i] == data){
            break;
        }
        else{
            re = -1;
        }
    }
    return re;
}

List insertSorted(List L, int data){
    int temp = 0;

    L.elem[L.count] = data;
    L.count++;

    for(int i = 0; i< L.count; i++){
        for(int j = i+1; j < L.count; j++){
            if(L.elem[i] > L.elem[j]){
                temp = L.elem[j];
                L.elem[j] = L.elem[i];
                L.elem[i] = temp; 
            }
        }
    }

    return L;
}

void display(List L){

    for(int i= 0;i< L.count ; i++){
        printf("%d = %d\n", i+1, L.elem[i]);
    }


}