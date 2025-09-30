#include <stdio.h>
#include <stdbool.h>



void initialize(unsigned char *set) {
    *set = 0;
}

void insert(unsigned char *set, int element) {
    if(element <0 || element>=8) return;
    unsigned char mask = 1 << element;
    *set |= mask; 
}

void delete(unsigned char *set, int element) {
    // mask = 1 << 3 = 00001000
    // ~mask = 11110111
    // mySet = 00001010 & 11110111 = 00000010
    // Set now contains {1}
    if(element <0 || element>=8) return;
    unsigned char mask = 1 << element;
    *set &= ~mask;
    
}

bool find(unsigned char set, int element) {
    if(element <0 || element>=8) return false;
    unsigned char mask = 1 << element;
    return (mask & set) != 0;
}

unsigned char Sunion(unsigned char A, unsigned char B) {
    return A|B;
}

unsigned char intersection(unsigned char A, unsigned char B) {
    return A&B;
}

unsigned char difference(unsigned char A, unsigned char B) {
    return A&~B;
}

void display(unsigned char set) {
    printf("{");
    int first = 1;
    for(int i=0;i<8;i++){
        if(set & (1<<i)){
            if(!first) printf(", ");
            printf("%d", i);
            first = 0;
        }
    }
    printf("}\n");
}


int main(){
    
    unsigned char A;
    initialize(&A);
    insert(&A,1);
    insert(&A,3);
    insert(&A,7);
    
    display(A);
    
    return 0;
}
