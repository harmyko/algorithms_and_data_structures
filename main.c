#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

int main() 
{
    BinarySearchTree *tree = binarySearchTreeCreate();

    if (tree != NULL)
    {
        printf("Binary Search Tree created successfully\n");
    }  

    binarySearchTreeInsert(tree, 5);
    printf("\nElement 5 inserted\n");
    binarySearchTreeInsert(tree, 3);
    printf("Element 3 inserted\n");
    binarySearchTreeInsert(tree, 7);
    printf("Element 7 inserted\n"); 
    binarySearchTreeInsert(tree, 2);
    printf("Element 2 inserted\n");
    binarySearchTreeInsert(tree, 4);
    printf("Element 4 inserted\n");
    binarySearchTreeInsert(tree, 6);
    printf("Element 6 inserted\n");
    binarySearchTreeInsert(tree, 8);
    printf("Element 8 inserted\n");
    binarySearchTreeInsert(tree, 1);
    printf("Element 1 inserted\n");
    binarySearchTreeInsert(tree, 9);
    printf("Element 9 inserted\n");
    binarySearchTreeInsert(tree, 10);
    printf("Element 10 inserted\n\n");

    printf("Tree size: %d\n", count(tree));
    printf("Tree is empty: %d\n", isEmpty(tree));
    printf("Tree is full: %d\n", isFull(tree));

    char *treeString = toString(tree);
    printf("Tree: %s\n", treeString);
    free(treeString);

    binarySearchTreeRemove(tree, 5);
    printf("\nElement 5 removed\n");
    binarySearchTreeRemove(tree, 3);
    printf("Element 3 removed\n");
    binarySearchTreeRemove(tree, 7);
    printf("Element 7 removed\n");
    binarySearchTreeRemove(tree, 2);
    printf("Element 2 removed\n");
    binarySearchTreeRemove(tree, 4);
    printf("Element 4 removed\n\n");

    printf("Tree size: %d\n", count(tree));
    printf("Tree is empty: %d\n", isEmpty(tree));
    printf("Tree is full: %d\n", isFull(tree));
    
    treeString = toString(tree);
    printf("Tree before balancing: %s\n", treeString);
    free(treeString);

    printf("Tree root before balancing: %d\n\n", tree->root->value);
    balanceTree(tree);

    treeString = toString(tree);
    printf("Tree after balancing: %s\n", treeString);
    free(treeString);

    printf("Tree root after balancing: %d\n\n", tree->root->value);

    printf("Tree size: %d\n", count(tree));
    printf("Tree is empty: %d\n", isEmpty(tree));
    printf("Tree is full: %d\n\n", isFull(tree));

    BinarySearchTree *clonedTree = clone(tree);
    treeString = toString(clonedTree);
    printf("Cloned tree: %s\n", treeString);
    free(treeString);
    printf("Cloned tree size: %d\n", count(clonedTree));
    printf("Cloned tree is empty: %d\n", isEmpty(clonedTree));
    printf("Cloned tree root: %d\n\n", clonedTree->root->value);

    makeEmpty(tree);
    printf("Tree emptied\n");
    printf("Tree size: %d\n", count(tree));
    printf("Tree is empty: %d\n", isEmpty(tree));
    printf("Tree is full: %d\n\n", isFull(tree));

    binarySearchTreeDestroy(clonedTree);
    binarySearchTreeDestroy(tree);
    printf("Binary Search Trees destroyed\n");
    return 0;
}