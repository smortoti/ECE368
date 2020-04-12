#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

long * recombineArray(long * temp1, long * temp2, int * size1, int * size2)
{
    int i = 0;
    int j = 0;
    int k = 0;
    long * newArray = malloc(sizeof(long) * (*size1 + *size2));

    while (i < *size1 && j < *size2)
    {
        if (temp1[i] <= temp2[j])
        {
            newArray[k] = temp1[i];
            k++;
            i++;
        }
        else
        {
            newArray[k] = temp2[j];
            k++;
            j++;
        }  
    }

    while (i < *size1)
    {
        newArray[k] = temp1[i];
        i++;
        k++;
    }

    while (j < *size2)
    {
        newArray[k] = temp2[j];
        j++;
        k++;
    }

    return newArray;
}

void Merge_Sort(long * array, int size)
{
    if (size == 0 || size == 1)
    {
        return;
    }

    int i = 0;
    int middle = size / 2;

    long * temp1 = malloc(sizeof(long) * middle);
    long * temp2 = malloc(sizeof(long) * (size - middle));

    for(i = 0; i < middle; i++)
    {
        temp1[i] = array[i];
    }

    for(i = 0; i < (size - middle); i++)
    {
        temp2[i] = array[middle + i];
    }

    Merge_Sort(temp1, middle);
    Merge_Sort(temp2, size - middle);

    array = recombineArray(temp1, temp2, middle, size - middle);

    free(temp1);
    free(temp2);
}

int partition(long * array, int size)
{
    int pivot = array[size - 1];
    int i = 0;
    int j = 0;
    long temp;

    for (j = 0; j < size; j++)
    {
        if (array[j] < pivot)
        {
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
            i++;
        }
    }

    temp = array[size];
    array[size] = array[i + 1];
    array[i + 1] = temp;
    
    return (i + 1);
}

void Quick_Sort(long * array, int size)
{
    if (size == 0 || size == 1)
    {
        return;
    }

    int partIdx = partition(array, size);

    long * temp1 = malloc(sizeof(long) * partIdx);
    long * temp2 = malloc(sizeof(long) * (size - partIdx));

    Quick_Sort(temp1, partIdx);
    Quick_Sort(temp2, size - partIdx);
}