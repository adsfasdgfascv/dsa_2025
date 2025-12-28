#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 10
#define ROOT_NODE -1
#define INVALID_NODE -2
#define CORRUPTED -999


// 1. Parent Pointer Representation (The Broken One)
typedef int UpLinkTable[MAX_NODES]; 

// 2. List of Children Representation (The Intact One)
typedef struct ListNode {
    int childIndex;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode* headers[MAX_NODES]; 
} DownLinkLogs;


void repair_uplinks(UpLinkTable T, DownLinkLogs L);
int get_hop_count(UpLinkTable T, int nodeA, int nodeB);

void initialize_system(UpLinkTable T, DownLinkLogs *L);
void add_connection(UpLinkTable T, DownLinkLogs *L, int parent, int child);
void corrupt_system(UpLinkTable T);
void print_uplink_table(UpLinkTable T);
int get_depth(UpLinkTable T, int node);

int main() {
    UpLinkTable networkMap;
    DownLinkLogs broadcastLog;

    initialize_system(networkMap, &broadcastLog);
    add_connection(networkMap, &broadcastLog, 0, 1);
    add_connection(networkMap, &broadcastLog, 0, 2);
    add_connection(networkMap, &broadcastLog, 1, 3);
    add_connection(networkMap, &broadcastLog, 1, 4);
    add_connection(networkMap, &broadcastLog, 2, 5);
    add_connection(networkMap, &broadcastLog, 2, 6);

    // 2. Break the system
    printf("=== Network Topology Recovery ===\n\n");
    printf("[STATUS] Simulating Memory Corruption...\n");
    corrupt_system(networkMap);
    printf("UpLinkTable before repair:\n");
    print_uplink_table(networkMap);

    // 3. STUDENT TASK 1: Repair
    printf("\n[PHASE 1] Repairing Uplinks using DownLinkLogs...\n");
    repair_uplinks(networkMap, broadcastLog);
    printf("Repair complete.\n\n");
    printf("UpLinkTable after repair:\n");
    print_uplink_table(networkMap);

    // 4. STUDENT TASK 2: Hop Count
    printf("\n[PHASE 2] Calculating Hop Counts...\n");
    
    // Case A: Siblings (3 and 4 share parent 1)
    int d1 = get_hop_count(networkMap, 3, 4);
    printf("Distance 3 <-> 4 (Expected: 2): %d\n", d1);

    // Case B: Cousins (3 and 6 share grandparent 0)
    int d2 = get_hop_count(networkMap, 3, 6);
    printf("Distance 3 <-> 6 (Expected: 4): %d\n", d2);

    // Case C: Ancestor/Descendant (5 and 0)
    int d3 = get_hop_count(networkMap, 5, 0);
    printf("Distance 5 <-> 0 (Expected: 2): %d\n", d3);

    return 0;
}

// ----------------------------------------------------
// STUDENT IMPLEMENTATION AREA
// ----------------------------------------------------
/**
 * TASK 1: Repair the Corrupted Array
 * Iterate through the 'DownLinkLogs' (Linked Lists). 
 * If a node P has a child C in its list, then we know Parent[C] must be P.
 * Update the UpLinkTable T[C] with P.
 */
void repair_uplinks(UpLinkTable T, DownLinkLogs L) {
    for(int i=0;i<MAX_NODES; i++){
        ListNode * temp = L[i];
        while(temp != NULL){
            T[temp->childIndex] = i;
            temp = temp->next;
        }
    }
}

/**
 * TASK 2: Calculate Hops (Distance)
 * Find the distance between two nodes using ONLY the parent array (UpLinkTable).
 * Logic:
 * 1. Calculate depth of Node A and Node B.
 * 2. Find their Lowest Common Ancestor (LCA).
 * 3. Formula: Dist = Depth(A) + Depth(B) - 2 * Depth(LCA).
 * * Note: You do not have access to children pointers here. Only parents.
 */
int get_hop_count(UpLinkTable T, int nodeA, int nodeB) {
    int count;
    for(int i=0;i<MAX_NODES;i++){
        if(T[i] == nodeA){
            count++;
            int temp = i;
        }
        else if(i == temp){
            count++;
        }
        else if(T[i] == nodeB){
            count++;
            return count;
            break;
        }
    }
    
    return -1;
}

// ----------------------------------------------------
//       HELPERS 
// ----------------------------------------------------


void initialize_system(UpLinkTable T, DownLinkLogs *L){
    for(int i=0;i<MAX_NODES;i++){
        L->headers[i] = NULL;
        T[i] = INVALID_NODE;
    }
}

void add_connection(UpLinkTable T, DownLinkLogs *L, int parent, int child){
    T[child] = parent;
    
    ListNode * newNode = malloc(sizeof(ListNode));
    newNode->childIndex = child;
    newNode->next = L->headers[parent]; 
    L->headers[parent] = newNode;
}

void corrupt_system(UpLinkTable T){
    T[1] = CORRUPTED;
    T[3] = CORRUPTED;
    T[5] = CORRUPTED;
    T[6] = CORRUPTED;
}

void print_uplink_table(UpLinkTable T){
    printf("--- Tree Array Representation ---\n");
    printf("Index (Child) | Parent\n");
    printf("--------------|-------\n");
    for(int i=0;i <MAX_NODES; i++){
        if(T[i] == ROOT_NODE) printf("ROOT\n");
        else if(T[i] == CORRUPTED) printf("CORRUPTED\n");
        else if (T[i] == INVALID_NODE) printf("Uninitialized\n");
        else printf("%d\n", T[i]);
        
    }
    printf("---------------------------------\n");
}