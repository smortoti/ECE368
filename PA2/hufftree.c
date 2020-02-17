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

Tree * Add_TreeNode(char chr, char * string)
{
    Tree * node = malloc(sizeof(*node)); 

    node->chr = chr; 
    node -> bin_code = string;
    node -> left = NULL; 
    node -> right = NULL; 
  
    return node; 
}

Tree * Build_Tree(List * head)
{
    long size = 0;

    size = countNode(head);

    return listToBstBuild(&head, size);
}
  
/* The main function that constructs balanced BST and returns root of it. 
       head_ref -->  Pointer to pointer to head node of linked list 
       n  --> No. of nodes in Linked List */
Tree * listToBstBuild(List ** head_ref, long n) 
{ 
    /* Base Case */
    if (n <= 0)
    {
        return NULL;
    }  
  
    /* Recursively construct the left subtree */
    Tree * left = listToBstBuild(head_ref, n/2); 
  
    /* Allocate memory for root, and link the above constructed left  
       subtree with root */
    Tree * root = Add_TreeNode((*head_ref)->chr, NULL); 
    root -> left = left; 
  
    /* Change head pointer of Linked List for parent recursive calls */
    *head_ref = (*head_ref) -> next; 
  
    /* Recursively construct the right subtree and link it with root  
      The number of nodes in right subtree  is total nodes - nodes in  
      left subtree - 1 (for root) which is n-n/2-1*/
    root -> right = listToBstBuild(head_ref, n-n/2-1); 
  
    return root; 
} 