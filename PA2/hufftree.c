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
        if (chr = tmpNode -> chr)
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
        fwrite(tmpNode -> freq, sizeof(long), 1, fptr);
        tmpNode = tmpNode -> next;
    }while(tmpNode -> next != NULL);

    fclose(fptr);

}

List * sort_List(List * head)
{
    int swapped;
    int i; 
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

/*long countNode(List * head)
{
    long count = 0;
    List * tempNode = NULL;

    while(tempNode != NULL)
    {
        tempNode = tempNode -> next;
        count++;
    }

    return(count);
}*/

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

/*Tree * createBranch(Tree * node1, Tree * node2)
{
    Tree * root = malloc(sizeof(*root));

    root -> freq = node1 -> freq + node2 -> freq;
    root -> bin_code = NULL;
    root -> chr = '\0';
    root -> left = node1;
    root -> right = node2;

    return root;
}*/

Tree * Build_Tree(TreeList * head)
{
    long size = countNode(head);

    Tree ** treeArray = malloc(sizeof(Tree *) * size);
    long i = 0;

    TreeList * head = TL_Build(treeArray, size);

    while (head -> next != NULL)
    {
        TreeList * second = head -> next;
        TreeList * third = second -> next;
        Tree * tn1 = head -> treeptr;
        Tree * tn2 = second -> treeptr;

        free(head);
        free(second);

        head = third;
        Tree * mrg = Merge_Tree(tn1, tn2);
        TreeList * ln = createTLNode(mrg);

        head = TL_Insert(head, ln);
    }

    return (head -> treeptr);
    
    /*while(head != NULL) // creates array of tree nodes
    {
       treeArray[i] = Add_TreeNode(head);

       head = Free_Node(head, head);

       i++;
    }

    i = 0;
    long size_counter = size;
    Tree * tempTree = NULL;

    while(size_counter > 1) // realloc array to shrink as tree builds
    {
        tempTree = createBranch(treeArray[i], treeArray[i + 1]);
        for (int j = i + 1, j < size, j++)
        {
            if ()
        }
        treeArray[i] = realloc(treeArray[i], sizeof(int));
        treeArray[i] = 0;
        i++;
        size_counter--;
    }*/

}

void PreOrder_Traverse(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    

}