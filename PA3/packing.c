#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "packing.h"
#define COUNT 10

Tree * buildTreeFromPostOrder(char * filename)
{
    FILE * fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        return NULL;
    }

    int readTemp = 0;
    List * head = NULL;
    int position = 0;
    int i = 0;
    int label = 0;
    int width = 0;
    int height = 0;
    Tree ** treeArray = NULL;
    int size = 0;
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
            head = createNode(head, readTemp, 0, 0);
        }
        else
        {
            if(!(feof(fptr)))
            {
                position = ftell(fptr);
                fseek(fptr, (long) (position - 1), SEEK_SET);
                fscanf(fptr, "%d(%d, %d)\n", &label, &width, &height);
                head = createNode(head, label, width, height);
            }
        }    
    }

    treeArray = LLtoArray(head, &size);
    tree = constructTree(treeArray, size);
    
    fclose(fptr);

    return(tree);
}

List * createNode(List * head, int label, int width, int height)
{
    if (head == NULL)
    {
        List * temp = malloc(sizeof(*temp));

        temp -> label = label;
        temp -> height = height;
        temp -> width = width;
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

/*Tree ** LLtoArray(List * head, int * size)
{
    List * temp = head;

    while(temp -> next != NULL)
    {
        temp = temp -> next;
        (*size)++;
    }

    Tree ** treeArray = malloc(sizeof(*treeArray) * (*size));

    int i = 0;
    temp = head;

    for(i = 0; i < (*size - 1); i++)
    {
        treeArray[i] -> label = temp -> label;
        treeArray[i] -> height = temp -> height;
        treeArray[i] -> width = temp -> width;
        treeArray[i] -> left = treeArray[i] -> right = NULL;
        temp = temp -> next;
    }

    freeLL(head);

    return(treeArray);
}*/

Tree * constructTree(List * head, Tree * root)
{
    List * temp = head;

    if (root == NULL)
    {
        while(temp -> next != NULL)
        {
            temp = temp -> next;
        }

        root = createTreeNode(root, temp -> label, temp -> width, temp -> height);
        freeNode(temp);
        return root;

    }

    if ((temp -> previous -> label != ('V' || 'H')) && (temp -> previous -> previous -> label != ('V' || 'H')))
    {
        return root;
    }

    if (temp -> previous -> label == ('V' || 'H'))
    {
        root -> right = 
    }
}

void printPreOrder(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, 'w');

    printTreeNode(fptr, root);

    fclose(fptr);

}

void printTreeNode(FILE * fptr, Tree * root)
{
    if(root == NULL)
    {
        return;
    }
    if(root -> label == 'V' || root -> label == 'H')
    {
        fprintf(fptr, "%c\n", root -> label);
    }
    else
    {
        fprintf(fptr, "%d(%d, %d)\n");
    }

    printTreeNode(fptr, root -> left);
    printTreeNode(fptr, root -> right);
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
    fprintf(stderr, "%ld, %c:\n", root->freq, root -> chr); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 