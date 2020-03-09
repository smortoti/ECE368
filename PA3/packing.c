#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "packing.h"
#define COUNT 10

Tree * buildTreeFromPostOrder(char * filename, int * upper_bound)
{
    FILE * fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        return NULL;
    }

    int readTemp = 0;
    List * head = NULL;
    int position = 0;
    int label = 0;
    int width = 0;
    int height = 0;
    Tree ** treeArray = NULL;
    int size = 1;
    Tree * tree = NULL;

    while(!(feof(fptr)))
    {
        readTemp = fgetc(fptr);
        if (readTemp == 'H' || readTemp == 'V')
        {
            if(!(feof(fptr)))
            {
                head = createNode(head, readTemp, 0, 0);
                readTemp = fgetc(fptr);
            }
        }
        else
        {
            if(!(feof(fptr)))
            {
                position = ftell(fptr);
                fseek(fptr, (long) (position - 1), SEEK_SET);
                fscanf(fptr, "%d(%d,%d)\n", &label, &width, &height);
                if(readTemp != '\n')
                {
                    head = createNode(head, label, width, height);
                }

            }
        }    
    }

    treeArray = LLtoArray(head, &size);

    if (treeArray == NULL)
    {
        fclose(fptr);
        return NULL;
    }

    (*upper_bound) = size - 1;

    tree = constructTree(treeArray, upper_bound);

    free(treeArray);
    
    fclose(fptr);

    return(tree);
}

Tree ** LLtoArray(List * head, int * size)
{
    List * temp = head;

    if (head == NULL)
    {
        return NULL;
    }
    
    while(temp -> next != NULL)
    {
        temp = temp -> next;
        (*size)++;
    }

    Tree ** treeArray = malloc(sizeof(*treeArray) * (*size));
    if (treeArray == NULL)
    {
        fprintf(stderr, "treeArray is NULL\n");
    }
    int i = 0;
    temp = head;

    for(i = 0; i < (*size); i++)
    {
        treeArray[i] = malloc(sizeof(*treeArray[i]));
        treeArray[i] -> label = temp -> label;
        treeArray[i] -> height = temp -> height;
        treeArray[i] -> width = temp -> width;
        treeArray[i] -> nodeLabel = temp -> nodeLabel;
        treeArray[i] -> left = treeArray[i] -> right = NULL;
        temp = temp -> next;
    }
    freeLL(head);
    return(treeArray);
}

List * createNode(List * head, int label, int width, int height)
{
    if (head == NULL)
    {
        List * temp = malloc(sizeof(*temp));

        temp -> label = label;
        temp -> height = height;
        temp -> width = width;
        if (height == 0 && width == 0)
        {
            temp -> nodeLabel = 'B';
        }
        else
        {
            temp -> nodeLabel = 'L';
        }
        temp -> next = NULL;
        temp -> previous = NULL;

        head = temp;

        return(head);
    }

    List * newNode = malloc(sizeof(*newNode));
    List * temp = head;

    while (temp -> next != NULL)
    {
        temp = temp -> next;
    }

    newNode -> label = label;
    newNode -> height = height;
    newNode -> width = width;

    if (height == 0 && width == 0)
    {
        newNode -> nodeLabel = 'B';
    }
    else
    {
        newNode -> nodeLabel = 'L';
    }
    newNode -> next = NULL;
    newNode -> previous = temp;
    temp -> next = newNode;

    return(head);
}

void freeLL(List * head)
{
    List * temp = head -> next;
    while(temp != NULL)
    {
        free(head);
        head = temp;
        temp = temp -> next;
    }
    free(head);
}

Tree * constructTree(Tree ** treeArray, int * upper_bound)
{
    Tree * root = treeArray[(*upper_bound)];

    if (root == NULL)
    {
        fprintf(stderr, "NULL\n");
    }

    if ((root -> nodeLabel) == 'B')
    {
        if (treeArray[(*upper_bound - 1)] -> nodeLabel == 'B')
        {
            (*upper_bound)--;
            root -> right = constructTree(treeArray, upper_bound);
        }
        else
        {
            (*upper_bound)--;
            root -> right = treeArray[(*upper_bound)];
        }

        if (treeArray[(*upper_bound - 1)] -> nodeLabel == 'B')
        {
            (*upper_bound)--;
            root -> left = constructTree(treeArray, upper_bound);
        }
        else
        {
            (*upper_bound)--;
            root -> left = treeArray[(*upper_bound)];
        }  
    }
    if (root -> nodeLabel == 'B')
    {
        if (root -> label == 'H')
        {
            root -> height = root -> left -> height + root -> right -> height;
            if (root -> left -> width > root -> right -> width)
            {
                root -> width = root -> left -> width;
            }
            else
            {
                root -> width = root -> right -> width;
            }   
        }
        else if(root -> label == 'V')
        {
            root -> width = root -> left -> width + root -> right -> width;
            if (root -> left -> height > root -> right -> height)
            {
                root -> height = root -> left -> height;
            }
            else
            {
                root -> height = root -> right -> height;
            }   
        }
    }
    return (root);
}

void printPreOrder(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, "w");

    printTreeNode(fptr, root);

    fclose(fptr);

}

void printTreeNode(FILE * fptr, Tree * root)
{
    if(root == NULL)
    {
        return;
    }
    if(root -> nodeLabel == 'B')
    {
        fprintf(fptr, "%c\n", root -> label);
    }
    else
    {
        fprintf(fptr, "%d(%d,%d)\n", root -> label, root -> width, root -> height);
    }

    printTreeNode(fptr, root -> left);
    printTreeNode(fptr, root -> right);
}

void printDimensions(char * filename, Tree * root) // JOB SECURITY (LEVEL 1)
{
    FILE * fptr = fopen(filename, "w");

    printDimHelper(fptr, root);

    fclose(fptr);
}

void printDimHelper(FILE * fptr, Tree * root)
{
    if (root == NULL)
    {
        return;
    }

    printDimHelper(fptr, root -> left);
    printDimHelper(fptr, root -> right);

    if (root -> nodeLabel == 'L')
    {
        fprintf(fptr, "%d(%d,%d)\n", root -> label, root -> width, root -> height);
        return;
    }
    if (root -> nodeLabel == 'B')
    {
        fprintf(fptr, "%c(%d,%d)\n", root -> label, root -> width, root -> height);
        return;
    }
}

void Pack(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, "w");

    int xorigin = 0;
    int yorigin = 0;

    PackHelper(fptr, root, xorigin, yorigin);

    fclose(fptr);
}

void PackHelper(FILE * fptr, Tree * root, int xorigin, int yorigin)
{
    if (root == NULL)
    {
        return;
    }

    if (root -> nodeLabel == 'B')
    {
        if (root -> label == 'H')
        {
            PackHelper(fptr, root -> left, xorigin, yorigin + root -> height - root -> left -> height);
            PackHelper(fptr, root -> right, xorigin, yorigin);
        }
        if (root -> label == 'V')
        {
            PackHelper(fptr, root -> left, xorigin, yorigin);
            PackHelper(fptr, root -> right, xorigin + root -> width - root -> right -> width, yorigin);
        }
    }
    else
    {
        fprintf(fptr, "%d((%d,%d)(%d,%d))\n", root -> label, root -> width, root -> height, xorigin, yorigin);
    }
    
}

void destroyTree(Tree * root)
{
    if (root -> left == NULL && root -> right == NULL)
    {
        free(root);
        return;
    }
    destroyTree(root -> left);
    destroyTree(root -> right);
    free(root);
}

void print2DUtil(Tree *root, int space) 
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
    fprintf(stderr, "%d, %d:\n", root->label, root -> width); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 
