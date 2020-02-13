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

Tree * Build_Tree(List * head)
{
    Tree * bin_tree = sizeof(*bin_tree);
    List * tmpNode = head;
    long size = head -> freq;

    do
    {
        tmpNode = tmpNode -> next;
        if (tmpNode -> freq < size)
        {
            size = tmpNode -> freq;
        }
    }while(tmpNode -> next != NULL);

    bin_tree = Add_TreeNode(head, size);





}