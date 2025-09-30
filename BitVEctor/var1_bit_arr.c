#include <stdio.h>
#include <stdbool.h>

#define MAX 100
typedef struct{
    int content[MAX];
    int count;
}SET_arr;

typedef struct node {
    int data;
    struct node *next;
} dtype, *LinkedSET;


//ARRAY
void initialize(SET_arr * set) {
    set->count =0;
}

void insert(SET_arr * set, int element) {
    if(element< 0 || element >=8 || set->count >= 8) return;
    
    for(int i =0;i<set->count; i++){
        if(set->content[i] == element) return;
    }
    set->content[set->count++] = element;
}

void delete(SET_arr * set, int element) {
    // mask = 1 << 3 = 00001000
    // ~mask = 11110111
    // mySet = 00001010 & 11110111 = 00000010
    // Set now contains {1}
    if(element< 0 || element >=8 || set->count >= 8) return;
    
    for(int i =0;i<set->count; i++){
        if(set->content[i] == element){
            for(int j = i;j< set->count; j++){
                set->content[j] = set->content[j+1];
            }
            set->count--;
            return;
        }
    }
    
    
}

bool find(SET_arr set, int element) {
    
    if(element< 0 || element >=8 || set.count >= 8) return false;

    for(int i =0;i<set.count; i++){
        if(set.content[i] == element) return true;
    }
    
    return false;
}

SET_arr Sunion(SET_arr A, SET_arr B) {
    
    SET_arr newSet;
    initialize(&newSet);
    
    
    for(int i =0;i<A.count; i++){
        insert(&newSet, A.content[i]);
    }
    
    for(int i =0;i<B.count; i++){
        if(!find(A, B.content[i])){
            insert(&newSet, B.content[i]);
        }
    }
    
    return newSet; 
}

SET_arr intersection(SET_arr A, SET_arr B) {
    SET_arr newSet;
    initialize(&newSet);
    
    
    for(int i =0;i<A.count; i++){
        if(find(B, A.content[i])){
            insert(&newSet, A.content[i]);
        }
    }
    
    return newSet; 
}

SET_arr difference(SET_arr A, SET_arr B) {
    SET_arr newSet;
    initialize(&newSet);
    
    for(int i =0;i<A.count; i++){
        if(!find(B, A.content[i])){
            insert(&newSet, A.content[i]);
        }
    }
    
    return newSet; 
}

void display(SET_arr A) {
    printf("{");
    for(int i=0;i<A.count; i++){
        printf("%d", A.content[i]);
        if(i<A.count-1){
            printf(", ");
        }
    }
    printf("}");
}


int main(){
    
    SET_arr A;
    initialize(&A);
    insert(&A,1);
    insert(&A,3);
    insert(&A,7);
    
    display(A);
    
    return 0;
}
