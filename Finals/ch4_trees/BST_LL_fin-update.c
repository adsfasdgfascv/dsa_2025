/******************************************************************************
 * PROGRAM: Binary Search Tree (BST) Implementation in C
 * 
 * COURSE: Data Structures and Algorithms
 * TOPIC: Binary Search Trees – Insertion, Deletion, Traversal, Utilities, 
 *        Mirror Image, and Tree Deletion
 * 
 * AUTHOR: Gabieta, Mark Anthony
 * DATE: November 19, 2025
 * VERSION: 1.0
 * 
 *****************************************************************************
 * 
 * PROGRAM DESCRIPTION:
 * This program implements a Binary Search Tree (BST) in C. Each node stores
 *      - label tree
 *      - Linked List
 *      - depth first
 * 
 * an integer key, and the tree maintains the BST property:
 * 
 *   - All keys in the left subtree are smaller than the node's key
 *   - All keys in the right subtree are larger than the node's key
 * 
 * Supported operations:
 *   1. make_null()          : Initializes an empty BST
 *   2. insert()             : Inserts a key into the BST
 *   3. delete()             : Deletes a key from the BST
 *   4. find()               : Searches for a key in the BST
 *   5. find_min()           : Finds the node with the smallest key
 *   6. find_max()           : Finds the node with the largest key
 *   7. inorder()            : In-order traversal
 *   8. preorder()           : Pre-order traversal
 *   9. postorder()          : Post-order traversal
 *  10. printTree()          : Visualizes the tree structure
 *  11. height()             : Returns the height of the BST (levels)
 *  12. totalNodes()         : Returns total number of nodes
 *  13. internalNodes()      : Returns number of internal nodes (non-leaf)
 *  14. externalNodes()      : Returns number of external nodes (leaf)
 *  15. mirrorImage()        : Generates the mirror image of the BST
 *  16. deleteTree()         : Deletes the entire tree and frees memory
 *  17. find_predecessor()   : Finds in-order predecessor (largest node in left subtree)
 * 
 * The program demonstrates:
 *   - Recursive insertion and deletion
 *   - Tree traversals (in-order, pre-order, post-order)
 *   - Computing tree utilities (height, total/internal/external nodes)
 *   - Creating a mirror image
 *   - Complete tree deletion
 *   - Visualization of BST structure in console
 * 
 *****************************************************************************
 * EXPECTED OUTPUT EXAMPLES:
 *
 * BST Traversals:
 * Inorder   : 2 3 4 6 7 15 17 18 20
 * Preorder  : 15 6 3 2 4 7 18 17 20
 * Postorder : 2 4 3 7 6 17 20 18 15
 *
 * Visual Tree Structure:
 *            20
 *         18
 *            17
 *     15
 *            7
 *         6
 *            4
 *         3
 *            2
 *
 *****************************************************************************
 * COMPILATION:
 *     gcc -o bst bst.c
 * 
 * EXECUTION:
 *     ./bst
 *
 *****************************************************************************
 * LEARNING OUTCOMES:
 * - Understand the structure and properties of a Binary Search Tree (BST)
 * - Implement recursive insertion, deletion, and search operations
 * - Perform in-order, pre-order, and post-order traversals
 * - Visualize a BST in console
 * - Calculate tree properties: height, total nodes, internal and external nodes
 * - Generate mirror image of BST
 * - Learn safe memory deallocation for entire tree
 *
 *****************************************************************************
 * REFERENCES:
 * - Reema Thareja, "Data Structures Using C", Second Edition, 2012,
 *   Department of Computer Science, Shyama Prasad Mukherjee College for Women,
 *   University of Delhi
 *  - Data Structures and Algorithm Analysis in C++, Mark Allen Weis
 *****************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COUNT 10

typedef int element_type;
typedef struct tree_node *tree_ptr;

struct tree_node{
    element_type what;
    tree_ptr left;
    tree_ptr right;
};

typedef tree_ptr SEARCH_TREE;

// Function Prototypes
SEARCH_TREE make_null(void);                    //done
tree_ptr find(element_type x, SEARCH_TREE T);   //done
tree_ptr find_min(SEARCH_TREE T);               //done
tree_ptr find_max(SEARCH_TREE T);               //done
tree_ptr insert(element_type x, SEARCH_TREE T); //done
tree_ptr delete(element_type x, SEARCH_TREE T); //done

/* Traversals */
void inorder(SEARCH_TREE T);                //done
void preorder(SEARCH_TREE T);               //done
void postorder(SEARCH_TREE T);              //done
void printTree(SEARCH_TREE T, int space);   //done


/* Utilities */
int height(SEARCH_TREE T);           /* height in number of levels: empty=0, single node=1 */           //done
int totalNodes(SEARCH_TREE T);                                                                          //done
int internalNodes(SEARCH_TREE T);    /* nodes with at least one child */                                //done
int externalNodes(SEARCH_TREE T);    /* leaf nodes (no children) */                                     //done
void mirrorImage(SEARCH_TREE T);
void deleteTree(SEARCH_TREE T);

/* Helper: find in-order predecessor (largest node in left subtree) */
struct tree_node* find_predecessor(SEARCH_TREE T);


int main(){
    SEARCH_TREE t = make_null();
    int keys[] = {15, 6, 18, 3, 7, 17, 20, 2, 4};
    int n = sizeof(keys)/ sizeof(keys[0]);
    for(int i=0;i<n;i++){
        t = insert(keys[i], t);
    }
    
    printf("BST Traversals:\n");
    printf("Inorder: "); inorder(t); printf("\n");
    printf("Postorder: "); postorder(t); printf("\n");
    printf("Preorder: "); preorder(t); printf("\n");
    
    printf("\n\n\n\n\n\nVisual Tree Structure:\n");
    printTree(t, 0);
    
    
    element_type key = 7;
    tree_ptr f = find(key, t);
    if(f) printf("%d, found\n", f->what);
    else printf("not found\n");
    
    printf("\nDeleting key 6...\n");
    t = delete(6, t);
    printf("\n\n\n\n\n\nVisual Tree after deletion:\n");
    printTree(t, 0);

    tree_ptr minNode = find_min(t);
    tree_ptr maxNode = find_max(t);
    if (minNode) printf("\nMinimum key: %d\n", minNode->what);
    if (maxNode) printf("Maximum key: %d\n", maxNode->what);
    
    
    /* Utilities */
    printf("\nHeight (levels): %d\n", height(t));
    printf("Total nodes    : %d\n", totalNodes(t));
    printf("Internal nodes : %d\n", internalNodes(t));
    printf("External nodes : %d\n", externalNodes(t));
    
    
    
    printf("\n\n\n\n\n\n--- MIRROR IMAGE OF TREE ---\n");
    mirrorImage(t);
    printTree(t, 0);
    
    printf("\n\n--- DELETING ENTIRE TREE ---\n");
    deleteTree(t);
    t = NULL;

    t == NULL ? printf("Tree deleted successfully.\n") : printf("Tree exists.\n");
    
    
    return 0;
}








SEARCH_TREE make_null(void){
    return NULL;
}

tree_ptr insert(element_type x, SEARCH_TREE T){
    
    if(T == NULL){
        T = malloc(sizeof(struct tree_node));
        if(!T){
            printf("out of space"); 
            return NULL;
        }
        T->what = x;
        T->left = T->right = NULL;
    }
    else if(x > T->what) T->right = insert(x, T->right);
    else if(x < T->what) T->left = insert(x, T->left);
    
    return T;
}

tree_ptr find(element_type x, SEARCH_TREE T){
    if(T == NULL) return NULL;
    if(x > T->what) return find(x, T->right);
    else if(x < T->what) return find(x, T->left);
    else return T;
}

tree_ptr delete(element_type x, SEARCH_TREE T){ //mark wein reference
    tree_ptr temp;
    
    if(T == NULL) return NULL;  // silently return

    else if(x  > T->what) T->right = delete(x, T->right);
    else if(x  < T->what) T->left = delete(x, T->left);
    else{// found da node
        if(T->left && T->right){ // both has existing child
            temp = find_min(T->right);
            T->what = temp->what;
            T->right = delete(T->what, T->right);
        }else{ 
            //just one or zero child
            temp = T;
            if(T->left  == NULL) T = T->right;
            else if(T->right  == NULL) T = T->left;
            free(temp);
        }
        
    }
    return T;
}

tree_ptr find_min(SEARCH_TREE T){
    if(T == NULL) return NULL;
    else if(T->left == NULL) return T;
    else return find_min(T->left);
    
    /*      OTHER syntax
    tree_node* smallestNode(SEARCH_TREE T) {
    if (T == NULL) return NULL;
    while (T->left != NULL)
        T = T->left;
    return T;
    */
}

tree_ptr find_max(SEARCH_TREE T){
    if(T == NULL) return NULL;
    while(T->right != NULL) T= T->right;
    return T;
}




int height(SEARCH_TREE T){
    if(!T) return 0;
    int hl = height(T->left);
    int hr = height(T->right);
    return(hr > hl ? hr : hl) +1; 
}
int totalNodes(SEARCH_TREE T){
    if(!T) return 0;
    return 1+ totalNodes(T->left) + totalNodes(T->right);
}

int internalNodes(SEARCH_TREE T){
    if(!T) return 0;
    if(T->left == NULL && T->right == NULL ) return 0;
    return 1 + internalNodes(T->left) + internalNodes(T->right); 
}
int externalNodes(SEARCH_TREE T){
    if(!T) return 0;
    if(T->left == NULL && T->right == NULL ) return 1;
    return externalNodes(T->left) + externalNodes(T->right); 
}


void mirrorImage(SEARCH_TREE T){
    if(T!=NULL){
        mirrorImage(T->left);
        mirrorImage(T->right);
        
        struct tree_node *Temp = T->left;
        T->left = T->right;
        T->right = Temp;
    }
}
void deleteTree(SEARCH_TREE T){
    if(T!=NULL){
        deleteTree(T->left);
        deleteTree(T->right);
    }
    free(T);
}

















//traversal waw
void inorder(SEARCH_TREE T){
    if(!T) return;
    inorder(T->left);
    printf("%d ",T->what);
    inorder(T->right);
}
void preorder(SEARCH_TREE T){
    if(!T) return;
    printf("%d ",T->what);
    preorder(T->left);
    preorder(T->right);
}
void postorder(SEARCH_TREE T){
    if(!T) return;
    postorder(T->left);
    postorder(T->right);
    printf("%d ",T->what);
}

void printTree(SEARCH_TREE T, int space) {
    if (T == NULL) return;
    space += COUNT;

    printTree(T->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    printf("%d\n", T->what);

    printTree(T->left, space);
}



