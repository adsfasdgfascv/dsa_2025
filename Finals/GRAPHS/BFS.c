#include <stdio.h>
#include <stdlib.h>

#define MAX 10
#define VISITED 1
#define UNVISITED 100

typedef int vertex;

typedef struct node{
    int vertex;
    struct node *next;
} *ptr, Node;

typedef ptr Graph[MAX];


void addEdge(Graph G, int src, int dest);
void bfs(Graph G, vertex v, int mark[]);
void displayGraph(Graph G);
void printQueueState(int queue[], int front, int rear);

int main(){
    Graph G;
    int edges, src, dest;
    int marker[MAX];
    
    for(int i=0;i<MAX;i++){
         G[i] = NULL;
         marker[i] = UNVISITED;
    }
    

    for(int i=0;i<MAX;i++){
        printf("Enter edges (src & dest): ");
        scanf("%d %d", &src, &dest);
        addEdge(G, src, dest);
    }
    
    printf("\nAdjacency List:");
    displayGraph(G);
    
    printf("\nBFS Traversal: ");
    bfs(G, 0, marker);
    
    
    return 0;
}


void addEdge(Graph G, int src, int dest){
    ptr newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = G[src];
    G[src] = newNode;
}

void bfs(Graph G, vertex start, int marker[]){
    int queue[MAX], front= -1, rear = -1;
    
    // enqueue start
    queue[++rear] = start;
    marker[start] = VISITED;
    /**/
    printf("Initial queue state after enqueue start:\n");
    printQueueState(queue, front, rear);

    
    while(front != rear){
        // dequeue
        start = queue[++front]; 
        printf("Node: %c(%d)\n", start + 65, start);
        /**/
        printf("\nDequeue -> Node: %c (%d)\n", start + 'A', start);
        printQueueState(queue, front, rear);

        // visit neighbors -> enqueue unvisited
        ptr temp = G[start];
        while(temp != NULL){
            if(marker[temp->vertex] == UNVISITED){
                queue[++rear] = temp->vertex;
                marker[temp->vertex] = VISITED;
                /**/
                printf("  Enqueue: %c (%d)\n", temp->vertex + 'A', temp->vertex);
                printQueueState(queue, front, rear);

            }
            temp = temp->next;
        }
        
    }
    
    //can turn it into a for loop;
}

void displayGraph(Graph G){
    for (int i = 0; i < MAX; i++){
        printf("\nNode %d:", i);
        ptr temp = G[i];
        while(temp != NULL){
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
    }
}



//////HELPER
void printQueueState(int queue[], int front, int rear){
    // Top row: FRONT and visible queue (front+1 .. rear)
    printf("FRONT = %2d\tQUEUE = ", front);
    if (front + 1 <= rear) {
        for (int i = front + 1; i <= rear; i++) {
            printf("%c ", queue[i] >= 0 ? (char)(queue[i] + 'A') : '\\');
        }
    } else {
        printf("(empty)");
    }
    printf("\n");

    // Bottom row: REAR and the entire underlying array (ORIG)
    printf("REAR  = %2d\tORIG  = ", rear);
    for (int i = 0; i < MAX; i++) {
        if (queue[i] == -1) printf("\\0 ");
        else printf("%c  ", (char)(queue[i] + 'A'));
    }
    printf("\n");
}
