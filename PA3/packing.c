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

    /* Read will have form of 
        %d ( %d , %d ) \n
    or
        &d \n
    */ 
    while(!(feof(fptr)))
    {
        readTemp = fgetc(fptr);
        if (readTemp == 'H' || readTemp == 'V')
        {
            if(!(feof(fptr)))
            {
                head = createNode(head, readTemp, 0, 0);
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

    fprintf(stderr, "enter array\n");

    treeArray = LLtoArray(head, &size);

    fprintf(stderr, "array success\n");

    (*upper_bound) = size - 1;

    fprintf(stderr, "assign success: %d\n", (*upper_bound));

    tree = constructTree(treeArray, upper_bound);
    
    fclose(fptr);

    return(tree);
}

Tree ** LLtoArray(List * head, int * size)
{
    List * temp = head;
    
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
        fprintf(stderr, "label: %d\n", treeArray[i] -> label);
    }
    freeLL(head);
    return(treeArray);
}

List * createNode(List * head, int label, int width, int height)
{
    fprintf(stderr, "height: %d, width: %d\n", height, width);
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
        fprintf(stderr, "enter branch\n");
    }
    else
    {
        newNode -> nodeLabel = 'L';
        fprintf(stderr, "enter leaf\n");
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

void freeNode(List * toDelete)
{
    List * temp = toDelete -> previous;
    List * temp2 = toDelete -> next;
    free(toDelete);
    temp -> next = temp2;
    temp2 -> previous = temp;
}

Tree * constructTree(Tree ** treeArray, int * upper_bound)
{
    Tree * root = treeArray[(*upper_bound)];

    if (root == NULL)
    {
        fprintf(stderr, "NULL\n");
    }

    fprintf(stderr, "nodeLabel: %c\n", treeArray[(*upper_bound)] -> nodeLabel);

    if ((root -> nodeLabel) == 'B')
    {
        if (treeArray[(*upper_bound - 1)] -> nodeLabel == 'B')
        {
            (*upper_bound)--;
            fprintf(stderr, "ub: %d\n", (*upper_bound));
            root -> right = constructTree(treeArray, upper_bound);
        }
        else
        {
            (*upper_bound)--;
           // fprintf(stderr, "ub: %d\n", (*upper_bound));
            root -> right = treeArray[(*upper_bound)];
        }

        if (treeArray[(*upper_bound - 1)] -> nodeLabel == 'B')
        {
            (*upper_bound)--;
           // fprintf(stderr, "ub: %d\n", (*upper_bound));
            root -> left = constructTree(treeArray, upper_bound);
        }
        else
        {
            (*upper_bound)--;
            //fprintf(stderr, "ub: %d\n", (*upper_bound));
            root -> left = treeArray[(*upper_bound)];
        }  
    }
    if (root -> nodeLabel == 'H')
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
    else if(root -> nodeLabel == 'V')
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

    PackHelper(fptr, root);

    fclose(fptr);
}

void PackHelper(FILE * fptr, Tree * root)
{
    
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
