#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

int main() 
{
    BinarySearchTree *tree = binarySearchTree_create();

    if (tree != NULL)
    {
        printf("Binary Search Tree created successfully\n");
    }  

    binarySearchTree_insert(tree, 5);
    printf("\nElement 5 inserted\n");
    binarySearchTree_insert(tree, 3);
    printf("Element 3 inserted\n");
    binarySearchTree_insert(tree, 7);
    printf("Element 7 inserted\n"); 
    binarySearchTree_insert(tree, 2);
    printf("Element 2 inserted\n");
    binarySearchTree_insert(tree, 4);
    printf("Element 4 inserted\n");
    binarySearchTree_insert(tree, 6);
    printf("Element 6 inserted\n");
    binarySearchTree_insert(tree, 8);
    printf("Element 8 inserted\n");
    binarySearchTree_insert(tree, 1);
    printf("Element 1 inserted\n");
    binarySearchTree_insert(tree, 9);
    printf("Element 9 inserted\n");
    binarySearchTree_insert(tree, 10);
    printf("Element 10 inserted\n\n");

    printf("Tree size: %d\n", binarySearchTree_count(tree));
    printf("Tree is empty: %d\n", binarySearchTree_isEmpty(tree));
    printf("Tree is full: %d\n", binarySearchTree_isFull(tree));

    char *treeString = binarySearchTree_toString(tree);
    printf("Tree: %s\n", treeString);
    free(treeString);

    binarySearchTree_remove(tree, 5);
    printf("\nElement 5 removed\n");
    binarySearchTree_remove(tree, 3);
    printf("Element 3 removed\n");
    binarySearchTree_remove(tree, 7);
    printf("Element 7 removed\n");
    binarySearchTree_remove(tree, 2);
    printf("Element 2 removed\n");
    binarySearchTree_remove(tree, 4);
    printf("Element 4 removed\n\n");

    printf("Tree size: %d\n", binarySearchTree_count(tree));
    printf("Tree is empty: %d\n", binarySearchTree_isEmpty(tree));
    printf("Tree is full: %d\n", binarySearchTree_isFull(tree));
    
    treeString = binarySearchTree_toString(tree);
    printf("Tree before balancing: %s\n", treeString);
    free(treeString);

    printf("Tree root before balancing: %d\n\n", tree->root->value);
    binarySearchTree_balanceTree(tree);

    treeString = binarySearchTree_toString(tree);
    printf("Tree after balancing: %s\n", treeString);
    free(treeString);

    printf("Tree root after balancing: %d\n\n", tree->root->value);

    printf("Tree size: %d\n", binarySearchTree_count(tree));
    printf("Tree is empty: %d\n", binarySearchTree_isEmpty(tree));
    printf("Tree is full: %d\n\n", binarySearchTree_isFull(tree));

    BinarySearchTree *clonedTree = binarySearchTree_clone(tree);
    treeString = binarySearchTree_toString(clonedTree);
    printf("Cloned tree: %s\n", treeString);
    free(treeString);
    printf("Cloned tree size: %d\n", binarySearchTree_count(clonedTree));
    printf("Cloned tree is empty: %d\n", binarySearchTree_isEmpty(clonedTree));
    printf("Cloned tree root: %d\n\n", clonedTree->root->value);

    binarySearchTree_makeEmpty(tree);
    printf("Tree emptied\n");
    printf("Tree size: %d\n", binarySearchTree_count(tree));
    printf("Tree is empty: %d\n", binarySearchTree_isEmpty(tree));
    printf("Tree is full: %d\n\n", binarySearchTree_isFull(tree));

    binarySearchTree_destroy(clonedTree);
    binarySearchTree_destroy(tree);
    printf("Binary Search Trees destroyed\n");
    return 0;
}