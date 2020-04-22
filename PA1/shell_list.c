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

void swap(Node * head, Node * prevSwap1, Node * swap1, Node * swap2, Node * prevSwap2)
{
    if (prevSwap1 == NULL)
    {
        // head is swap1
        head = swap2;
        head -> next = swap1 -> next;
        prevSwap2 -> next = swap1;
        swap1 -> next = swap2 -> next;
    }
    prevSwap1 -> next = swap2;
    prevSwap2 -> next = swap1;
    swap2 -> next = swap1 -> next;
    swap1 -> next = swap2 -> next;
}
Node * List_Shellsort(Node * nodelist, long * n_comp)
{
    long sequence = 0;
    long size = 1;
    long a = 0;
    long iminusk = 0;
    long b = 0;
    long c = 0;
    long d = 0;
    long k = 0;
    long j = 0;
    long i = 0;
    long l = 0;
    long m = 0;
    long holder;

    Node * nodecount = nodelist;
    Node * temp = nodelist;
    Node * arraymintemp = nodelist;
    Node * tempIminK = nodelist;
    Node * prevTemp2 = NULL;
    Node * temp2 = nodelist;
    Node * prevTempIminK = NULL;

    temp = nodelist;

    while (nodecount -> next != NULL) // Finds size of linked list
    {
        nodecount = nodecount -> next;
        size++;
    }

    //fprintf(stderr, "size: %ld\n", size);

    do // Generates sequence
    {
        sequence = 3 * sequence + 1;
    }while(sequence < size);

    sequence = (sequence - 1) / 3;

    for(k = sequence; k > 0; k = (k - 1) / 3) // Shellsort algorithm
    {
        for(j = k; j < size; j++)
        {
            temp = nodelist;
            while (a < j)
            {
                temp = temp -> next;
                a++;
            }
            a = 0;
            i = j;
            iminusk = i - k;
            
            tempIminK = nodelist;
            prevTempIminK = NULL;
            while (b < iminusk)
            {
                tempIminK = tempIminK -> next;
                if(prevTempIminK == NULL)
                {
                    prevTempIminK = nodelist;
                }
                else
                {
                    prevTempIminK = prevTempIminK -> next;
                }
                
                b++;
            }
            b = 0;

            while ((i >= k) && (tempIminK -> value > temp -> value))
            {
                temp2 = nodelist;
                prevTemp2 = NULL;
                while (c < i)
                {
                    temp2 = temp2 -> next;
                    if(prevTemp2 == NULL)
                    {
                        prevTemp2 = nodelist;
                    }
                    else
                    {
                        prevTemp2 = prevTemp2 -> next;
                    }
                    c++;
                }
                c = 0;
                if (prevTempIminK == NULL)
                {
                    prevTemp2 -> next = tempIminK;
                    tempIminK -> next = temp2 -> next;
                    temp2 -> next = tempIminK -> next;
                    nodelist = temp2;
                }
                else
                {
                    prevTempIminK -> next = temp2;
                    prevTemp2 -> next = tempIminK;
                    temp2 -> next = tempIminK -> next;
                }
                
                i = iminusk;
                (*n_comp)++;
            }
            (*n_comp)++;
            temp2 = nodelist;
            while (d < i)
            {
                temp2 = temp2 -> next;
                d++;
            }
            d = 0;
            //holder = temp2 -> value;
            //temp2 -> value = temp -> value;
            temp -> value = holder;
        }
    }

    /*fprintf(stderr, "sequence success\n");

    sequence = (sequence - 1) / 3;
    k = sequence;
    /* Shellsort algorithm using while loops to make up for array indexing. 
    Any array indexing is used with a while loop to progress the linked list.

    while (temp != NULL)
    {
        fprintf(stderr, "%ld ", temp -> value);
        temp = temp -> next;
    }
    fprintf(stderr, "\n\n");

    

    temp = nodelist;

    while(k > 0) 
    {
        for(j = k; j < size; j++)
        {
            while (i != j) // increments temp and assigns i
            {
                temp = temp -> next;
                i++;
            }

            while (l != (i - k)) // assigns initial comparison for swapping loop
            {
                arraymintemp = arraymintemp -> next;
                l++;
                if (arraymintemp -> next == NULL)
                {
                    break;
                }
            }

            l = 0; // resets counter

            while ((i >= k) && (arraymintemp -> value > temp -> value))
            {
                fprintf(stderr, "values to swap: amt -> val: %ld, tmp -> val: %ld\n", arraymintemp -> value, temp -> value);
                holder = temp -> value; // Swap values
                temp -> value = arraymintemp -> value;
                arraymintemp -> value = holder;
                fprintf(stderr, "values after swap: amt -> val: %ld, tmp -> val: %ld\n\n", arraymintemp -> value, temp -> value);

                temp = nodelist; // Reassigns comparisons
                arraymintemp = nodelist;

                while (m != (i - k))
                {
                    temp = temp -> next;
                    arraymintemp = arraymintemp -> next;
                    m++;
                }

                m = 0;
                (*n_comp)++;
                i = i - k;
            }

            if (arraymintemp -> value <= temp -> value) // resets temp if failure to enter swapping loop
            {
                arraymintemp = nodelist;
            }

            (*n_comp)++;
            temp = nodelist;

            while (m != i)
            {
                temp = temp -> next;
                m++;
            }
            m = 0;
        }
        k = (k - 1) / 3;
    }*/
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
    fprintf(stderr, "\n");

    fclose(fptr);

    return(write_num);

}
