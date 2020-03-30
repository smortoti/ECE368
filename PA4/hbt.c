#include <stdio.h>
#include <stdlib.h>
#include "hbtfun.h"
#include "hbt.h"
#define COUNT 10


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

    if ((root -> balance != -1) || (root -> balance != 0) || (root -> balance != 1))
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
    newNode -> balance = 0;
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

    Tnode * current = root;
    Tnode * previous = NULL;
    Tnode * unbal = NULL;
    Tnode * prevUnbal = NULL;

    while(current != NULL)
    {
        if (current -> key >= newNode -> key)
        {
            if (current -> left == NULL || current -> left -> balance == 0)
            {
                current -> balance += 1;
                unbal = current;
                prevUnbal = previous;
                previous = current;
                current = current -> left;

                if (current == NULL)
                {
                    previous -> left = newNode;
                }
            }
            else
            {
                unbal = current;
                prevUnbal = previous;
                previous = current;
                current = current -> left;

                if (current == NULL)
                {
                    previous -> left = newNode;
                }
            }
        }
        else
        {
            if (current -> right == NULL || current -> right -> balance == 0)
            {
                current -> balance -= 1;
                unbal = current;
                prevUnbal = previous;
                previous = current;
                current = current -> right;

                if (current == NULL)
                {
                    previous -> right = newNode;
                }
            }
            else
            {
                unbal = current;
                prevUnbal = previous;
                previous = current;
                current = current -> right;

                if (current == NULL)
                {
                    previous -> right = newNode;
                }
            }
        }
    }
    if (unbal -> balance > 1)
    {
        fprintf(stderr, "enter CW\n");
        CWRotate(unbal, prevUnbal);
    }

    if (unbal -> balance < -1)
    {
        fprintf(stderr, "enter CCW\n");
        CCWRotate(unbal, prevUnbal);
    }

    return root;
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

void CCWRotate(Tnode * root, Tnode * prevUnbal)
{
    Tnode * newRoot = root -> right;
    Tnode * temp = newRoot -> left;

    int leftBal = 0;
    int rightBal = 0;

    if (newRoot -> balance > 0)
    {
        CWRotate(newRoot, root);
        leftBal = 0;
        rightBal = 0;
    }

    newRoot -> left = root;
    root -> right = temp;

    findHeights(newRoot, &leftBal, &rightBal);
    newRoot -> balance = leftBal - rightBal;

    if (prevUnbal == NULL)
    {
        return;
    }

    if (prevUnbal -> right == root)
    {
        prevUnbal -> right = newRoot;
    }

    if (prevUnbal -> left == root)
    {
        prevUnbal -> left = newRoot;
    }

}

void CWRotate(Tnode * root, Tnode * prevUnbal)
{
    Tnode * newRoot = root -> left;
    Tnode * temp = newRoot -> right;

    int leftBal = 0;
    int rightBal = 0;

    if (newRoot -> balance < 0)
    {
        CCWRotate(newRoot, root);
        leftBal = 0;
        rightBal = 0;
    }

    newRoot -> right = root;
    root -> left = temp;

    findHeights(newRoot, &leftBal, &rightBal);
    newRoot -> balance = leftBal - rightBal;

    if (prevUnbal == NULL)
    {
        return;
    }

    if (prevUnbal -> right == root)
    {
        prevUnbal -> right = newRoot;
    }

    if (prevUnbal -> left == root)
    {
        prevUnbal -> left = newRoot;
    }

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

    fwrite(&(root -> key), sizeof(int), 1, fptr);
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

Tnode * buildPreOrder(int * key_array, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    Tnode * root = createNode(key_array[start]);

    int i = start;
    for (i = start; i <= end; i++)
    {
        if (key_array[i] > root -> key)
        {
            break;
        }
    }

    root -> left = buildPreOrder(key_array, start + 1, i - 1);
    root -> right = buildPreOrder(key_array, i, end);

    return root;
}

void print2DUtil(Tnode *root, int space) // debugging tree print function
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    fprintf(stderr, "\n"); 
    for (int i = COUNT; i < space; i++) 
        fprintf(stderr, " "); 
    fprintf(stderr, "%d, %d:\n", root->key, root -> balance); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
