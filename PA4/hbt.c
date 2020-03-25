#include <stdio.h>
#include <stdlib.h>
#include "hbtfun.h"
#include "hbt.h"


int isBST(Tnode * node, int min, int max)  
{
    if (node == NULL)
    {
        return 1;
    }  

    if (node -> key < min || node -> key > max)  
    {
        return 0;
    }

    return (isBST(node -> left, min, node -> key - 1) && isBST(node -> right, node -> key + 1, max));  // Allow only distinct values 
}  

int isBal(Tnode * root)
{
    if (root == NULL)
    {
        return 1;
    }

    if (root -> balance != ('-1' || '0' || '1'))
    {
        return 0;
    }

    return (isBal(root -> left) && (isBal(root -> right)));
}

void findHeights(Tnode * root, int * leftBal, int * rightBal)
{
    if (root == NULL)
    {
        return;
    }

    findHeights(root -> left, leftBal, rightBal);
    findHeights(root -> right, leftBal, rightBal);

    if (leftBal > rightBal)
    {
        (*leftBal)++;
    }
    else
    {
       (*rightBal)++;
    }
}

Tnode * createNode(int key)
{
    Tnode * newNode = malloc(sizeof(*newNode));

    newNode -> key = key;
    newNode -> balance = '0';
    newNode -> left = NULL;
    newNode -> right = NULL;

    return newNode;
}

Tnode * insertNode(Tnode * root, Tnode * newNode)
{

    if (root == NULL)
    {
        return newNode;
    }

    insertNodeHelp(root, newNode);

    return (root);
}

void insertNodeHelp(Tnode * root, Tnode * newNode)
{
    int leftBal = 0;
    int rightBal = 0;

    if (root -> key >= newNode -> key)
    {
        if (root -> left == NULL)
        {
            root -> left = newNode;
            findHeights(root -> left, &leftBal, &rightBal);
            root -> left -> balance = leftBal - rightBal;
            return;
        }
        else
        {
            insertNodeHelp(root -> left, newNode);
            return;
        }
    }
    if (root -> key < newNode -> key)
    {
        if (root -> right == NULL)
        {
            root -> right = newNode;
            findHeights(root -> right, &leftBal, &rightBal);
            root -> right -> balance = leftBal - rightBal;
            return;
        }
        else
        {
            insertNodeHelp(root -> right, newNode);
            return;
        }
        
    }
}