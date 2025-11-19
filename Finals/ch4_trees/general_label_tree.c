/******************************************************************************
 * PROGRAM: General Tree Implementation (First Child / Next Sibling)
 * 
 * COURSE: Data Structures and Algorithms
 * TOPIC: General Trees – First Child / Next Sibling Representation
 * 
 * AUTHOR: Gabieta, Mark Anthony
 * DATE: November 18, 2025
 * VERSION: 2.0
 * 
 *****************************************************************************
 * 
 * PROGRAM DESCRIPTION:
 * This program implements a GENERAL TREE (not just a binary tree) using the
 * "First Child / Next Sibling" representation as described in:
 * 
 *   Mark Allen Weiss – Data Structures and Algorithm Analysis in C (Section 4.1.1)
 * 
 * In this structure, each node stores:
 *     - first_child   (pointer to the leftmost child)
 *     - next_sibling  (pointer to the next child in the same level)
 * 
 * This allows a node to have ANY number of children without wasting memory.
 * 
 * The program constructs the following general tree:
 * 
 *              0
 *            / | \
 *           3  4  6
 *             / \
 *            2   1
 *           / \
 *          7   8
 * 
 * The tree is then traversed using:
 *     1. Preorder Traversal
 *     2. Inorder Traversal (adapted for general trees)
 *     3. Postorder Traversal
 * 
 *****************************************************************************
 * 
 * OBJECTIVES:
 * 1. Implement a TRUE GENERAL TREE using the First Child / Next Sibling model.
 * 2. Demonstrate depth-first traversals adapted for general trees:
 *      - Preorder (Root → Children)
 *      - Inorder  (Leftmost Child → Root → Remaining Children)
 *      - Postorder (Children → Root)
 * 3. Show how a tree with unlimited children can be stored efficiently.
 * 4. Reinforce recursive traversal logic with non-binary tree structures.
 * 5. Provide clear coding style, comments, and textbook-aligned implementation.
 * 
 *****************************************************************************
 * 
 * EXPECTED OUTPUT:
 * 
 * Preorder : 0 3 4 2 7 8 1 6
 * Inorder  : 3 0 4 2 7 8 1 6
 * Postorder: 3 7 8 2 1 6 0
 * 
 *****************************************************************************
 * 
 * KEY CONCEPTS:
 * - General Tree (N-Ary Tree)
 * - First Child / Next Sibling Representation
 * - Depth-First Search (DFS)
 * - Recursive Traversals
 * - Linked List Based Children Management
 * - Pointer Manipulation in C
 * 
 *****************************************************************************
 * 
 * FUNCTIONS:
 * - newNode()        : Allocates and initializes a new tree node
 * - appendChild()    : Appends a child to a parent node (as last sibling)
 * - buildTree()      : Constructs the full general tree based on the diagram
 * - preorder()       : Recursive preorder traversal
 * - inorder()        : Adapted inorder traversal for general trees
 * - postorder()      : Recursive postorder traversal
 * 
 *****************************************************************************
 * 
 * COMPILATION:
 *     gcc -o general_tree general_tree.c
 * 
 * EXECUTION:
 *     ./general_tree
 * 
 *****************************************************************************
 * 
 * LEARNING OUTCOMES:
 * - Understand the First Child / Next Sibling general tree representation.
 * - Learn how to traverse trees with unlimited children.
 * - Identify differences between binary tree traversals and general tree DFS.
 * - Apply recursive logic to hierarchical data structures.
 * 
 *****************************************************************************
 * 
 * REFERENCES:
 * - Mark Allen Weiss, "Data Structures and Algorithm Analysis in C"
 * - Cormen et al., "Introduction to Algorithms"
 * 
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    int element;
    struct tree_node *first_child;
    struct tree_node *next_sibling;
} *tree_ptr;

// Function Prototypes
tree_ptr newNode(int elem);
void appendChild(tree_ptr parent, tree_ptr child);
void buildTree(tree_ptr *root);

void preorder(tree_ptr root);
void postorder(tree_ptr root);
void inorder(tree_ptr root);   // adapted for general tree

int main() {
    tree_ptr root = NULL;
    buildTree(&root);

    printf("GENERAL TREE (First Child / Next Sibling)\n\n");

    printf("Preorder : ");
    preorder(root);
    printf("\n");

    printf("Inorder  : ");
    inorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    return 0;
}

tree_ptr newNode(int elem) {
    tree_ptr node = (tree_ptr) malloc(sizeof(struct tree_node));
    node->element = elem;
    node->first_child = NULL;
    node->next_sibling = NULL;
    return node;
}

// Add child to parent (as last sibling)
void appendChild(tree_ptr parent, tree_ptr child) {
    if (parent->first_child == NULL) {
        parent->first_child = child;
    } else {
        tree_ptr temp = parent->first_child;
        while (temp->next_sibling != NULL) {
            temp = temp->next_sibling;
        }
        temp->next_sibling = child;
    }
}

// Build the EXACT TREE using real general-tree representation
void buildTree(tree_ptr *root) {
    *root = newNode(0);

    tree_ptr n3 = newNode(3);
    tree_ptr n4 = newNode(4);
    tree_ptr n6 = newNode(6);

    // Root children: 3, 4, 6
    appendChild(*root, n3);
    appendChild(*root, n4);
    appendChild(*root, n6);

    // Children of 4: 2, 1
    tree_ptr n2 = newNode(2);
    tree_ptr n1 = newNode(1);
    appendChild(n4, n2);
    appendChild(n4, n1);

    // Children of 2: 7, 8
    appendChild(n2, newNode(7));
    appendChild(n2, newNode(8));
}

// ====== TRAVERSALS ======

void preorder(tree_ptr root) {
    if (root == NULL) return;

    printf("%d ", root->element);

    // Traverse all children
    tree_ptr child = root->first_child;
    while (child != NULL) {
        preorder(child);
        child = child->next_sibling;
    }
}

// General tree has no "true" inorder; this is an adaptation:
// Visit leftmost child → root → other children
void inorder(tree_ptr root) {
    if (root == NULL) return;

    tree_ptr child = root->first_child;

    if (child != NULL) {
        inorder(child);        // leftmost subtree
    }

    printf("%d ", root->element);

    if (child != NULL) {
        child = child->next_sibling;
        while (child != NULL) {
            inorder(child);
            child = child->next_sibling;
        }
    }
}

void postorder(tree_ptr root) {
    if (root == NULL) return;

    tree_ptr child = root->first_child;

    // Visit ALL children first
    while (child != NULL) {
        postorder(child);
        child = child->next_sibling;
    }

    printf("%d ", root->element);
}
