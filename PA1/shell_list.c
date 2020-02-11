#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "shell_list.h"

typedef struct List
{
    Node * head;
    Node * tail;
} List;

List * addNode(List * headnode, long val)
{
    Node * newnode = malloc(sizeof(Node));
    Node * temp = NULL;

    newnode -> value = val;
    newnode -> next = NULL;

    if (headnode -> head == NULL)
    {
        headnode -> head = newnode;
        headnode -> tail = newnode;
        headnode -> head -> next = NULL;
        
        return(headnode);
    }

    else
    {
        headnode -> tail -> next = newnode;
        headnode -> tail = headnode -> tail -> next;

        return(headnode);
    }
    
}

Node * List_Load_From_File(char * filename)
{
    FILE * fptr = fopen(filename, "r");
    
    if (fptr == NULL)
    {
        fprintf(stderr, "%s", "fopen fail\n");
        return(EXIT_FAILURE);
    }

    List * nodelist = malloc(sizeof(List));
    long holder = 0;

    while(fread(holder, sizeof(long), 1, fptr))
    {
        nodelist = addNode(nodelist, holder);
    }

    fclose(fptr);

    return(nodelist -> head);
}