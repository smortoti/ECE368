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
        return 0;
    }

    int leftBal = isBal(root -> left);
    int rightBal = isBal(root -> right);

    if (leftBal > rightBal)
    {
        return (leftBal + 1);
    }
    else
    {
       return (rightBal + 1);
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
    if (root -> key >= newNode -> key)
    {
        if (root -> left == NULL)
        {
            root -> left = newNode;
            return;
        }
        else
        {
            insertNodeHelp(root -> left, newNode);
        }
    }
    if (root -> key < newNode -> key)
    {
        if (root -> right == NULL)
        {
            root -> right = newNode;
            return;
        }
        else
        {
            insertNodeHelp(root -> right, newNode);
        }
        
    }
}