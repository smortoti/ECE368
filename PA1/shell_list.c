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
	Node * listholder = NULL;
    nodelist -> head = NULL;
    nodelist -> tail = NULL;
    long holder = 0;

    while(fread(&holder, sizeof(long), 1, fptr)) // Reads into node
    {
        nodelist = addNode(nodelist, holder); // Adds node for each value
    }

    fclose(fptr);

    listholder = nodelist -> head; // Creates temporary holder to return list and for freeineg memory
    free(nodelist);

    return(listholder);
}

void swap(Node ** headRef, Node * prevSwap1, Node * swap1, Node * swap2, Node * prevSwap2)
{
    Node * temp = NULL;

    if (prevSwap1 != NULL)
    {
        prevSwap1 -> next = swap2;
    }
    else
    {
        *headRef = swap2;
    }

    prevSwap2 -> next = swap1;
    temp = swap2 -> next;
    swap2 -> next = swap1 -> next;
    swap1 -> next = temp;
}

Node * List_Shellsort(Node * head, long * n_comp)
{
    long sequence = 0;
    long size = 1;
    long a = 0;
    long b = 0;
    long c = 0;
    long d = 0;
    long k = 0;
    long j = 0;
    long i = 0;

    Node * nodecount = head;
    Node * temp = head;
    Node * tempIminK = head;
    Node * prevTemp2 = NULL;
    Node * temp2 = head;
    Node * prevTempIminK = NULL;
	Node * prevTemp;

    temp = head;

    while (nodecount -> next != NULL) // Finds size of linked list
    {
        nodecount = nodecount -> next;
        size++;
    }

    do // Generates sequence
    {
        sequence = 3 * sequence + 1;
    }while(sequence < size);

    sequence = (sequence - 1) / 3;

    for(k = sequence; k > 0; k = (k - 1) / 3) // Shellsort algorithm
    {
        for(j = k; j < size; j++)
        {
            temp = head;
            prevTemp = NULL;

            while (a < j)
            {
                prevTemp = temp;
                temp = temp -> next;
                a++;
            }
            a = 0;

            i = j;
            tempIminK = head;
            prevTempIminK = NULL;

	    	while (b < (i - k))
            {
                prevTempIminK = tempIminK;
                tempIminK = tempIminK -> next;              
                b++;
            }
            b = 0;

            while ((i >= k) && (tempIminK -> value > temp -> value))
            {
                temp2 = head;
                prevTemp2 = NULL;

                while (c < i)
                {
                    prevTemp2 = temp2;
                    temp2 = temp2 -> next;
                    c++;
                }
                c = 0;

                swap(&head, prevTempIminK, tempIminK, temp2, prevTemp2);
                i = i - k;

                prevTempIminK = NULL;
                tempIminK = head;
                while (b < (i - k))
                {
                    prevTempIminK = tempIminK;
                    tempIminK = tempIminK -> next;              
                    b++;
                }
                b = 0;

                (*n_comp)++;
            }
            (*n_comp)++;

            prevTemp2 = NULL;
            temp2 = head;
            while (d < i)
            {
                prevTemp2 = temp2;
                temp2 = temp2 -> next;
                d++;
            }
            d = 0;
        }
    }

    return (head);
}

void freeLL(Node * head)
{
	while(head != NULL)
	{
		Node * temp = head -> next;
		free (head);
		head = temp;
	}
}

int List_Save_To_File(char * filename, Node * head)
{
    FILE * fptr = fopen(filename, "wb");
    int write_num = 0;
    Node * tempnode = head;

    if (fptr == NULL) // Checks if fopen fails
    {
       return(EXIT_FAILURE);
    }

    while(tempnode != NULL)
    {
        fwrite(&(tempnode -> value), sizeof(long), 1, fptr);
        tempnode = tempnode -> next; // writes to file, advances node
        write_num++;
    }
    freeLL(head);

    fclose(fptr);

    return(write_num);

}
