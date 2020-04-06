#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "shell_list.h"

typedef struct List // created a list structure to more efficiently add nodes to the list
{
    Node * head;
    Node * tail;
} List;

List * addNode(List * headnode, long val)
{
    Node * newnode = malloc(sizeof(Node));

    newnode -> value = val;
    newnode -> next = NULL;

    if (headnode -> head == NULL) // Adds node if list structure has no nodes
    {
        headnode -> head = newnode;
        headnode -> tail = newnode;
        headnode -> head -> next = NULL;
        
        return(headnode);
    }

    else // Adds node if list structure already has node
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
    }

    List * nodelist = malloc(sizeof(List));
    nodelist -> head = NULL;
    nodelist -> tail = NULL;
    long holder = 0;

    while(fread(&holder, sizeof(long), 1, fptr)) // Reads into node
    {
        nodelist = addNode(nodelist, holder); // Adds node for each value
    }

    fclose(fptr);

    Node * listhold = malloc(sizeof(Node));
    listhold = nodelist -> head; // Creates temporary holder to return list and for freeineg memory
    free(nodelist);

    return(listhold);
}

Node * List_Shellsort(Node * nodelist, long * n_comp)
{
    long sequence = 0;
    long size = 1;
    Node * nodecount = nodelist;
    long k = 0;
    long j = 0;
    Node * temp = nodelist;
    long i = 0;
    long l = 0;
    long m = 0;
    Node * arraymintemp = nodelist;
    int holder;

    while (nodecount -> next != NULL) // Finds size of linked list
    {
        nodecount = nodecount -> next;
        size++;
    }

    fprintf(stderr, "size: %ld\n", size);

    do // Generates sequence
    {
        sequence = 3 * sequence + 1;
    }while(sequence < size);

    fprintf(stderr, "sequence success\n");

    sequence = (sequence - 1) / 3;
    /* Shellsort algorithm using while loops to make up for array indexing. 
    Any array indexing is used with a while loop to progress the linked list. */
    while(k > 0) 
    {
        for(j = k; j < size; j++)
        {
            if (i < size)
            {
                while (i != j)
                {
                    temp = temp -> next;
                    i++;
                }

                //fprintf(stderr, "i: %d k= %d i-k= %d\n", i, k, i - k);

                while (l != (i - k))
                {
                    arraymintemp = arraymintemp -> next;
                    l++;
                    if (arraymintemp -> next == NULL)
                    {
                    fprintf(stderr, "amt is NULL1\n");
                    break;
                    }
                }

                l = 0;

                fprintf(stderr, "i: %d, k: %d, amt -> value: %d, temp -> value: %d\n", i, k, arraymintemp -> value, temp -> value);

                while ((i >= k) && (arraymintemp -> value > temp -> value))
                {
                    holder = temp -> value; // Swap values
                    temp -> value = arraymintemp -> value;
                    arraymintemp -> value = holder;

                    temp = nodelist;
                    arraymintemp = nodelist;

                    //fprintf(stderr, "assignment success\n");
                    fprintf(stderr, "m: %d i-k: %d\n", m, i-k);
                    while (m != (i - k))
                    {
                        temp = temp -> next;
                        if (arraymintemp -> next == NULL)
                        {
                            fprintf(stderr, "amt is NULL2\n");
                        }
                        arraymintemp = arraymintemp -> next;
                        m++;
                    }
                    m = 0;
                    (*n_comp)++;
                    i = i - k;
                }
                if (arraymintemp -> value <= temp -> value)
                {
                    arraymintemp = nodelist;
                }
                (*n_comp)++;
                temp = nodelist;

                while (m != i)
                {
                    temp = temp -> next;
                    m++;
                    //fprintf(stderr, "m increment: %d\n", m);
                }
                m = 0;
                //fprintf(stderr, "sort success\n");
            }
        }
        k = (k - 1) / 3;

    }
    return (nodelist);
}

int List_Save_To_File(char * filename, Node * nodelist)
{
    FILE * fptr = fopen(filename, "wb");
    int write_num = 0;
    Node * tempnode = nodelist;

    if (fptr == NULL) // Checks if fopen fails
    {
       return(EXIT_FAILURE);
    }

    while(tempnode != NULL && fwrite(&(tempnode -> value), sizeof(long), 1, fptr))
    {
        tempnode = tempnode -> next; // writes to file, advances node
        write_num++;
    }

    fclose(fptr);

    return(write_num);

}
