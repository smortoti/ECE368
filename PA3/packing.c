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

    List * head = NULL;
    Tree ** treeArray = NULL;
    Tree * tree = NULL;

    int readTemp = 0;
    int position = 0;
    int label = 0;
    int width = 0;
    int height = 0;
    int size = 0;

    while(!(feof(fptr)))
    {
        readTemp = fgetc(fptr); // reads initial character from input file
        if (readTemp == 'H' || readTemp == 'V') // if charater is a branch node, create LL Node for branch
        {
            if(!(feof(fptr)))
            {
                head = createNode(head, readTemp, 0, 0);
                size++;
                readTemp = fgetc(fptr); // read the newline char after branch label and advance the file stream
            }
        }
        else
        {
            if(!(feof(fptr)))
            {
                position = ftell(fptr); // finds position of file
                fseek(fptr, (long) (position - 1), SEEK_SET); // returns file stream back to the read from fgetc
                fscanf(fptr, "%d(%d,%d)\n", &label, &width, &height); // reads the full formatted line from the file
                if(readTemp != '\n') // ensures no nodes are added with newline character
                {
                    head = createNode(head, label, width, height);
                    size++;
                }

            }
        }    
    }

    treeArray = LLtoArray(head, size); // creates an array of tree nodes from the read-in LL

    if (treeArray == NULL) // checks if treeArray is NULL, i.e. from an empty file
    {
        fclose(fptr);
        return NULL;
    }

    (*upper_bound) = size - 1; // assigns upper bound to last element of the array

    tree = constructTree(treeArray, upper_bound); // constructs tree from postorder read in

    free(treeArray); // frees array pointer used for tree nodes
    
    fclose(fptr);

    return(tree);
}

Tree ** LLtoArray(List * head, int size)
{
    List * temp = head;

    if (head == NULL)
    {
        return NULL;
    }
    
    /*while(temp -> next != NULL) // finds total nodes read-in
    {
        temp = temp -> next;
        (*size)++; // use address to return out of function
    }*/

    Tree ** treeArray = malloc(sizeof(*treeArray) * (size));

    if (treeArray == NULL)
    {
        fprintf(stderr, "treeArray is NULL\n");
    }
    int i = 0;
    temp = head;

    for(i = 0; i < size; i++) // make copies of treeArray nodes from LL into an array
    {
        treeArray[i] = malloc(sizeof(*treeArray[i]));
        treeArray[i] -> label = temp -> label;
        treeArray[i] -> height = temp -> height;
        treeArray[i] -> width = temp -> width;
        treeArray[i] -> nodeLabel = temp -> nodeLabel;
        treeArray[i] -> left = treeArray[i] -> right = NULL;
        temp = temp -> next;
    }
    freeLL(head); // free LL
    return(treeArray);
}

List * createNode(List * head, int label, int width, int height)
{
    if (head == NULL) // creates new head node
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

    while (temp -> next != NULL) // creates new node if head isn't NULL
    {
        temp = temp -> next;
    }

    newNode -> label = label;
    newNode -> height = height;
    newNode -> width = width;

    if (height == 0 && width == 0) // checks if new node is a branch or leaf node (branch has no initial height or width)
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

void freeLL(List * head) // frees LL by freeing head and making head = head -> next
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

Tree * constructTree(Tree ** treeArray, int * upper_bound) // uses treeArray (i.e. forest) to construct the tree
{
    Tree * root = treeArray[(*upper_bound)];

    if (root == NULL)
    {
        fprintf(stderr, "NULL\n");
    }

    if ((root -> nodeLabel) == 'B')
    {
        if (treeArray[(*upper_bound - 1)] -> nodeLabel == 'B') // if node to the left of last node in the array is a branch node, add to the right of tree and recur
        {
            (*upper_bound)--;
            root -> right = constructTree(treeArray, upper_bound);
        }
        else // if it is a leaf node, add to right and continue
        {
            (*upper_bound)--;
            root -> right = treeArray[(*upper_bound)];
        }

        if (treeArray[(*upper_bound - 1)] -> nodeLabel == 'B') // if node two spaces to the left in the array is a branch node, add to the left of parent and recur
        {
            (*upper_bound)--;
            root -> left = constructTree(treeArray, upper_bound);
        }
        else // if node is a leaf node, add and continue
        {
            (*upper_bound)--;
            root -> left = treeArray[(*upper_bound)];
        }  

        // if both nodes are leaf nodes, no more recursion occurs and thus the function returns
    }
    if (root -> nodeLabel == 'B') // calculates dimensions (rooms) of branch nodes
    {
        if (root -> label == 'H') // checks if branch node is a horizontal cut
        {
            root -> height = root -> left -> height + root -> right -> height; // with an H branch, height is the addition of both child nodes
            if (root -> left -> width > root -> right -> width) // with an H branch, width is the larger of the two widths of the child nodes
            {
                root -> width = root -> left -> width;
            }
            else
            {
                root -> width = root -> right -> width;
            }   
        }
        else if(root -> label == 'V') // checks if branch is a vertical cut
        {
            root -> width = root -> left -> width + root -> right -> width; // vice versa for V nodes
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
    return (root); // return completed tree
}

void printPreOrder(char * filename, Tree * root) // opens file and calls recursive helper function
{
    FILE * fptr = fopen(filename, "w");

    printTreeNode(fptr, root);

    fclose(fptr);

}

void printTreeNode(FILE * fptr, Tree * root) // prints preorder traversal of nodes
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

void printDimensions(char * filename, Tree * root) // opens file and calls recursive helper function
{
    FILE * fptr = fopen(filename, "w");

    printDimHelper(fptr, root);

    fclose(fptr);
}

void printDimHelper(FILE * fptr, Tree * root) // prints dimensions recursively
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

void Pack(char * filename, Tree * root) // opens file and calls recursibe helper function
{
    FILE * fptr = fopen(filename, "w");

    int xorigin = 0;
    int yorigin = 0;

    PackHelper(fptr, root, xorigin, yorigin);

    fclose(fptr);
}

void PackHelper(FILE * fptr, Tree * root, int xorigin, int yorigin)
{
    if (root == NULL) // base case
    {
        return;
    }

    if (root -> nodeLabel == 'B') // must cycle through the whole tree, uses recursion
    {
        if (root -> label == 'H')
        {
            PackHelper(fptr, root -> left, xorigin, yorigin + root -> height - root -> left -> height); // for an H branch, the height changes by the total room size minus the block size on the left
            PackHelper(fptr, root -> right, xorigin, yorigin); // right does not affect origin for H branches
        }
        if (root -> label == 'V') // vice versa for V case
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

void destroyTree(Tree * root) // frees tree
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

void print2DUtil(Tree *root, int space) // debugging tree print function
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
