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

Tree * Add_TreeNode(List * head, List * head_next)
{
    Tree * left = malloc(sizeof(Tree)); 
    Tree * right = malloc(sizeof(Tree));
    Tree * branch = malloc(sizeof(Tree));

    left -> chr = head -> chr; 
    left -> bin_code = NULL;
    left -> freq = head -> freq;
    left -> left = NULL; 
    left -> right = NULL; 

    right -> chr = head_next -> chr;
    right -> bin_code = NULL;
    right -> freq = head_next -> freq;
    right -> left = NULL;
    right -> right = NULL;

    branch -> chr = '\0';
    branch -> bin_code = NULL;
    branch -> freq = head -> freq + head_next -> freq;
    branch -> left = left;
    branch -> right = right;

    return branch; 
}

List * Insert_Node(List * head, long freq)
{
    List * newNode = malloc(sizeof(*newNode));

    newNode -> freq = freq;
    newNode -> chr = '\0';

    List * tempNode = head;

    while (newNode -> freq > tempNode -> next -> freq)
    {
        tempNode = tempNode -> next;
    }

    List * holder = NULL;

    if (tempNode -> next != NULL)
    {
        List * holder = tempNode -> next;
    }

    tempNode -> next = newNode;
    newNode -> next = holder;

    return head;



}

Tree * Build_Tree(List * head)
{
    long size = countNode(head);

    Tree ** treeArray = malloc(sizeof(Tree *) * size);
    long i = 0;

    while(head -> next != NULL)
    {
       treeArray[i] = Add_TreeNode(head, head -> next);
       i++;

       head = Free_Node(head, head);
       head = Free_Node(head, head);

       head = Insert_Node(head, treeArray[i - 1] -> freq)
    }

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