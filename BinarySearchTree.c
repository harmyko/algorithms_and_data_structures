#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The maximum length of the string that will be returned by the binarySearchTree_toString function
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
BinarySearchTree *binarySearchTree_create()
{
    BinarySearchTree *newBinarySearchTree = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));

    if (newBinarySearchTree == NULL)
    {
        return NULL;
    }

    newBinarySearchTree->root = NULL;

    return newBinarySearchTree;
}

// Helper function of binarySearchTree_destroy
void binarySearchTree_nodeDestroy(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    binarySearchTree_nodeDestroy(node->left);
    binarySearchTree_nodeDestroy(node->right);

    free(node);
}

// Destroys a Binary Search Tree
void binarySearchTree_destroy(BinarySearchTree *binarySearchTree)
{
    binarySearchTree_nodeDestroy(binarySearchTree->root);
    free(binarySearchTree);
}

// Helper function of binarySearchTree_Insert
Node *binarySearchTree_nodeInsert(Node *node, int value)
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
        node->left = binarySearchTree_nodeInsert(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = binarySearchTree_nodeInsert(node->right, value);
    }

    return node;
}

// Inserts a new value into the Binary Search Tree
void binarySearchTree_insert(BinarySearchTree *binarySearchTree, int value)
{
    Node *newNode = binarySearchTree_nodeInsert(binarySearchTree->root, value);

    if (binarySearchTree->root == NULL)
    {
        binarySearchTree->root = newNode;
    }
}

// Helper function of binarySearchTree_count
int binarySearchTree_nodeCount(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return 1 + binarySearchTree_nodeCount(node->left) + binarySearchTree_nodeCount(node->right);
}

// Returns the number of elements in a Binary Search Tree
int binarySearchTree_count(BinarySearchTree *binarySearchTree)
{
    return binarySearchTree_nodeCount(binarySearchTree->root);
}

// Checks if the tree contains zero elements
int binarySearchTree_isEmpty(BinarySearchTree *binarySearchTree)
{
    if (binarySearchTree_count(binarySearchTree) == 0)
    {
        return 1;
    }

    return 0;
}

// Checks if no more nodes can be added to the tree
int binarySearchTree_isFull(BinarySearchTree *binarySearchTree)
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
void binarySearchTree_nodePrintToString(Node *node, char *binarySearchTreeString)
{
    if (node == NULL)
    {
        return;
    }

    binarySearchTree_nodePrintToString(node->left, binarySearchTreeString);

    char *buffer = (char *)malloc(sizeof(char) * 20);
    sprintf(buffer, "%d ", node->value);
    strcat(binarySearchTreeString, buffer);

    binarySearchTree_nodePrintToString(node->right, binarySearchTreeString);
}

// Returns a string representation of the Binary Search Tree
char *binarySearchTree_toString(BinarySearchTree *binarySearchTree)
{
    char *binarySearchTreeString = (char *)malloc(sizeof(char) * STRING_LENGTH);

    if (binarySearchTreeString == NULL)
    {
        return NULL;
    }

    binarySearchTreeString[0] = '\0';

    binarySearchTree_nodePrintToString(binarySearchTree->root, binarySearchTreeString);

    return binarySearchTreeString;
}

// Helper function of binarySearchTree_clone
void binarySearchTree_nodeClone(Node *node, Node **newNode)
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

    binarySearchTree_nodeClone(node->left, &((*newNode)->left));
    binarySearchTree_nodeClone(node->right, &((*newNode)->right));
}

// Clones a Binary Search Tree
BinarySearchTree *binarySearchTree_clone(BinarySearchTree *binarySearchTree)
{
    if (binarySearchTree == NULL)
    {
        return NULL;
    }

    BinarySearchTree *newBinarySearchTree = binarySearchTree_create();

    if (newBinarySearchTree == NULL)
    {
        return NULL;
    }

    binarySearchTree_nodeClone(binarySearchTree->root, &(newBinarySearchTree->root));

    return newBinarySearchTree;
}

// Removes all nodes from a Binary Search Tree
BinarySearchTree *binarySearchTree_makeEmpty(BinarySearchTree *binarySearchTree)
{
    binarySearchTree_nodeDestroy(binarySearchTree->root);
    binarySearchTree->root = NULL;
    return binarySearchTree;
}

// Removes a node from a Binary Search Tree
Node *binarySearchTree_nodeRemove(Node *node, int value)
{
    if (node == NULL)
    {
        return NULL;
    }

    if (value < node->value)
    {
        node->left = binarySearchTree_nodeRemove(node->left, value);
    }
    else if (value > node->value)
    {
        node->right = binarySearchTree_nodeRemove(node->right, value);
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
        node->right = binarySearchTree_nodeRemove(node->right, tempNode->value);
    }

    return node;
}

// Removes a value from a Binary Search Tree
void binarySearchTree_remove(BinarySearchTree *binarySearchTree, int value)
{
    if (binarySearchTree == NULL || binarySearchTree->root == NULL)
    {
        return;
    }

    binarySearchTree->root = binarySearchTree_nodeRemove(binarySearchTree->root, value);
}

// Stores the values of the nodes in the tree in an array in in-order traversal
void binarySearchTree_storeInOrder(Node *node, int *arr, int *index)
{
    if (node == NULL)
    {
        return;
    }

    binarySearchTree_storeInOrder(node->left, arr, index);
    arr[(*index)++] = node->value;
    binarySearchTree_storeInOrder(node->right, arr, index);
}

// Helper function of binarySearchTree_balanceTree
Node *binarySearchTree_buildBalancedTree(int *arr, int start, int end)
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
    newNode->left = binarySearchTree_buildBalancedTree(arr, start, mid - 1);
    newNode->right = binarySearchTree_buildBalancedTree(arr, mid + 1, end);

    return newNode;
}

// Balances a Binary Search Tree
void binarySearchTree_balanceTree(BinarySearchTree *tree)
{
    if (tree == NULL || tree->root == NULL)
    {
        return;
    }
 
    int *arr = (int *)malloc(sizeof(int) * binarySearchTree_count(tree));
    if (arr == NULL)
    {
        return;
    }

    int index = 0;
    binarySearchTree_storeInOrder(tree->root, arr, &index);

    binarySearchTree_nodeDestroy(tree->root);
    tree->root = binarySearchTree_buildBalancedTree(arr, 0, binarySearchTree_count(tree) - 1);

    free(arr);
}

