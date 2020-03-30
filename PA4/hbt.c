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

    insertNodeHelp(root, newNode, NULL);

    return (root);
}

void insertNodeHelp(Tnode * root, Tnode * newNode, Tnode * unbalNode)
{
    int leftBal = 0;
    int rightBal = 0;

    if (root -> balance == (-1 || 1))
    {
        unbalNode == root;
    }

    if (root -> key >= newNode -> key)
    {
        if (root -> left == NULL)
        {
            root -> left = newNode;
            findHeights(root -> left, &leftBal, &rightBal);
            root -> left -> balance = leftBal - rightBal;
            leftBal = rightBal = 0;
            findHeights(unbalNode, &leftBal, &rightBal);
            unbalNode -> balance = leftBal - rightBal;
            if (unbalNode -> balance < '-1' || unbalNode -> balance > '1')
            {
                if (unbalNode -> balance < '-1')
                {
                    CCWRotate(unbalNode);
                }
                else
                {
                    CWRotate(unbalNode);
                }
            }
            return;
        }
        else
        {
            insertNodeHelp(root -> left, newNode, unbalNode);
        }
    }
    else if (root -> key < newNode -> key)
    {
        if (root -> right == NULL)
        {
            root -> right = newNode;
            findHeights(root -> right, &leftBal, &rightBal);
            root -> right -> balance = leftBal - rightBal;
            leftBal = rightBal = 0;
            findHeights(unbalNode, &leftBal, &rightBal);
            unbalNode -> balance = leftBal - rightBal;
            if (unbalNode -> balance < '-1' || unbalNode -> balance > '1')
            {
                if (unbalNode -> balance < '-1')
                {
                    CCWRotate(unbalNode);
                }
                else
                {
                    CWRotate(unbalNode);
                }
            }
            return;
        }
        else
        {
            insertNodeHelp(root -> right, newNode, unbalNode);
        }
    }
}

void destroyTree(Tnode * root) // frees tree
{
    if (root -> left == NULL && root -> right == NULL)
    {
        free(root);
        return;
    }
    destroyTree(root -> left);
    destroyTree(root -> right);
    free(root); // ensures branch is destroyed after recursion
}

void CCWRotate(Tnode * root)
{
    Tnode * newRoot = root -> right;
    Tnode * temp = newRoot -> left;

    newRoot -> left = root;
    root -> right = temp;
}

void CWRotate(Tnode * root)
{
    Tnode * newRoot = root -> left;
    Tnode * temp = newRoot -> right;

    newRoot -> right = root;
    root -> left = temp;
}

void printPreOrder(char * filename, Tnode * root)
{
    FILE * fptr = fopen(filename, "wb");

    printPreOrderHelp(fptr, root);

    fclose(fptr);
}

void printPreOrderHelp(FILE * fptr, Tnode * root)
{
    if (root == NULL)
    {
        return;
    }

    char pattern = 0;

    if (root -> left == NULL)
    {
        if (root -> right == NULL)
        {
            pattern = 0x00;
        }
        else
        {
            pattern = 0x01;
        }   
    }
    else
    {
        if (root -> right == NULL)
        {
            pattern = 0x02;
        }
        else
        {
            pattern = 0x03;
        }
    }

    fwrite(root -> key, sizeof(int), 1, fptr);
    fwrite(&pattern, sizeof(char), 1, fptr);

    printPreOrderHelp(fptr, root -> left);
    printPreOrderHelp(fptr, root -> right);
        
}

void deleteNode(Tnode * root, int toDelete)
{
    if (toDelete < root -> key)
    {
        deleteNode(root -> left, toDelete);
    }
    else if (toDelete > root -> key)
    {
        deleteNode(root -> right, toDelete);
    }
    else
    {
        
    }
}
