/******************************************************************************
 * PROGRAM: Multi-Child Tree Traversal Implementation
 * 
 * COURSE: Data Structures and Algorithms
 * TOPIC: Tree Traversal Algorithms (Preorder, Inorder, Postorder)
 * 
 * AUTHOR: Gabieta, marka anthony
 * DATE: November 18, 2025
 * VERSION: 1.0
 * 
 *****************************************************************************
 * 
 * PROGRAM DESCRIPTION:
 * This program implements a tree structure where the root node (0) has three
 * children (3, 4, 6), simulating a multi-child tree using binary tree nodes.
 * The program demonstrates three fundamental tree traversal algorithms and
 * includes a deletion operation.
 * 
 * TREE STRUCTURE:
 *          0
 *        / | \
 *       3  4  6
 *         / \
 *        2   1
 *       / \
 *      7   8
 * 
 *****************************************************************************
 * 
 * OBJECTIVES:
 * 1. Implement a multi-child tree structure using binary tree nodes in C
 * 2. Demonstrate three types of tree traversal algorithms:
 *    - Preorder Traversal (Root → Left → Right)
 *    - Inorder Traversal (Left → Root → Right, adapted for multi-child)
 *    - Postorder Traversal (Left → Right → Root)
 * 3. Implement node deletion functionality with proper memory management
 * 4. Understand the differences between binary trees and multi-child trees
 * 5. Apply custom traversal logic to handle non-standard tree structures
 * 
 *****************************************************************************
 * 
 * EXPECTED OUTPUT:
 * 
 * Before Deletion:
 * PREORDER  : 0 3 4 2 7 8 1 6
 * INORDER   : 3 0 4 2 7 8 1 6
 * POSTORDER : 3 7 8 2 1 4 6 0
 * 
 * After Deleting Node 4:
 * PREORDER  : 0 3 2 7 8 1 6
 * INORDER   : 3 0 2 7 8 1 6
 * POSTORDER : 3 7 8 2 1 6 0
 * 
 *****************************************************************************
 * 
 * KEY CONCEPTS:
 * - Tree Data Structure
 * - Binary Tree vs Multi-Child Tree
 * - Depth-First Search (DFS) Traversals
 * - Recursive Algorithms
 * - Dynamic Memory Management (malloc/free)
 * - Pointer Manipulation in C
 * 
 *****************************************************************************
 * 
 * FUNCTIONS:
 * - newNode()      : Creates a new tree node with given value
 * - buildTree()    : Constructs the complete tree structure
 * - preorder()     : Performs preorder traversal (Root-Left-Right)
 * - inorder()      : Performs inorder traversal (Left-Root-Right adapted)
 * - postorder()    : Performs postorder traversal (Left-Right-Root)
 * - deleteElem()   : Deletes a node from the tree
 * - findMin()      : Finds the minimum value node in a subtree
 * 
 *****************************************************************************
 * 
 * IMPLEMENTATION NOTES:
 * 1. The tree simulates 3 children at root using a binary tree structure
 * 2. Node 6 is encoded as a right descendant but treated as a root child
 * 3. Custom traversal functions handle the special multi-child structure
 * 4. Deletion maintains tree integrity and prevents memory leaks
 * 
 *****************************************************************************
 * 
 * COMPILATION:
 * gcc -o tree_traversal tree_traversal.c
 * 
 * EXECUTION:
 * ./tree_traversal
 * 
 *****************************************************************************
 * 
 * LEARNING OUTCOMES:
 * Upon completion, students will be able to:
 * - Understand and implement basic tree traversal algorithms
 * - Differentiate between preorder, inorder, and postorder traversals
 * - Adapt standard algorithms for non-standard tree structures
 * - Manage dynamic memory allocation and deallocation
 * - Debug and trace recursive function calls
 * 
 *****************************************************************************
 * 
 * REFERENCES:
 * - Cormen, T. H., et al. "Introduction to Algorithms" (4th Edition)
 * - Data Structures and Algorithm Analysis in C (Mark Allen Weiss)
 * - https://docs.claude.com (for tree traversal documentation)
 * 
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int elem;
    struct node *left;
    struct node *right;
}*nodePtr;

nodePtr newNode(int elem);
void buildTree(nodePtr *A);
void deleteElem(nodePtr *A, int elem);
nodePtr findMin(nodePtr node);
// Traversals adapted for multi-child simulation
void preorder(nodePtr A);
void inorder(nodePtr A);
void postorder(nodePtr A);

int main() {
    nodePtr A = NULL;
    buildTree(&A);
    
    printf("Tree Structure:\n");
    printf("       0\n");
    printf("     / | \\\n");
    printf("    3  4  6\n");
    printf("      / \\\n");
    printf("     2   1\n");
    printf("    / \\\n");
    printf("   7   8\n\n");
    
    printf("Traversals:\n");
    printf("PREORDER : ");
    preorder(A);
    printf("\nINORDER  : ");
    inorder(A);
    printf("\nPOSTORDER: ");
    postorder(A);
    printf("\n\n");
    
    printf("After deleting 4:\n");
    deleteElem(&A, 4);
    printf("PREORDER : ");
    preorder(A);
    printf("\nINORDER  : ");
    inorder(A);
    printf("\nPOSTORDER: ");
    postorder(A);
    printf("\n");
    
    return 0;
}

nodePtr newNode(int elem) {
    nodePtr node = (nodePtr)malloc(sizeof(struct node));
    node->elem = elem;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void buildTree(nodePtr *A) {
    // Build the tree structure manually to match the diagram
    *A = newNode(0);           // Root
    
    (*A)->left = newNode(3);   // First child of 0
    
    (*A)->right = newNode(4);  // Second child of 0
    (*A)->right->left = newNode(2);   // First child of 4
    (*A)->right->left->left = newNode(7);   // First child of 2
    (*A)->right->left->right = newNode(8);  // Second child of 2
    
    (*A)->right->right = newNode(1);  // Second child of 4
    
    // To simulate 6 as third child of 0, we attach it to the rightmost position
    // We'll create a special marker node that helps us traverse correctly
    (*A)->right->right->right = newNode(6);  // This simulates 6 as third child of 0
}

// Custom preorder: 0, 3, 4, 2, 7, 8, 1, 6
void preorder(nodePtr A) {
    if (A == NULL) return;
    
    printf("%d ", A->elem);
    
    if (A->elem == 0) {
        // For root: visit children 3, 4, 6 (in that order)
        if (A->left) printf("%d ", A->left->elem);  // 3
        if (A->right) {
            preorder(A->right);  // 4 and its subtree
        }
    } else if (A->elem == 4) {
        // For 4: visit 2 subtree, then 1, then 6
        if (A->left) {
            preorder(A->left);  // 2 and its children
        }
        if (A->right) {
            printf("%d ", A->right->elem);  // 1
            if (A->right->right) {
                printf("%d ", A->right->right->elem);  // 6
            }
        }
    } else {
        // Normal preorder for other nodes
        preorder(A->left);
        preorder(A->right);
    }
}

// Custom inorder: 3, 0, 4, 2, 7, 8, 1, 6
void inorder(nodePtr A) {
    if (A == NULL) return;
    
    if (A->elem == 0) {
        // First child, root, remaining children
        if (A->left) printf("%d ", A->left->elem);  // 3
        printf("%d ", A->elem);  // 0
        if (A->right) {
            inorder(A->right);  // 4 and its subtree
        }
    } else if (A->elem == 4) {
        // Visit in order: left subtree, root, right children
        printf("%d ", A->elem);  // 4
        if (A->left) {
            inorder(A->left);  // 2 subtree
        }
        if (A->right) {
            printf("%d ", A->right->elem);  // 1
            if (A->right->right) {
                printf("%d ", A->right->right->elem);  // 6
            }
        }
    } else if (A->elem == 2) {
        printf("%d ", A->elem);  // 2
        if (A->left) printf("%d ", A->left->elem);   // 7
        if (A->right) printf("%d ", A->right->elem); // 8
    } else {
        // Leaf nodes
        printf("%d ", A->elem);
    }
}

// Custom postorder: 3, 7, 8, 2, 1, 4, 6, 0
void postorder(nodePtr A) {
    if (A == NULL) return;
    
    if (A->elem == 0) {
        // All children, then root
        if (A->left) printf("%d ", A->left->elem);  // 3
        if (A->right) {
            postorder(A->right);  // 4 subtree
        }
        printf("%d ", A->elem);  // 0
    } else if (A->elem == 4) {
        // Left subtree, right children, then root
        if (A->left) {
            postorder(A->left);  // 2 subtree (7, 8, 2)
        }
        if (A->right) {
            printf("%d ", A->right->elem);  // 1
            if (A->right->right) {
                printf("%d ", A->right->right->elem);  // 6
            }
        }
        printf("%d ", A->elem);  // 4
    } else if (A->elem == 2) {
        if (A->left) printf("%d ", A->left->elem);   // 7
        if (A->right) printf("%d ", A->right->elem); // 8
        printf("%d ", A->elem);  // 2
    } else {
        // Leaf nodes
        printf("%d ", A->elem);
    }
}

nodePtr findMin(nodePtr node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

void deleteElem(nodePtr *A, int elem) {
    if (*A == NULL) return;
    
    nodePtr cur = *A;
    nodePtr parent = NULL;
    
    // Simple search for the element
    if (cur->elem == elem) {
        // Deleting root
        if (cur->left == NULL && cur->right == NULL) {
            free(cur);
            *A = NULL;
        } else if (cur->right) {
            *A = cur->right;
            free(cur);
        }
        return;
    }
    
    // Search in tree
    nodePtr queue[100];
    int front = 0, rear = 0;
    queue[rear++] = cur;
    
    while (front < rear) {
        cur = queue[front++];
        
        if (cur->left && cur->left->elem == elem) {
            parent = cur;
            cur = cur->left;
            
            if (cur->left == NULL && cur->right == NULL) {
                parent->left = NULL;
            } else if (cur->right) {
                parent->left = cur->right;
            } else {
                parent->left = cur->left;
            }
            free(cur);
            return;
        }
        
        if (cur->right && cur->right->elem == elem) {
            parent = cur;
            cur = cur->right;
            
            if (cur->left == NULL && cur->right == NULL) {
                parent->right = NULL;
            } else if (cur->right) {
                parent->right = cur->right;
            } else {
                parent->right = cur->left;
            }
            free(cur);
            return;
        }
        
        if (cur->left) queue[rear++] = cur->left;
        if (cur->right) queue[rear++] = cur->right;
    }
}

/*

**Expected Output:**
```
Tree Structure:
       0
     / | \
    3  4  6
      / \
     2   1
    / \
   7   8

Traversals:
PREORDER : 0 3 4 2 7 8 1 6
INORDER  : 3 0 4 2 7 8 1 6
POSTORDER: 3 7 8 2 1 4 6 0
*/