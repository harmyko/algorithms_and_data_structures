#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The maximum length of the string that will be returned by the toString function
#define STRING_LENGTH 100

// A node in a Binary Search Tree
typedef struct Node
{
    int value;
    struct Node *left;
    struct Node *right;
} Node;

// A Binary Search Tree
typedef struct BinarySearchTree
{
    Node *root;
} BinarySearchTree;

// Creates a new Binary Search Tree
BinarySearchTree *binarySearchTreeCreate()
{
    BinarySearchTree *newBinarySearchTree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));

    if (newBinarySearchTree == NULL)
    {
        return NULL;
    }

    newBinarySearchTree->root = NULL;

    return newBinarySearchTree;
}

// Destroys a node and all its children
void nodeDestroy(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    nodeDestroy(node->left);
    nodeDestroy(node->right);

    free(node);
}

// Destroys a Binary Search Tree
void binarySearchTreeDestroy(BinarySearchTree *binarySearchTree)
{
    nodeDestroy(binarySearchTree->root);
    free(binarySearchTree);
}

// Inserts a new value into the Binary Search Tree
Node *nodeInsert(Node *node, int value)
{
    if (node == NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));

        if (newNode == NULL)
        {
            return NULL;
        }

        newNode->value = value;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (value == node->value)
    {
        return node;
    }

    if (value < node->value)
    {
        node->left = nodeInsert(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = nodeInsert(node->right, value);
    }

    return node;
}

// Inserts a new value into the Binary Search Tree
void binarySearchTreeInsert(BinarySearchTree *binarySearchTree, int value)
{
    Node *newNode = nodeInsert(binarySearchTree->root, value);

    if (binarySearchTree->root == NULL)
    {
        binarySearchTree->root = newNode;
    }
}

// Returns the number of elements in a node
int nodeCount(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return 1 + nodeCount(node->left) + nodeCount(node->right);
}

// Returns the number of elements in a Binary Search Tree
int count(BinarySearchTree *binarySearchTree)
{
    return nodeCount(binarySearchTree->root);
}

// Checks if the tree contains zero elements
int isEmpty(BinarySearchTree *binarySearchTree)
{
    if (count(binarySearchTree) == 0)
    {
        return 1;
    }

    return 0;
}

// Checks if no more nodes can be added to the tree
int isFull(BinarySearchTree *binarySearchTree)
{
    Node *tempNode = (Node *)malloc(sizeof(Node));

    if (tempNode == NULL)
    {
        return 1;
    }

    free(tempNode);
    return 0;
}

// Prints the values of the nodes in the tree to a string
void nodePrintToString(Node *node, char *binarySearchTreeString)
{
    if (node == NULL)
    {
        return;
    }

    nodePrintToString(node->left, binarySearchTreeString);

    char *buffer = (char *)malloc(sizeof(char) * 20);
    sprintf(buffer, "%d ", node->value);
    strcat(binarySearchTreeString, buffer);

    nodePrintToString(node->right, binarySearchTreeString);
}

// Returns a string representation of the Binary Search Tree
char *toString(BinarySearchTree *binarySearchTree)
{
    char *binarySearchTreeString = (char *)malloc(sizeof(char) * STRING_LENGTH);

    if (binarySearchTreeString == NULL)
    {
        return NULL;
    }

    binarySearchTreeString[0] = '\0';

    nodePrintToString(binarySearchTree->root, binarySearchTreeString);

    return binarySearchTreeString;
}

// Clones a node and all its children
void nodeClone(Node *node, Node **newNode)
{
    if (node == NULL)
    {
        *newNode = NULL;
        return;
    }

    *newNode = (Node *)malloc(sizeof(Node));

    if (*newNode == NULL)
    {
        return;
    }

    (*newNode)->value = node->value;
    (*newNode)->left = NULL;
    (*newNode)->right = NULL;

    nodeClone(node->left, &((*newNode)->left));
    nodeClone(node->right, &((*newNode)->right));
}

// Clones a Binary Search Tree
BinarySearchTree *clone(BinarySearchTree *binarySearchTree)
{
    if (binarySearchTree == NULL)
    {
        return NULL;
    }

    BinarySearchTree *newBinarySearchTree = binarySearchTreeCreate();

    if (newBinarySearchTree == NULL)
    {
        return NULL;
    }

    nodeClone(binarySearchTree->root, &(newBinarySearchTree->root));

    return newBinarySearchTree;
}

// Removes all nodes from a Binary Search Tree
BinarySearchTree *makeEmpty(BinarySearchTree *binarySearchTree)
{
    nodeDestroy(binarySearchTree->root);
    binarySearchTree->root = NULL;
    return binarySearchTree;
}

// Removes a node from a Binary Search Tree
Node *nodeRemove(Node *node, int value)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (value < node->value)
    {
        node->left = nodeRemove(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = nodeRemove(node->right, value);
    }
    else if (node->value == value)
    {
        if (node->left == NULL && node->right == NULL)
        {
            free(node);
            return NULL;
        }

        if (node->left == NULL)
        {
            Node *tempNode = node->right;
            free(node);
            return tempNode;
        }

        if (node->right == NULL)
        {
            Node *tempNode = node->left;
            free(node);
            return tempNode;
        }

        Node *tempNode = node->right;

        while (tempNode->left != NULL)
        {
            tempNode = tempNode->left;
        }

        node->value = tempNode->value;
        node->right = nodeRemove(node->right, tempNode->value);
    }

    return node;
}

// Removes a value from a Binary Search Tree
void binarySearchTreeRemove(BinarySearchTree *binarySearchTree, int value)
{
    if (binarySearchTree == NULL || binarySearchTree->root == NULL)
    {
        return;
    }

    binarySearchTree->root = nodeRemove(binarySearchTree->root, value);
}

// Stores the values of the nodes in the tree in an array in in-order traversal
void storeInOrder(Node *node, int *arr, int *index)
{
    if (node == NULL)
    {
        return;
    }

    storeInOrder(node->left, arr, index);
    arr[(*index)++] = node->value;
    storeInOrder(node->right, arr, index);
}

// Builds a balanced Binary Search Tree from a sorted array
Node *buildBalancedTree(int *arr, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    int mid = (start + end) / 2;
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        return NULL;
    }

    newNode->value = arr[mid];
    newNode->left = buildBalancedTree(arr, start, mid - 1);
    newNode->right = buildBalancedTree(arr, mid + 1, end);

    return newNode;
}

// Balances a Binary Search Tree
void balanceTree(BinarySearchTree *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        return;
    }
 
    int *arr = (int *)malloc(sizeof(int) * count(tree));
    if (arr == NULL)
    {
        return;
    }

    int index = 0;
    storeInOrder(tree->root, arr, &index);

    nodeDestroy(tree->root);
    tree->root = buildBalancedTree(arr, 0, count(tree) - 1);

    free(arr);
}

