/*
Title : POT ID#101
Documentation Header File : <put your filename here>.c 
Author : <Your Name> Date : Mon, Nov 17, 2025 (UTC) 
Build : gcc -std=c11 -Wall -Wextra -O2 <file>.c -o pot_demo Run : ./pot_demo

Overview
    implements: POT represented as a binary min-heap stored in an array.
    Each node is a student record;
    priority is the numeric grade (lower grade = higher priority).
    The minimum grade is always at the root (index 0).
    The heap is stored in a flat array using the standard complete-binary-tree index mapping: parent = (i - 1) / 2; left child = 2i + 1; right child = 2i + 2 


Objectives
    Maintain a priority queue of students keyed by grade (min-heap/POT) 


Support efficient operations:
    Insert (up-heapify) in O(log n) (minimum)
    deleteMin (down-heapify) in O(log n) 
    Peek min in O(1).
    Provide simple display and duplicate-ID protection (linear scan by idNum).
    Demonstrate correct array index arithmetic for parent/children 

TO implement:
    InsertMax (up-heapify)
    DeleteMax (down-heapify)


Data Structures

    Key Operations and Algorithms
        insertPOT(P, info):
            Reject if a duplicate idNum exists (linear scan).
            Append new element at lastNdx + 1.
            Up-heapify: bubble up while parent.grade > child.grade
        
        deleteMin(P):
            Remove and return root (min).
            Move last element to root.
            Down-heapify: repeatedly swap with the smaller child until the min-heap property is restored 
        
        display(P): prints the array in level order for quick inspection.
            Index Relationships (array-based complete binary tree) 
            Parent(i) = (i - 1) / 2
            Left(i) = 2*i + 1
            Right(i) = 2*i + 2
    
    Complexity
        Insert: O(log n) due to up-heapify; duplicate check adds O(n) linear scan.
        deleteMin: O(log n) due to down-heapify.
        Peek min: O(1).
        Display: O(n).
        Space: O(MAX) for the backing array.
        Assumptions and Invariants
        The array models a complete binary tree (no holes) 


Min-heap property: for every index i > 0, data[parent(i)].grade <= data[i].grade 

MAX defines fixed capacity. Calls to insert beyond capacity should be rejected or require dynamic growth (not mandatory in this version).
Duplicate prevention uses idNum equality (strcmp == 0).
Ties on grade: no secondary ordering guaranteed (non-stable heap).



Testing Tips
Insert values in ascending, descending, and random grade order; ensure root is always the minimum.
Repeatedly deleteMin until empty; the sequence of removed grades should be nondecreasing.
Include duplicate idNum to verify duplicate detection path.
Possible Extensions
Dynamic resizing (grow array when full).
Secondary key for stable tie-breaking (e.g., idNum).
Hash set for O(1) duplicate detection.
================================================================================ End of Documentation Header
*/



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX 20

typedef struct name{
    char fname[50];
    char mi;
    char lname[50];
}studName;

typedef struct student{
    char idNum[10];
    studName name;
    int grade;
}student;

typedef struct node{
    student * data;
    int lastNdx;
}POT;

// Lifecycle
void pot_init(POT* P);  // 
void pot_free(POT* P); 

//COre functions
void insertPOT(POT *P, student info); 
void generateStudent(POT *P); //
student deleteMin(POT *P); //
void display(POT *P);

//Queries
int pot_is_empty(const POT* P);
int pot_is_full(const POT* P);
int pot_size(const POT* P);
const student* pot_min(const POT* P);


int main(){
    POT P;
    pot_init(&P);
    
    generateStudent(&P);
    display_tree(&P); 
    
    student del = deleteMin(&P);
    
    display_tree(&P); 
  return 0;
}






void pot_init(POT* P){
    if(P == NULL) return;
    
    P->data = malloc(sizeof(student) * MAX);
    if(P->data == NULL){
        printf("Allocation failed. enkkkk");
        return;
    }
    P->lastNdx = -1;
}

void generateStudent(POT *P){
    student stud[] = {
    {"STUD1008", {"Olivia", 'B', "Hernandez"}, 123},
    {"STUD1001", {"John", 'R', "Doe"}, 128},
    {"STUD1020", {"Lily", 'N', "Tanaka"}, 255},
    {"STUD1004", {"Joey", 'K', "Lee"}, 207},
    {"STUD1002", {"Jane", 'L', "Smith"}, 217},
    {"STUD1005", {"Michael", 'T', "Garcia"}, 36},
    {"STUD1008", {"Olivia", 'B', "Hernandez"}, 123},
    {"STUD1003", {"Mark", 'S', "Johnson"}, 130},
    {"STUD1010", {"Mia", 'D', "Nguyen"}, 89},
    {"STUD1011", {"Ethan", 'E', "Perez"}, 130},
    {"STUD1021", {"Elijah", 'O', "Yamamoto"}, 36},
    {"STUD1017", {"Daniel", 'K', "Cruz"}, 128},
    {"STUD1019", {"Noah", 'M', "Reyes"}, 130},
    {"STUD1012", {"Chung", 'F', "Tan"}, 231},
    {"STUD1013", {"Alexander", 'G', "Reyes"}, 44},
    {"STUD1014", {"Sofia", 'H', "Wong"}, 149},
    {"STUD1015", {"Benjamin", 'I', "Liu"}, 202},
    {"STUD1016", {"Chloe", 'J', "Gonzales"}, 59},
    {"STUD1018", {"Garret", 'L', "Santos"}, 73},
    {"STUD1029", {"Gabriel", 'W', "Nguyen"}, 108},
    };
    
    
    for(int i=0; i<MAX; i++){
        insertPOT(P,stud[i]);
    }
}


void insertPOT(POT *P, student info){
    
    int i = 0; //traveral
    int Pndx = 0; //parent
    int Cndx = 0; //child
    
    //finds duplication
    for( ; i<= P->lastNdx && strcmp(P->data[i].idNum, info.idNum) != 0; i++){}
    
    if(i > P->lastNdx){
        P->lastNdx++;
        Cndx = P->lastNdx;
        Pndx = (Cndx-1)/2;

        if(Pndx >= 0){
            while(Cndx != 0 && P->data[Pndx].grade > info.grade){
                P->data[Cndx] = P->data[Pndx];
                Cndx = Pndx;
                Pndx = (Cndx -1)/2;
            }
        }
        P->data[Cndx] = info;
    }else{
        printf("Cannot insert, %s already exists.\n", info.name.fname);
    }
}

student deleteMin(POT *P){
    student min;
    int ndx = 0;
    
    if(P->lastNdx == -1){
        printf("Heap is empty.\n");
        return (student){"", {"", ' ', ""}, -1};
    }
    
    
    min = P->data[0];   //save the min
    P->data[0] = P->data[P->lastNdx];   //moves the last element to the root
    P->lastNdx--;
        
    while(1){
        int left = 2*ndx+1;
        int right = 2*ndx +2;
        int smallest = ndx;
        
        if(left <= P->lastNdx && P->data[left].grade < P->data[smallest].grade){
            smallest = left;
        } 
        
        if(right <= P->lastNdx && P->data[right].grade < P->data[smallest].grade){
            smallest = right;
        } 
        
        if(smallest == ndx){    //if ndx is already smallest
            break;
        }
        
        student temp = P->data[ndx];
        P->data[ndx] = P->data[smallest];
        P->data[smallest] = temp;

        ndx = smallest;  // Move down
        
        
    }
    
    return min;
}
















// Helper: safe repeat spaces
static void print_spaces(int n) {
    for (int i = 0; i < n; ++i) putchar(' ');
}

// Optional: a compact level-order dump (indices and grades)
void display_table(const POT* P) {
    if (!P || P->lastNdx < 0) { puts("(empty heap)"); return; }
    printf("\nLevel-order (index: [grade])\n");
    for (int i = 0; i <= P->lastNdx; ++i) {
        printf("%d:[%d]%s", i, P->data[i].grade, (i == P->lastNdx ? "\n" : "  "));
    }
}

// Visual tree like:
//           [36]
//          /    \
//       [44]   [73]
//      /   \   /   \
//   [59] [89][108] [130]
void display_tree(const POT* P) {
    if (!P || P->lastNdx < 0) {
        puts("\n(empty heap)\n");
        return;
    }

    const int n = P->lastNdx + 1;
    const int NODEW = 5;       // "[%3d]" is 5 chars wide
    const int GAP    = 2;      // base space unit between cells

    // Compute height h such that 2^h - 1 >= n
    int h = 0, cap = 1;
    while (cap - 1 < n) { h++; cap <<= 1; }

    // Total printable width in columns (characters) for the bottom level
    const int maxNodesLast = 1 << (h - 1);
    const int lineWidth = (NODEW + GAP) * maxNodesLast - GAP;

    char* line = (char*)malloc((size_t)lineWidth + 1);
    if (!line) { perror("malloc"); return; }

    printf("\n"); // leading blank line

    for (int level = 0; level < h; ++level) {
        int nodesOnLevel = 1 << level;
        int startIndex = nodesOnLevel - 1;
        int endIndex = startIndex + nodesOnLevel - 1;
        if (startIndex > P->lastNdx) break;

        // Node centers for this level are placed evenly across lineWidth
        // center(k) = lineWidth * (2k+1) / (2*nodesOnLevel)
        memset(line, ' ', (size_t)lineWidth);
        line[lineWidth] = '\0';

        for (int k = 0; k < nodesOnLevel; ++k) {
            int idx = startIndex + k;
            if (idx > P->lastNdx) break;

            int center = (lineWidth * (2 * k + 1)) / (2 * nodesOnLevel);
            char label[NODEW + 1];
            // fixed width label so alignment is stable
            snprintf(label, sizeof(label), "[%3d]", P->data[idx].grade);

            int start = center - NODEW / 2;
            if (start < 0) start = 0;
            if (start + NODEW > lineWidth) start = lineWidth - NODEW;

            for (int c = 0; c < NODEW; ++c) line[start + c] = label[c];
        }
        puts(line);

        // Connector line (slashes to hint children positions)
        if (level < h - 1) {
            memset(line, ' ', (size_t)lineWidth);
            line[lineWidth] = '\0';

            int nextNodes = nodesOnLevel << 1;
            for (int k = 0; k < nodesOnLevel; ++k) {
                int idx = startIndex + k;
                if (idx > P->lastNdx) break;

                int center = (lineWidth * (2 * k + 1)) / (2 * nodesOnLevel);

                int leftIdx  = 2 * idx + 1; // children indices in array [[11]]
                int rightIdx = 2 * idx + 2; // [[11]]

                // Compute child centers for the next level
                int leftCenter  = (lineWidth * (2 * (2 * k) + 1)) / (2 * nextNodes);
                int rightCenter = (lineWidth * (2 * (2 * k + 1) + 1)) / (2 * nextNodes);

                if (leftIdx <= P->lastNdx) {
                    int pos = (center + leftCenter) / 2;
                    if (pos >= 0 && pos < lineWidth) line[pos] = '/';
                }
                if (rightIdx <= P->lastNdx) {
                    int pos = (center + rightCenter) / 2;
                    if (pos >= 0 && pos < lineWidth) line[pos] = '\\';
                }
            }
            puts(line);
        }
    }

    free(line);
    printf("\nlastNdx = %d, size = %d\n\n", P->lastNdx, n);
    
    
    
    int i;
    printf("\n");
    for(i = 0; i <= P->lastNdx; i++){
        printf("Index: %d - Parent:%d - %s %s %s %d\n", i,(i - 1)/2,P->data[i].idNum,P->data[i].name.fname, P->data[i].name.lname, P->data[i].grade);
    }

    printf("\n\n\n\n");
}






