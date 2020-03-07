#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "packing.h"

Tree * buildTreeFromPostOrder(char * filename)
{
    FILE * fptr = fopen(filename, 'r');

    if (fptr == NULL)
    {
        return NULL;
    }

    int readTemp = 0;
    List * head = NULL;
    int position = 0;
    int i = 0;
    int label = 0;
    int width = 0;
    int height = 0;
    /* Read will have form of 
        %d ( %d , %d ) \n
    or
        &d \n
    */ 
    while(!(feof(fptr)))
    {
        readTemp = fgetc(fptr);
        if (readTemp == 'H' || readTemp == 'V')
        {
            head = createNode(head, readTemp, 0, 0);
        }
        else
        {
            if(!(feof(fptr)))
            {
                position = ftell(fptr);
                fseek(fptr, (long) (position - 1), SEEK_SET)
                fscanf(fptr, "%d(%d, %d)\n", &label, &width, &height);
                head = createNode(head, label, width, height);
            }
        }    
    }
    
    fclose(fptr);
}

List * createNode(List * head, int label, int width, int height)
{
    if (head == NULL)
    {
        List * temp = malloc(sizeof(*temp));

        temp -> label = label;
        temp -> height = height;
        temp -> width = width;
        temp -> next = NULL;

        head = temp;

        return(head);
    }

    List * newNode = malloc(sizeof(*newNode));
    List * temp = head;

    while (temp -> next != NULL)
    {
        temp = temp -> next;
    }

    newNode -> label = label;
    newNode -> height = height;
    newNode -> width = width;
    newNode -> next = NULL;
    temp -> next = newNode;

    return(head);
}