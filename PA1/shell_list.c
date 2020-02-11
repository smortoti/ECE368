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
    }

    List * nodelist = malloc(sizeof(List));
    long holder = 0;

    while(fread((void *)holder, sizeof(long), 1, fptr))
    {
        nodelist = addNode(nodelist, holder);
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
    int size = 0;
    long counter = 1;
    Node * nodecount = nodelist;
    long k = 0;
    long j = 0;
    Node * temp = nodelist;
    long i = 0;
    long l = 0;
    long m = 0;
    Node * arraytemp1 = NULL;
    Node * arraytemp2 = NULL;
    Node * arraymintemp = NULL;
    Node * arraytemp = NULL;
    Node * tempholder = NULL;
    long o = 0;
    Node * tempholder2 = NULL;

    while (nodecount -> next != NULL)
    {
        nodecount -> next = nodecount;
        counter++;
    }

    do
    {
        sequence = 3 * sequence + 1;
    }while(sequence < counter);

    sequence = (sequence - 1) / 3;

    for(k = sequence; k > 0; k = (k - 1) / 3)
    {
        while(j < counter)
        {
            j++;
            while(i != j)
            {
                arraytemp = arraytemp -> next;
                i++;
            }
            l = j;

            while(m != (l - k))
            {
                arraymintemp = arraymintemp -> next;
                m++;
            }
            m = 0;

            while (l >= k && ((arraymintemp -> value) > (arraytemp -> value)))
            {
                while(o < l)
                {
                    arraytemp1 = arraytemp1 -> next;
                    o++;
                }
                o = 0;
                while (o < l - k)
                {
                    arraytemp2 = arraytemp2 -> next;
                    o++;
                }
                o = 0;

                tempholder = arraytemp1;
                tempholder2 = nodelist;

                while(tempholder2 -> next != arraytemp1)
                {
                    tempholder2 = tempholder2 -> next;
                }

                Node * tempholder3 = nodelist;

                while (tempholder3 -> next != arraytemp2)
                {
                    tempholder3 = tempholder3 -> next;
                }

                arraytemp1 -> next = arraytemp2 -> next;
                arraytemp2 -> next = tempholder -> next;
                tempholder2 -> next = arraytemp2;
                tempholder3 -> next = arraytemp1;

                l = l - k;
                (*n_comp)++;

            }
            (*n_comp)++;

        }

    }
    return (nodelist);
}

int List_Save_To_File(char * filename, Node * nodelist)
{
    FILE * fptr = fopen(filename, "wb");
    int write_num = 0;
    Node * tempnode = NULL;

    if (fptr == NULL) // Checks if fopen fails
    {
       return(EXIT_FAILURE);
    }

    while(fwrite((void *)tempnode -> value, sizeof(long), 1, fptr))
    {
        tempnode = tempnode -> next;
        write_num++;
    }

    fclose(fptr);

    return(write_num);

}