#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#define STRING_LENGTH 100

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinarySearchTree {
    Node *root;
} BinarySearchTree;

BinarySearchTree *binarySearchTreeCreate();
void binarySearchTreeDestroy(BinarySearchTree *binarySearchTree);
void binarySearchTreeInsert(BinarySearchTree *binarySearchTree, int value);
void binarySearchTreeRemove(BinarySearchTree *binarySearchTree, int value);
int nodeCount(Node *node);
int count(BinarySearchTree *binarySearchTree);
int isEmpty(BinarySearchTree *binarySearchTree);
int isFull(BinarySearchTree *binarySearchTree);
char *toString(BinarySearchTree *binarySearchTree);
BinarySearchTree *clone(BinarySearchTree *binarySearchTree);
BinarySearchTree *makeEmpty(BinarySearchTree *binarySearchTree);
void balanceTree(BinarySearchTree *tree);
void nodeDestroy(Node *node);
Node *nodeInsert(Node *node, int value);
Node *nodeRemove(Node *node, int value);
void nodePrintToString(Node *node, char *binarySearchTreeString);
void storeInOrder(Node *node, int *arr, int *index);
Node *buildBalancedTree(int *arr, int start, int end);
void nodeClone(Node *node, Node **newNode);

#endif 
