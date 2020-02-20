#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "h_comp.h"

#define ASCIIMAX 256

List * Read_From_File(char * filename)
{
    FILE * fptr = fopen(filename, "r");
    
    if (fptr == NULL)
    {
        return(NULL);
    }

    List * chr_list = NULL;
    char chr = 'a';

    while ((chr != EOF)) // creates a new node for 
    {
        chr = fgetc(fptr);
        if (!feof(fptr))
        {
            chr_list = Add_Node(chr_list, chr);
        }
    }

    fclose(fptr);

    return(chr_list);

}

List * Add_Node(List * head, char chr)
{
    List * newNode = malloc(sizeof(*newNode));

    if (head == NULL) // checks if list has a head node
    {
        head = newNode;
        head -> next = NULL;
        head -> chr = chr;
        head -> freq = 1;

        return(head);
    }

    List * tmpNode = head;
    List * secondTemp = NULL;

    while(tmpNode != NULL) // checks if the character has already been read
    {
        if (chr == tmpNode -> chr)
        {
            (tmpNode -> freq)++;
            free(newNode); // New node wasn't used, freed to preserve memory

            return(head);
        }
        if (tmpNode -> next == NULL)
        {
            secondTemp = tmpNode;
        }
        tmpNode = tmpNode -> next;
        
    }

    secondTemp -> next = newNode;
    newNode -> next = NULL;
    newNode -> chr = chr;
    newNode -> freq = 1;

    return(head);

}

void Read_Freq(char * filename, List * head)
{
    FILE * fptr = fopen(filename, "wb");
    
    if (fptr == NULL) // checks if open succeeds
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    List * tmpNode = head;
    int i = 0;
    long zero = 0;
    int write = 0;

    while(i < ASCIIMAX)
    {
        if ((tmpNode -> chr) == i)
        {
            write = fwrite(&(tmpNode -> freq), sizeof(long), 1, fptr);
            i++;
        }
        else if (tmpNode -> next == NULL)
        {
            write = fwrite(&zero, sizeof(long), 1, fptr);
            i++;
        }
        if (write == 1)
        {
            tmpNode = head;
            write = 0;
        }
        else
        {
            tmpNode = tmpNode -> next;
        }

    }

    fclose(fptr);

}

void sort_List(List * head)
{
    int swapped;
    List * ptr1; 
    List * lptr = NULL; 
  
    /* Checking for empty list */
    if (head == NULL) 
        return; 
  
    do // Linked list bubble sort
    { 
        swapped = 0; 
        ptr1 = head; 
  
        while (ptr1 -> next != lptr) 
        { 
            if (ptr1 -> freq > ptr1 -> next -> freq) 
            {  
                swap(ptr1, ptr1 -> next); 
                swapped = 1; 
            } 
            ptr1 = ptr1 -> next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
}

void swap(List * node1, List * node2) 
{ 
    List * temp = node1; 
    node1 -> freq = node2 -> freq; 
    node1 -> chr = node2 -> chr;
    node2 -> freq = temp -> freq; 
    node2 -> chr = temp -> chr;
} 

long countNode(List * head)
{
    long count = 0;

    List * tempNode = head;

    while(tempNode != NULL)
    {
        tempNode = tempNode -> next;
        count++;
    }

    return(count);
}

Tree * Add_TreeNode(char chr, long freq)
{
    Tree * root = malloc(sizeof(Tree));

    root -> freq = freq;
    root -> chr = chr;
    root -> bin_code = NULL;
    root -> left = root -> right = NULL;

    return root; 
}

Tree * Merge_Tree(Tree * node1, Tree * node2)
{
    Tree * root = malloc(sizeof(*root));

    root -> left = node1;
    root -> right = node2;
    root -> chr = '\0';
    root -> freq = node1 -> freq + node2 -> freq;

    return root;
}

TreeList * createTLNode(Tree * root)
{
    TreeList * head = malloc(sizeof(*head));

    head -> next = NULL;
    head -> treeptr = root;

    return head;
}

TreeList * TL_Insert(TreeList * head, TreeList * node)
{
    if (head == NULL)
    {
        fprintf(stderr, "head is NULL\n");
        return node;
    }

    fprintf(stderr, "entering assign\n");

    long freq1 = (head -> treeptr -> freq);
    long freq2 = (node -> treeptr -> freq);

    fprintf(stderr, "assignment success\n");

    if (freq1 > freq2)
    {
        node -> next = head;
        return node;
    }

    head -> next = TL_Insert(head -> next, node);

    return head;
}

TreeList * TL_Build(Tree ** treeArray, long size)
{
    long i = 0;
    TreeList * head = NULL;
    fprintf(stderr, "%ld\n", size);
    
    for (i = 0; i < size; i++)
    {
        fprintf(stderr, "enter array\n");
        TreeList * node1 = createTLNode(treeArray[i]);
        fprintf(stderr, "addnode success\n");
        if (node1 == NULL)
        {
            fprintf(stderr, "node1 is null\n");
        }
        head = TL_Insert(head, node1);
        //fprintf(stderr, "insert success\n");

    }
    fprintf(stderr, "for loop completion\n");

    return head;
}
List * Free_Node(List * head, List * nodeToDelete)
{
    List * temp = head;

    if (head == nodeToDelete)
    {   
        free(head);

        return (temp -> next);
    }
    
    while (temp -> next != nodeToDelete)
    {
        temp = temp -> next;
    }

    List * ln = temp -> next;

    free(temp -> next);

    temp -> next = ln -> next;

    return(head);

}

Tree * Build_Tree(List * head)
{
    long size = countNode(head);

    Tree ** treeArray = malloc(sizeof(Tree *) * size);
    List * tempNode = head;
    long i = 0;

    while(tempNode != NULL) // Fills treeArray with tree nodes
    {
        treeArray[i] = Add_TreeNode(head -> chr, head -> freq);
        tempNode = tempNode -> next;
    }

    fprintf(stderr, "forest success\n");

    TreeList * headTree = TL_Build(treeArray, size);

    fprintf(stderr, "build success\n");

    if (headTree == NULL)
    {
        fprintf(stderr, "headTree alloc fail\n");
    }

    while (headTree -> next != NULL)
    {
        TreeList * second = headTree -> next;
        TreeList * third = second -> next;
        Tree * tn1 = headTree -> treeptr;
        Tree * tn2 = second -> treeptr;

        free(headTree);
        free(second);

        headTree = third;
        fprintf(stderr, "headtree reassign success\n");
        Tree * mrg = Merge_Tree(tn1, tn2); // branch nodes are created with '\0' as chr value
        fprintf(stderr, "merge success\n");
        TreeList * ln = createTLNode(mrg);
        fprintf(stderr, "newnode success\n");

        headTree = TL_Insert(headTree, ln);
        fprintf(stderr, "insert success\n");
    }

    return (headTree -> treeptr);
}

void printTreeNode(Tree * node)
{
    if (node -> chr == '\0')
    {
        fprintf(stdout, "0");
    }
    else
    {
        fprintf(stdout, "1%c", node -> chr);
    }
}

void PreOrder_Traverse(Tree * node)
{
    if (node == NULL)
    {
        return;
    }

    printTreeNode(node);
    PreOrder_Traverse(node -> left);
    PreOrder_Traverse(node -> right);

}

void PreOrder_Traverse_Write(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    PreOrder_Traverse(root);
    
    fclose(fptr);
}

void PreOrder_Traverse_Code(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        fprintf(stderr, "fopen fail\n");
    }

    long leftIndex = 0;
    long rightIndex = 0;

    printCodes(root, &leftIndex, &rightIndex);
 
}

void printCodes(Tree * node, long * ind_left, long * ind_right)
{
    if (node -> chr != '\0')
    {
        fprintf(stdout, "%c:", node -> chr);
    }

    if ((node -> left == NULL) && (node -> right == NULL))
    {
        if ((*ind_left) > (*ind_right))
        {
            long i = 0;
            for (i = *ind_left; i > 0; i--)
            {
                fprintf(stdout, "0");
            }
            fprintf(stdout, "\n");
            return;
        }
        else
        {
            long i = 0;
            for (i = *ind_right; i > 0; i--)
            {
                fprintf(stdout, "1");
            }
            fprintf(stdout, "\n");
            return;
        }
    }
    if (((*ind_left > (*ind_right - 1)) && (*ind_right > 0)))
    {
        long i = 0;
        for (i = *ind_left; i > 0; i--)
        {
            fprintf(stdout, "0");
            (*ind_left)--;
        }
    }
    else if ((*ind_right > (*ind_left - 1)) && ((*ind_left > 0)))
    {
        long i = 0;
        for (i = *ind_right; i > 0; i--)
        {
            fprintf(stdout, "1");
            (*ind_right)--;
        }
    }

    printCodes(node -> left, ind_left++, ind_right);
    printCodes(node -> right, ind_left, ind_right++);
}
