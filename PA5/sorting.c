#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

long * recombineArray(long * temp1, long * temp2, int size1, int size2)
{
    int i = 0;
    int j = 0;
    int k = 0;
    long * newArray = malloc(sizeof(long) * (size1 + size2));

    while (i < size1 && j < size2)
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

    while (i < size1)
    {
        newArray[k] = temp1[i];
        i++;
        k++;
    }

    while (j < size2)
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

void swap(long * a, long * b) 
{ 
    long t = *a; 
    *a = *b; 
    *b = t; 
} 

void quickSortHelp(long * array, int first, int last)
{
    if (first >= last) 
    { 
        return;
    }

    long pivot = array[first];
    int low = first + 1;
    int high = last;

    while (low < high)
    {
        while ((low < last) && (array[low] <= pivot))
        {
            low++;
        }

        while ((first < high) && (array[high] > pivot))
        {
            high--;
        }

        if (low < high)
        {
            swap(&array[low], &array[high]);
        }
    }

    if (pivot > array[high])
    {
        swap(&array[first], &array[high]);
    }

    quickSortHelp(array, first, high - 1);
    quickSortHelp(array, low, last);
     
}

void Quick_Sort(long * array, int size)
{
    quickSortHelp(array, 0, size - 1);
}
