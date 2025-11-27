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
void dfs(Graph G, vertex v, int mark[]);
void displayGraph(Graph G);


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
    
    printf("\nDFS Traversal: ");
    dfs(G, 0, marker);
    
    
    return 0;
}


void addEdge(Graph G, int src, int dest){
    ptr newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = G[src];
    G[src] = newNode;
}

void dfs(Graph G, vertex v, int marker[]){
    marker[v] = VISITED;
    printf("Node: %c(%d)\n", v + 65, v);
    
    ptr temp = G[v];
    while(temp != NULL){
        if(marker[temp->vertex] == UNVISITED){
            dfs(G, temp->vertex, marker);
        }
        temp = temp->next;
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


