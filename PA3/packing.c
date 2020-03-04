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

    fseek(fptr, 0, SEEK_END);
    
    int size = ftell(fptr);

    int * readArray = malloc(sizeof(int) * size);
    int * readTemp = 0;

    fseek(fptr, 0, SEEK_SET);

    int i = 0;
    /* Read will have form of 
        %d ( %d , %d ) \n
    or
        &d \n
    */ 
    while(!(feof(fptr)))
    {
        readTemp = fgetc(fptr);
        if (!(feof(fptr)) && !(readTemp == '(' || readTemp == ')'))
        {
            readArray[i] = readTemp;
            i++;
        }
    }




}