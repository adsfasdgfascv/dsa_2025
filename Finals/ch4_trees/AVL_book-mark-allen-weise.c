/******************************************************************************
 * PROGRAM: AVL Tree Implementation
 * 
 * COURSE: Data Structures and Algorithms
 * TOPIC: AVL Trees – Insertion, Traversal, and Visualization
 * 
 * AUTHOR: Gabieta, Mark Anthony
 * DATE: November 19, 2025
 * VERSION: 1.0
 * 
 *****************************************************************************
 * 
 * PROGRAM DESCRIPTION:
 * This program implements an AVL (Adelson-Velskii and Landis) tree in C. 
 * An AVL tree is a self-balancing binary search tree where the height 
 * difference of left and right subtrees of any node is at most 1. Each 
 * node stores an integer key and its height.
 *
 * Supported operations:
 *   1. make_null()       : Initialize an empty AVL tree
 *   2. insert()          : Insert a key while maintaining AVL balance
 *   3. find()            : Search for a key
 *   4. find_min()        : Find node with minimum key
 *   5. find_max()        : Find node with maximum key
 *   6. inorder(), preorder(), postorder() : Traversals
 *   7. printTree()       : Visualize the tree structure
 * 
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>

typedef int element_type;
typedef struct avl_node *avl_ptr;

struct avl_node {
    element_type element;
    avl_ptr left;
    avl_ptr right;
    int height;  // height of the node
};

typedef avl_ptr SEARCH_TREE;

#define COUNT 10

// Function Prototypes
SEARCH_TREE make_null(void);
avl_ptr find(element_type x, SEARCH_TREE T);
avl_ptr find_min(SEARCH_TREE T);
avl_ptr find_max(SEARCH_TREE T);
avl_ptr insert(element_type x, SEARCH_TREE T);

void inorder(SEARCH_TREE T);
void preorder(SEARCH_TREE T);
void postorder(SEARCH_TREE T);
void printTree(SEARCH_TREE T, int space);

// AVL helper functions
int height(avl_ptr p);
int max(int a, int b);
avl_ptr s_rotate_left(avl_ptr k2);
avl_ptr s_rotate_right(avl_ptr k2);
avl_ptr double_rotate_left(avl_ptr k3);
avl_ptr double_rotate_right(avl_ptr k3);

int main() {
    SEARCH_TREE T = make_null();

    // Insert example nodes
    int keys[] = {15, 6, 18, 3, 7, 17, 20, 2, 4};
    int n = sizeof(keys)/sizeof(keys[0]);
    for (int i = 0; i < n; i++) {
        T = insert(keys[i], T);
    }

    printf("AVL Traversals:\n");
    printf("Inorder  : "); inorder(T); printf("\n");
    printf("Preorder : "); preorder(T); printf("\n");
    printf("Postorder: "); postorder(T); printf("\n\n");

    printf("Visual AVL Tree Structure:\n");
    printTree(T, 0);

    return 0;
}

// ====== AVL Tree Operations ======
SEARCH_TREE make_null(void) {
    return NULL;
}

int height(avl_ptr p) {
    return p == NULL ? -1 : p->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

avl_ptr find(element_type x, SEARCH_TREE T) {
    if (T == NULL) return NULL;
    if (x < T->element) return find(x, T->left);
    else if (x > T->element) return find(x, T->right);
    else return T;
}

avl_ptr find_min(SEARCH_TREE T) {
    if (T == NULL) return NULL;
    else if (T->left == NULL) return T;
    else return find_min(T->left);
}

avl_ptr find_max(SEARCH_TREE T) {
    if (T == NULL) return NULL;
    while (T->right != NULL) T = T->right;
    return T;
}

// ====== Rotations ======
avl_ptr s_rotate_left(avl_ptr k2) {
    avl_ptr k1 = k2->right;
    k2->right = k1->left;
    k1->left = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->right), k2->height) + 1;
    return k1;
}

avl_ptr s_rotate_right(avl_ptr k2) {
    avl_ptr k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max(height(k2->left), height(k2->right)) + 1;
    k1->height = max(height(k1->left), k2->height) + 1;
    return k1;
}

avl_ptr double_rotate_left(avl_ptr k3) {
    k3->right = s_rotate_right(k3->right);
    return s_rotate_left(k3);
}

avl_ptr double_rotate_right(avl_ptr k3) {
    k3->left = s_rotate_left(k3->left);
    return s_rotate_right(k3);
}

// ====== AVL Insertion ======
avl_ptr insert(element_type x, SEARCH_TREE T) {
    if (T == NULL) {
        T = (avl_ptr) malloc(sizeof(struct avl_node));
        if (!T) {
            fprintf(stderr, "Out of space!!!\n");
            exit(1);
        }
        T->element = x;
        T->left = T->right = NULL;
        T->height = 0;
    } else if (x < T->element) {
        T->left = insert(x, T->left);
        if (height(T->left) - height(T->right) == 2) {
            if (x < T->left->element)
                T = s_rotate_right(T);
            else
                T = double_rotate_right(T);
        }
    } else if (x > T->element) {
        T->right = insert(x, T->right);
        if (height(T->right) - height(T->left) == 2) {
            if (x > T->right->element)
                T = s_rotate_left(T);
            else
                T = double_rotate_left(T);
        }
    }
    // else duplicate, do nothing

    T->height = max(height(T->left), height(T->right)) + 1;
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
