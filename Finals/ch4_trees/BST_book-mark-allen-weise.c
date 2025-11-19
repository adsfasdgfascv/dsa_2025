/******************************************************************************
 * PROGRAM: Binary Search Tree (BST) Implementation
 * 
 * COURSE: Data Structures and Algorithms
 * TOPIC: Binary Search Trees – Insertion, Deletion, Traversal, and Visualization
 * 
 * AUTHOR: Gabieta, Mark Anthony
 * DATE: November 19, 2025
 * VERSION: 1.0
 * 
 *****************************************************************************
 * 
 * PROGRAM DESCRIPTION:
 * This program implements a Binary Search Tree (BST) in C. Each node stores an
 * integer key, and the tree maintains the BST property:
 * 
 *   - All keys in the left subtree are smaller than the node's key
 *   - All keys in the right subtree are larger than the node's key
 * 
 * The program supports the following operations:
 *   1. make_null()   : Initializes an empty BST
 *   2. insert()      : Recursively inserts a key into the BST
 *   3. delete()      : Recursively deletes a key from the BST
 *   4. find()        : Searches for a key in the BST
 *   5. find_min()    : Finds the node with the smallest key
 *   6. find_max()    : Finds the node with the largest key
 *   7. inorder()     : Prints the BST in-order
 *   8. preorder()    : Prints the BST pre-order
 *   9. postorder()   : Prints the BST post-order
 *  10. printTree()   : Visualizes the tree structure
 * 
 * The program demonstrates insertion, deletion, searching, and traversals,
 * along with a visual representation of the BST.
 * 
 *****************************************************************************
 * 
 * EXPECTED OUTPUT:
 *
 * BST Traversals:
 * Inorder  : 2 3 4 6 7 15 17 18 20
 * Preorder : 15 6 3 2 4 7 18 17 20
 * Postorder: 2 4 3 7 6 17 20 18 15
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
 * 
 * COMPILATION:
 *     gcc -o bst bst.c
 * 
 * EXECUTION:
 *     ./bst
 *
 *****************************************************************************
 * 
 * LEARNING OUTCOMES:
 * - Understand the structure and properties of a Binary Search Tree (BST)
 * - Implement recursive insertion and deletion in BST
 * - Perform in-order, pre-order, and post-order traversals
 * - Implement tree visualization to understand tree structure
 * - Understand the use of recursion in tree algorithms
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int element_type;
typedef struct tree_node *tree_ptr;

struct tree_node {
    element_type element;
    tree_ptr left;
    tree_ptr right;
};

typedef tree_ptr SEARCH_TREE;

// Function Prototypes
SEARCH_TREE make_null(void);
tree_ptr find(element_type x, SEARCH_TREE T);
tree_ptr find_min(SEARCH_TREE T);
tree_ptr find_max(SEARCH_TREE T);
tree_ptr insert(element_type x, SEARCH_TREE T);
tree_ptr delete(element_type x, SEARCH_TREE T);

void inorder(SEARCH_TREE T);
void preorder(SEARCH_TREE T);
void postorder(SEARCH_TREE T);
void printTree(SEARCH_TREE T, int space);

#define COUNT 10

int main() {
    SEARCH_TREE T = make_null();

    // Insert example nodes
    int keys[] = {15, 6, 18, 3, 7, 17, 20, 2, 4};
    int n = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < n; i++) {
        T = insert(keys[i], T);
    }

    printf("BST Traversals:\n");
    printf("Inorder  : "); inorder(T); printf("\n");
    printf("Preorder : "); preorder(T); printf("\n");
    printf("Postorder: "); postorder(T); printf("\n\n");

    printf("Visual Tree Structure:\n");
    printTree(T, 0);

    // Demonstrate find, delete, find_min, find_max
    element_type key = 7;
    tree_ptr f = find(key, T);
    if (f) printf("\nKey %d found in BST.\n", key);
    else printf("\nKey %d not found in BST.\n", key);

    printf("\nDeleting key 6...\n");
    T = delete(6, T);
    printf("Visual Tree after deletion:\n");
    printTree(T, 0);

    tree_ptr minNode = find_min(T);
    tree_ptr maxNode = find_max(T);
    if (minNode) printf("\nMinimum key: %d\n", minNode->element);
    if (maxNode) printf("Maximum key: %d\n", maxNode->element);

    return 0;
}

// ====== BST Operations ======
SEARCH_TREE make_null(void) {
    return NULL;
}

tree_ptr find(element_type x, SEARCH_TREE T) {
    if (T == NULL) return NULL;
    if (x < T->element) return find(x, T->left);
    else if (x > T->element) return find(x, T->right);
    else return T;
}

tree_ptr find_min(SEARCH_TREE T) {
    if (T == NULL) return NULL;
    else if (T->left == NULL) return T;
    else return find_min(T->left);
}

tree_ptr find_max(SEARCH_TREE T) {
    if (T == NULL) return NULL;
    while (T->right != NULL) T = T->right;
    return T;
}

tree_ptr insert(element_type x, SEARCH_TREE T) {
    if (T == NULL) {
        T = (tree_ptr) malloc(sizeof(struct tree_node));
        if (!T) {
            fprintf(stderr, "Out of space!!!\n");
            exit(1);
        }
        T->element = x;
        T->left = T->right = NULL;
    } else if (x < T->element) T->left = insert(x, T->left);
    else if (x > T->element) T->right = insert(x, T->right);
    // else duplicate, do nothing
    return T;
}

tree_ptr delete(element_type x, SEARCH_TREE T) {
    tree_ptr tmp;
    if (T == NULL) {
        printf("Element not found: %d\n", x);
        return NULL;
    } else if (x < T->element) T->left = delete(x, T->left);
    else if (x > T->element) T->right = delete(x, T->right);
    else { // Found node to delete
        if (T->left && T->right) { // Two children
            tmp = find_min(T->right);
            T->element = tmp->element;
            T->right = delete(T->element, T->right);
        } else { // One or zero children
            tmp = T;
            if (T->left == NULL) T = T->right;
            else if (T->right == NULL) T = T->left;
            free(tmp);
        }
    }
    return T;
}

// ====== Traversals ======
void inorder(SEARCH_TREE T) {
    if (!T) return;
    inorder(T->left);
    printf("%d ", T->element);
    inorder(T->right);
}

void preorder(SEARCH_TREE T) {
    if (!T) return;
    printf("%d ", T->element);
    preorder(T->left);
    preorder(T->right);
}

void postorder(SEARCH_TREE T) {
    if (!T) return;
    postorder(T->left);
    postorder(T->right);
    printf("%d ", T->element);
}

// ====== Tree Visualization ======
void printTree(SEARCH_TREE T, int space) {
    if (T == NULL) return;
    space += COUNT;

    printTree(T->right, space);

    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    printf("%d\n", T->element);

    printTree(T->left, space);
}
