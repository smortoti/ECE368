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

int getHeight(Tnode * root)
{
    if (root == NULL)
    {
        return 0;
    }

    int heightLeft = getHeight(root -> left);
    int heightRight = getHeight(root -> right);

    if (heightLeft > heightRight)
    {
        return (heightLeft + 1);
    }
    else
    {
       return (heightRight + 1);
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

Tnode * CCWRotate(Tnode * node)
{
	Tnode * left = node -> left;
	Tnode * rightSub = left -> right;

	left -> right = node;
	node -> left = rightSub;

	int leftHeight = getHeight(node -> left);
	int rightHeight = getHeight(node -> right);

	node -> balance = leftHeight - rightHeight;

	leftHeight = getHeight(left -> left);
	rightHeight = getHeight(left -> right);

	left -> balance = leftHeight - rightHeight;

    return left;
}

Tnode * CWRotate(Tnode * node)
{
	Tnode * right = node -> right;
	Tnode * leftSub = right -> left;

	right -> left = node;
	node -> right = leftSub;

	int leftHeight = getHeight(node -> left);
	int rightHeight = getHeight(node -> right);

	node -> balance = leftHeight - rightHeight;

	leftHeight = getHeight(right -> left);
	rightHeight = getHeight(right -> right);
	
	right -> balance = leftHeight - rightHeight;

	return right;
}

Tnode * insertNode(Tnode * root, Tnode * newNode)
{
	if (root == NULL)
	{
		return newNode;
	}

	if (newNode -> key <= root -> key)
	{
		root -> left = insertNode(root -> left, newNode);
	}

	else
	{
		root -> right = insertNode(root -> right, newNode);
	}

	int leftHeight = getHeight(root -> left);
	int rightHeight = getHeight(root -> right);
	
	root -> balance = leftHeight - rightHeight;

	if (root -> balance > 1 && newNode -> key < root -> left -> key)
	{
		return CCWRotate(root);

	}
	
	if (root -> balance < -1 && newNode -> key > root -> right -> key)
	{
		return CWRotate(root);
	}

	if (root -> balance > 1 && newNode -> key > root -> left -> key)
	{
		root -> left = CWRotate(root -> left);
		return CCWRotate(root);
	}

	if (root -> balance < -1 && newNode -> key < root -> right -> key)
	{
		root -> right = CCWRotate(root -> right);
		return CWRotate(root);
	}

	return root;
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

int getBalance(Tnode * root)
{
	if (root == NULL)
	{
		return 0;
	}
	return (getHeight(root -> left) - getHeight(root -> right));
}


Tnode * predecessor(Tnode * root)
{
	Tnode * current = root;

	while (current -> left != NULL)
	{
		current = current -> left;
	}

	return current;
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
	fprintf(stderr, "key: %d bal: %d\n", root -> key, root -> balance);

    fwrite(&(root -> key), sizeof(int), 1, fptr);
    fwrite(&pattern, sizeof(char), 1, fptr);

    printPreOrderHelp(fptr, root -> left);
    printPreOrderHelp(fptr, root -> right);
        
}

Tnode * deleteNode(Tnode * root, int toDelete)
{
    if (root == NULL)
	{
		return root;
	}

	if (toDelete < root -> key)
	{
		root -> left = deleteNode(root -> left, toDelete);
	}

	else if (toDelete > root -> key)
	{
		root -> right = deleteNode(root -> right, toDelete);
	}

	else
	{
		fprintf(stderr, "enter delete\n");
		if ((root -> left == NULL) || (root -> right == NULL))
		{
			Tnode * temp = root -> left ? root -> left : root -> right;

			if (temp == NULL)
			{
				fprintf(stderr, "temp is Null\n");
				temp = root;
				root = NULL;
			}
			else
			{
				fprintf(stderr, "copy over\n");
				*root = *temp;
			}
			
			free(temp);
		}
		else
		{
			fprintf(stderr, "find predecessor\n");
			Tnode * temp = predecessor(root);

			root -> key = temp -> key;
			root -> right = deleteNode(root -> right, temp -> key);
		}
	}

	if (root == NULL)
	{
		return root;
	}

	int leftHeight = getHeight(root -> left);
	int rightHeight = getHeight(root -> right);

	root -> balance = leftHeight - rightHeight;

	if (root -> balance > 1 && getBalance(root -> left) >= 0)
	{
		return CCWRotate(root);
	}

	if (root -> balance > 1 && getBalance(root -> left) < 0)
	{
		root -> left = CWRotate(root -> left);
		return CCWRotate(root);
	}

	if (root -> balance < -1 && getBalance(root -> right) <= 0)
	{
		return CWRotate(root);
	}

	if (root -> balance < -1 && getBalance(root -> right) > 0)
	{
		root -> right = CCWRotate(root -> right);
		return CWRotate(root);
	}

	return root;
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
