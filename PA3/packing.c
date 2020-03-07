#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "packing.h"

Tree * buildTreeFromPostOrder(char * filename)
{
    FILE * fptr = fopen(filename, 'r');

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

Tree ** LLtoArray(List * head, int * size)
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
}


Tree * constructTreeUtil(Tree ** treeArray, int * postIndex, int key, int min, int max, int size) 
{ 
    // Base case 
    if (*postIndex < 0) 
        return NULL; 
  
    Tree * root = NULL; 
  
    // If current element of post[] is in range, then 
    // only it is part of current subtree 
    if (key > min && key < max) 
    { 
        // Allocate memory for root of this subtree and decrement 
        // *postIndex 
        root = treeArray[(*postIndex)]; 
        *postIndex = *postIndex - 1; 
  
        if (*postIndex >= 0) 
        { 
  
          // All nodes which are in range {key..max} will go in right 
          // subtree, and first such node will be root of right subtree. 
          root -> right = constructTreeUtil(treeArray, postIndex, treeArray[*postIndex], key, max, size); 
  
          // Construct the subtree under root 
          // All nodes which are in range {min .. key} will go in left 
          // subtree, and first such node will be root of left subtree. 
          root -> left = constructTreeUtil(treeArray, postIndex, treeArray[*postIndex], min, key, size ); 
        } 
    } 
    return root; 
} 
  
// The main function to construct BST from given postorder 
// traversal. This function mainly uses constructTreeUtil() 
Tree * constructTree (Tree ** treeArray, int size) 
{ 
    int postIndex = size - 1; 
    return constructTreeUtil(treeArray, &postIndex, treeArray[postIndex], INT_MIN, INT_MAX, size); 
} 