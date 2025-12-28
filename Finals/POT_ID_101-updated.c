#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX 20

typedef struct name{
    char fname[50];
    char mi;
    char lname[50];
} studName;

typedef struct student{
    char idNum[10];
    studName name;
    int grade;
} student;

typedef struct node{
    student * data;
    int lastNdx;
} POT;

// --- Lifecycle & Core Min-Heap Functions ---
void pot_init(POT* P); 
void pot_free(POT* P); 

void insertMinPOT(POT *P, student info); // Implements Min-Heap Insert (Up-Heapify)
student deleteMin(POT *P);               // Implements Min-Heap Delete (Down-Heapify, Optimized Shift)


// --- Queries & Utilities ---
void generateStudent(POT *P); 
int  pot_is_empty(const POT* P);
int  pot_is_full(const POT* P);
int  pot_size(const POT* P);
const student* pot_min(const POT* P); // Peek O(1)
void display_tree(const POT* P);
void display_student(const student* s, const char* label);
static void minHeapify(POT *P, int index); // implemented but not used by deleteMin

int main(){
    POT minHeap;
    pot_init(&minHeap);
    
    printf("========================================================\n");
    printf("               MIN-HEAP PRIORITY QUEUE                  \n");
    printf("========================================================\n");
    
    generateStudent(&minHeap);
    printf("\n--- Initial Min-Heap Construction ---\n");
    display_tree(&minHeap); 
    
    // --- Min-Heap Testing ---
    student del_min_a = deleteMin(&minHeap);
    printf("Deleted Minimum (Highest Priority):\n");
    display_student(&del_min_a, "Removed Min");
    
    printf("\n--- Min-Heap After Deletion ---\n");
    display_tree(&minHeap); 
    
    student del_min_b = deleteMin(&minHeap);
    printf("Deleted Minimum (Next Highest Priority):\n");
    display_student(&del_min_b, "Removed Min");
    
    pot_free(&minHeap);
    
    return 0;
}

// ==========================================
//           CORE HEAP IMPLEMENTATIONS
// ==========================================

void pot_init(POT* P){ 
    if(P == NULL) return;
    
    P->data = (student*) malloc(sizeof(student) * MAX);
    if(P->data == NULL){
        printf("Allocation failed.\n");
        P->lastNdx = -1;
        return;
    }
    P->lastNdx = -1;
}

void pot_free(POT* P) {
    if (P != NULL && P->data != NULL) {
        free(P->data);
        P->data = NULL;
        P->lastNdx = -1;
    }
}

int pot_is_empty(const POT* P) {
    return (P == NULL || P->lastNdx == -1);
}

// FIXED: must use && instead of ||
int pot_is_full(const POT* P){
    return (P != NULL && P->lastNdx == MAX-1);
}

int pot_size(const POT* P){
    if (!P) return 0;
    return P->lastNdx + 1;
}

const student* pot_min(const POT* P){
    if (pot_is_empty(P)) return NULL;
    return &P->data[0];
}

void insertMinPOT(POT *P, student info){
    if(pot_is_full(P)) {
        printf("Cannot insert %s: Heap is full.\n", info.name.fname);
        return;
    }
    
    // finds duplicate
    for(int i = 0; i <= P->lastNdx; i++){
        if(strcmp(P->data[i].idNum, info.idNum) == 0){
            return;
        }
    }

    P->lastNdx++;
    int Cndx = P->lastNdx;
    int Pndx = (Cndx-1)/2;

    // up-heapify by grade
    while(Cndx > 0 && P->data[Pndx].grade > info.grade){
        P->data[Cndx] = P->data[Pndx];
        Cndx = Pndx;
        Pndx = (Cndx-1)/2;
    }
    P->data[Cndx] = info;
}


// --- MIN HEAP DELETE (Down-Heapify, Optimized Shifting Method) ---
student deleteMin(POT *P){
    if (pot_is_empty(P)) {
        printf("Heap is empty.\n");
        return (student){"", {"", ' ', ""}, -1};
    }
    
    student min = P->data[0]; 
    student lastElement = P->data[P->lastNdx]; 
    P->lastNdx--;
    
    if (P->lastNdx < 0) {
        // only one element was present
        return min;
    }
    
    int Cndx = 0;
    int child = 1; 
    
    while (child <= P->lastNdx) {
        // pick the smaller child
        if (child < P->lastNdx && P->data[child + 1].grade < P->data[child].grade) {
            child++; 
        }

        // if lastElement is already in correct position
        if (lastElement.grade <= P->data[child].grade) {
            break; 
        }

        // move child up
        P->data[Cndx] = P->data[child];

        Cndx = child;
        child = 2 * Cndx + 1;
    }

    // Place the saved last element into the final hole
    P->data[Cndx] = lastElement;
    
    return min;
}

// Optional generic non-recursive heapify by grade (not used by deleteMin)
static void minHeapify(POT *P, int index){
    if (!P || P->lastNdx < 0) return;

    while (1) {
        int left  = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left <= P->lastNdx && P->data[left].grade < P->data[smallest].grade) {
            smallest = left;
        }
        if (right <= P->lastNdx && P->data[right].grade < P->data[smallest].grade) {
            smallest = right;
        }

        if (smallest == index) break;

        student temp = P->data[index];
        P->data[index] = P->data[smallest];
        P->data[smallest] = temp;

        index = smallest;
    }
}

// ==========================================
//              QUERY & UTILITIES
// ==========================================

void generateStudent(POT *P){
    student stud[] = {
        {"STUD1008", {"Olivia",    'B', "Hernandez"}, 123},
        {"STUD1001", {"John",      'R', "Doe"},       128},
        {"STUD1020", {"Lily",      'N', "Tanaka"},    255},
        {"STUD1004", {"Joey",      'K', "Lee"},       207},
        {"STUD1002", {"Jane",      'L', "Smith"},     217},
        {"STUD1005", {"Michael",   'T', "Garcia"},    36},
        {"STUD1008", {"Olivia",    'B', "Hernandez"}, 123}, // duplicate ID
        {"STUD1003", {"Mark",      'S', "Johnson"},   130},
        {"STUD1010", {"Mia",       'D', "Nguyen"},    89},
        {"STUD1011", {"Ethan",     'E', "Perez"},     130},
        {"STUD1021", {"Elijah",    'O', "Yamamoto"},  36},
        {"STUD1017", {"Daniel",    'K', "Cruz"},      128},
        {"STUD1019", {"Noah",      'M', "Reyes"},     130},
        {"STUD1012", {"Chung",     'F', "Tan"},       231},
        {"STUD1013", {"Alexander", 'G', "Reyes"},     44},
        {"STUD1014", {"Sofia",     'H', "Wong"},      149},
        {"STUD1015", {"Benjamin",  'I', "Liu"},       202},
        {"STUD1016", {"Chloe",     'J', "Gonzales"},  59},
        {"STUD1018", {"Garret",    'L', "Santos"},    73},
        {"STUD1029", {"Gabriel",   'W', "Nguyen"},    108},
    };
    
    int total_to_insert = sizeof(stud) / sizeof(student);

    for(int i = 0; i < total_to_insert; i++){
        insertMinPOT(P, stud[i]);
    }
}

void display_student(const student* s, const char* label) {
    if (!s || s->grade == -1) {
        printf("%s: (NULL)\n", label);
    } else {
        printf("%s: ID %s | Name: %s %c. %s | Grade: %d\n", 
               label, s->idNum, s->name.fname, s->name.mi, s->name.lname, s->grade);
    }
}

// Visual tree display (uses grade only)
void display_tree(const POT* P) {
    if (!P || P->lastNdx < 0) {
        puts("\n(empty heap)\n");
        return;
    }

    const int n = P->lastNdx + 1;
    const int NODEW = 5; 
    const int GAP = 2; 

    int h = 0, cap = 1;
    while (cap - 1 < n) { h++; cap <<= 1; }

    const int maxNodesLast = 1 << (h - 1);
    const int lineWidth = (NODEW + GAP) * maxNodesLast - GAP;

    char* line = (char*)malloc((size_t)lineWidth + 1);
    if (!line) { perror("malloc"); return; }

    printf("\n--- Heap Structure (Grade Priority) ---\n");

    for (int level = 0; level < h; ++level) {
        int nodesOnLevel = 1 << level;
        int startIndex = nodesOnLevel - 1;
        if (startIndex > P->lastNdx) break;

        memset(line, ' ', (size_t)lineWidth);
        line[lineWidth] = '\0';

        for (int k = 0; k < nodesOnLevel; ++k) {
            int idx = startIndex + k;
            if (idx > P->lastNdx) break;

            int center = (lineWidth * (2 * k + 1)) / (2 * nodesOnLevel);
            char label[NODEW + 1];
            snprintf(label, sizeof(label), "[%3d]", P->data[idx].grade);

            int start = center - NODEW / 2;
            if (start < 0) start = 0;
            if (start + NODEW > lineWidth) start = lineWidth - NODEW;

            for (int c = 0; c < NODEW; ++c) line[start + c] = label[c];
        }
        puts(line);

        if (level < h - 1) {
            memset(line, ' ', (size_t)lineWidth);
            line[lineWidth] = '\0';

            int nextNodes = nodesOnLevel << 1;
            for (int k = 0; k < nodesOnLevel; ++k) {
                int idx = startIndex + k;
                if (idx > P->lastNdx) break;

                int center = (lineWidth * (2 * k + 1)) / (2 * nodesOnLevel);
                int leftIdx  = 2 * idx + 1;
                int rightIdx = 2 * idx + 2;

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
    printf("---------------------------------------\n");
    printf("Current Size: %d | Root Grade: %d\n", n, P->data[0].grade);
    printf("---------------------------------------\n");
}
