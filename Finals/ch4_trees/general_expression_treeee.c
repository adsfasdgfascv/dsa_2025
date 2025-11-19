/******************************************************************************
 * PROGRAM: Expression Tree Implementation (First Child / Next Sibling)
 * 
 * COURSE: Data Structures and Algorithms
 * TOPIC: Expression Trees – First Child / Next Sibling Representation
 * 
 * AUTHOR: Gabieta, Mark Anthony
 * DATE: November 19, 2025
 * VERSION: 3.0
 * 
 *****************************************************************************
 * 
 * PROGRAM DESCRIPTION:
 * This program implements an EXPRESSION TREE using the First Child / Next Sibling
 * model. Each node stores either an operator (+,-,*,/) or an operand (number).
 * 
 * The program constructs the following expression tree:
 * 
 *              +
 *            / | \
 *           3  *  6
 *             / \
 *            -   1
 *           / \
 *          7   8
 * 
 * Traversals correspond to:
 *  - Preorder  : Prefix expression
 *  - Inorder   : Infix expression
 *  - Postorder : Postfix expression
 * 
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree_node {
    char* element;                   // operator or operand
    struct tree_node *first_child;   // leftmost child
    struct tree_node *next_sibling;  // next sibling
} *tree_ptr;

// Function prototypes
tree_ptr newNode(const char* elem);
void appendChild(tree_ptr parent, tree_ptr child);
void buildTree(tree_ptr *root);

void preorder(tree_ptr root);
void inorder(tree_ptr root);
void postorder(tree_ptr root);
void printTree(tree_ptr root, int depth);

int main() {
    tree_ptr root = NULL;
    buildTree(&root);

    printf("EXPRESSION TREE (First Child / Next Sibling)\n\n");

    printf("Tree visualization:\n");
    printTree(root, 0);
    printf("\n");

    printf("Preorder (Prefix): ");
    preorder(root);
    printf("\n");

    printf("Inorder (Infix) : ");
    inorder(root);
    printf("\n");

    printf("Postorder (Postfix): ");
    postorder(root);
    printf("\n");

    return 0;
}

tree_ptr newNode(const char* elem) {
    tree_ptr node = (tree_ptr) malloc(sizeof(struct tree_node));
    node->element = strdup(elem);  // copy string
    node->first_child = NULL;
    node->next_sibling = NULL;
    return node;
}

void appendChild(tree_ptr parent, tree_ptr child) {
    if (!parent->first_child) {
        parent->first_child = child;
    } else {
        tree_ptr temp = parent->first_child;
        while (temp->next_sibling) temp = temp->next_sibling;
        temp->next_sibling = child;
    }
}

void buildTree(tree_ptr *root) {
    *root = newNode("+");    // root operator

    tree_ptr n3 = newNode("3");
    tree_ptr nMul = newNode("*");
    tree_ptr n6 = newNode("6");

    appendChild(*root, n3);
    appendChild(*root, nMul);
    appendChild(*root, n6);

    tree_ptr nSub = newNode("-");
    tree_ptr n1 = newNode("1");

    appendChild(nMul, nSub);
    appendChild(nMul, n1);

    appendChild(nSub, newNode("7"));
    appendChild(nSub, newNode("8"));
}

// ====== Traversals ======
void preorder(tree_ptr root) {
    if (!root) return;
    printf("%s ", root->element);
    tree_ptr child = root->first_child;
    while (child) {
        preorder(child);
        child = child->next_sibling;
    }
}

void inorder(tree_ptr root) {
    if (!root) return;
    tree_ptr child = root->first_child;
    if (child) inorder(child); // leftmost child
    printf("%s ", root->element);
    if (child) {
        child = child->next_sibling;
        while (child) {
            inorder(child);
            child = child->next_sibling;
        }
    }
}

void postorder(tree_ptr root) {
    if (!root) return;
    tree_ptr child = root->first_child;
    while (child) {
        postorder(child);
        child = child->next_sibling;
    }
    printf("%s ", root->element);
}

// ====== Print Tree Vertically ======
void printTree(tree_ptr root, int depth) {
    if (!root) return;
    for (int i = 0; i < depth; i++) printf("    "); // indent
    printf("%s\n", root->element);

    tree_ptr child = root->first_child;
    while (child) {
        printTree(child, depth + 1);
        child = child->next_sibling;
    }
}
