#include <stdio.h>
#include <stdlib.h>
#include "hbtfun.h"
#include "hbt.h"
#define COUNT 10


void isBST(Tnode * node, int * BSTeval)  
{

    if (node == NULL)
    {
        return;
    }  

    if (node -> left != NULL)
    {
        if (node -> left -> key > node -> key)
        {
            (*BSTeval) = 0;
            return;
        }
    }

    if (node -> right != NULL)
    {
        if (node -> right -> key <= node -> key)
        {
            (*BSTeval) = 0;
            return;
        }
    }

    isBST(node -> left, BSTeval);
    isBST(node -> right, BSTeval);
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
    Tnode * unbal = root;
    Tnode * prevUnbal = NULL;

    while(current != NULL)
    {
        if (current -> balance != 0)
        {
            unbal = current;
        }
        if (newNode -> key <= current -> key)
        {
            if (current -> left == NULL)
            {
                current -> balance += 1;
                current -> left = newNode;
                current = current -> left -> left;
            }
            else if(current -> left -> balance == 0)
            {
                current -> balance += 1;
                current = current -> left;
            }
            else
            {
                current = current -> left;
            }  
        }
        else
        {
            if (current -> right == NULL)
            {
                current -> right = newNode;
                current -> balance -= 1;
                fprintf(stderr, "Null");
                current = current -> right -> right;
            }
            else if (current -> right -> balance == 0)
            {
                current -> balance -= 1;
                current = current -> right;
            }
            else
            {
                current = current -> right;
            }  
        }
    }

    return root;

   /* while(current != NULL)
    {
        if (current -> balance != 0)
        {
            unbal = current;
            prevUnbal = previous;
        }
        fprintf(stderr, "root: %d\n", root -> key);
        fprintf(stderr, "unbal: %d\n", unbal -> key);

        previous = current;

        if (current -> key >= newNode -> key)
        {
            current = current -> left;
        }
        else
        {
            current = current -> right;
        }

        if ((current == NULL) || (current -> balance == 0))
        {
            if (previous -> key >= newNode -> key)
            {
                previous -> balance += 1;
            }
            else
            {
                previous -> balance -= 1;
            }
        }
    }
    fprintf(stderr, "UNBAL\n");
    print2DUtil(unbal, 5);

    if (newNode -> key > previous -> key)
    {
        previous -> right = newNode;
    }
    else
    {
        previous -> left = newNode;
    }
    
    if (unbal -> balance > 1)
    {
        fprintf(stderr, "enter CW\n");
        previous = CWRotate(unbal, prevUnbal);
    }

    if (unbal -> balance < -1)
    {
        fprintf(stderr, "enter CCW\n");
        previous = CCWRotate(unbal, prevUnbal);
    }

    return root;*/
}

void destroyTree(Tnode * root) // frees tree
{
    if (root == NULL)
    {
        return;
    }
    destroyTree(root -> left);
    destroyTree(root -> right);
    free(root); // ensures branch is destroyed after recursion
}

Tnode * CCWRotate(Tnode * root, Tnode * prevUnbal)
{
    Tnode * newRoot = root -> right;
    fprintf(stderr, "newroot key: %d\n", newRoot -> key);
    Tnode * temp = newRoot -> left;

    if (newRoot -> balance > 0)
    {
        root = CWRotate(newRoot, root);
    }

    newRoot -> left = root;
    root -> right = temp;

    root -> balance += 2;
    newRoot -> balance += 1;

    if (prevUnbal != NULL)
    {
        fprintf(stderr, "enter if\n");
        if (prevUnbal -> right == root)
        {
            prevUnbal -> right = newRoot;
        }
        else
        {
            prevUnbal -> left = newRoot;
        }
    }
    fprintf(stderr, "newRoot: %d", newRoot -> key);

    return newRoot;
}

Tnode * CWRotate(Tnode * root, Tnode * prevUnbal)
{
    Tnode * newRoot = root -> left;
    fprintf(stderr, "newroot key: %d", newRoot -> key);
    Tnode * temp = newRoot -> right;

    if (newRoot -> balance < 0)
    {
        root = CCWRotate(newRoot, root);
    }

    newRoot -> right = root;
    root -> left = temp;

    root -> balance -= 2;
    newRoot -> balance -= 1;

    if (prevUnbal != NULL)
    {
        if (prevUnbal -> right == root)
        {
            prevUnbal -> right = newRoot;
        }
        else
        {
            prevUnbal -> left = newRoot;
        }
    }
    return newRoot;
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

Tnode * buildPreOrder(int * key_array, char * pattern_array, int index)
{
    Tnode * root = createNode(key_array[index]);

    if (pattern_array[index] == 3)
    {
        root -> left = buildPreOrder(key_array, pattern_array, index + 1);
        root -> right = buildPreOrder(key_array, pattern_array, index + 1);
    }
    else if (pattern_array[index] == 2)
    {
        root -> left = buildPreOrder(key_array, pattern_array, index + 1);
        root -> right = NULL;
    }
    else if (pattern_array[index] == 1)
    {
        root -> left = NULL;
        root -> right = buildPreOrder(key_array, pattern_array, index + 1);
    }
    else
    {
       root -> left = NULL;
       root -> right = NULL;
    }

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
