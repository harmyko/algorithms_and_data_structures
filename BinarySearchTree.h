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

BinarySearchTree *binarySearchTree_create();
void binarySearchTree_destroy(BinarySearchTree *binarySearchTree);
void binarySearchTree_insert(BinarySearchTree *binarySearchTree, int value);
void binarySearchTree_remove(BinarySearchTree *binarySearchTree, int value);
int binarySearchTree_nodeCount(Node *node);
int binarySearchTree_count(BinarySearchTree *binarySearchTree);
int binarySearchTree_isEmpty(BinarySearchTree *binarySearchTree);
int binarySearchTree_isFull(BinarySearchTree *binarySearchTree);
char *binarySearchTree_toString(BinarySearchTree *binarySearchTree);
BinarySearchTree *binarySearchTree_clone(BinarySearchTree *binarySearchTree);
BinarySearchTree *binarySearchTree_makeEmpty(BinarySearchTree *binarySearchTree);
void binarySearchTree_balanceTree(BinarySearchTree *tree);
void binarySearchTree_nodeDestroy(Node *node);
Node *binarySearchTree_nodeInsert(Node *node, int value);
Node *binarySearchTree_nodeRemove(Node *node, int value);
void binarySearchTree_nodePrintToString(Node *node, char *binarySearchTreeString);
void binarySearchTree_storeInOrder(Node *node, int *arr, int *index);
Node *binarySearchTree_buildBalancedTree(int *arr, int start, int end);
void binarySearchTree_nodeClone(Node *node, Node **newNode);

#endif 
