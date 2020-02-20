#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "h_comp.h"

List * Read_From_File(char * filename)
{
    FILE * fptr = fopen(filename, "rb");
    
    if (fptr == NULL)
    {
        return(NULL);
    }

    List * chr_list = malloc(sizeof(*chr_list));
    char chr;

    while ((chr = fgetc(fptr) != EOF)) // creates a new node for 
    {
        chr_list = Add_Node(chr_list, chr);
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

    while(tmpNode -> next != NULL) // checks if the character has already been read
    {
        if (chr == tmpNode -> chr)
        {
            (tmpNode -> freq)++;
            free(newNode); // New node wasn't used, freed to preserve memory

            return(head);
        }
        tmpNode = tmpNode -> next;
    }

    tmpNode -> next = newNode;
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
    
    do // writes into file, use do while to ensure last node of linked list is written
    {
        fwrite(&(tmpNode -> freq), sizeof(long), 1, fptr);
        tmpNode = tmpNode -> next;
    }while(tmpNode -> next != NULL);

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
    List * tempNode = NULL;

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
    TreeList * head = malloc(sizeof(TreeList));

    head -> next = NULL;
    head -> treeptr = root;

    return head;
}

TreeList * TL_Insert(TreeList * head, TreeList * node)
{
    if (head == NULL)
    {
        return node;
    }

    Tree * tn1 = head -> treeptr;
    Tree * tn2 = node -> treeptr;

    long freq1 = tn1 -> freq;
    long freq2 = tn2 -> freq;

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
    
    for (i = 0; i < size; i++)
    {
        TreeList * node1 = createTLNode(treeArray[i]);
        head = TL_Insert(head, node1);
    }

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

    TreeList * headTree = TL_Build(treeArray, size);

    while (headTree -> next != NULL)
    {
        TreeList * second = headTree -> next;
        TreeList * third = second -> next;
        Tree * tn1 = headTree -> treeptr;
        Tree * tn2 = second -> treeptr;

        free(headTree);
        free(second);

        headTree = third;
        Tree * mrg = Merge_Tree(tn1, tn2); // branch nodes are created with '\0' as chr value
        TreeList * ln = createTLNode(mrg);

        headTree = TL_Insert(head, ln);
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

    long * leftIndex = sizeof(long);
    long * rightIndex = sizeof(long);

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
                fprintf(stdout, "1");
            }
            fprintf(stdout, "\n");
            return;
        }
        else
        {
            long i = 0;
            for (i = *ind_right; i > 0; i--)
            {
                fprintf(stdout, "0");
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
            fprintf(stdout, "1");
            (*ind_left)--;
        }
    }
    else if ((*ind_right > (*ind_left - 1)) && ((*ind_left > 0)))
    {
        long i = 0;
        for (i = *ind_right; i > 0; i--)
        {
            fprintf(stdout, "0");
            (*ind_right)--;
        }
    }

    printCodes(node -> left, ind_left++, ind_right);
    printCodes(node -> right, ind_left, ind_right++);
}