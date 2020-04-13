#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

void merge(long * array, int l, int m, int r)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int size1 = m - l + 1; 
    int size2 = r - m; 
  
    // creates temp arrays
    long * temp1 = malloc(sizeof(long) * size1);
    long * temp2 = malloc(sizeof(long) * size2); 
  
    // copies data to temp arrays
    for (i = 0; i < size1; i++)
    {
        temp1[i] = array[l + i];
    } 
    for (j = 0; j < size2; j++) 
    {
        temp2[j] = array[m + 1+ j]; 
    }

    
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 

    while (i < size1 && j < size2) 
    { 
        if (temp1[i] <= temp2[j]) 
        { 
            array[k] = temp1[i]; 
            i++; 
        } 
        else
        { 
            array[k] = temp2[j]; 
            j++; 
        } 
        k++; 
    } 
  
    // If there are any remaining elements from either temp array, add them to the merged array
    while (i < size1) 
    { 
        array[k] = temp1[i]; 
        i++; 
        k++; 
    } 
  
    while (j < size2) 
    { 
        array[k] = temp2[j]; 
        j++; 
        k++; 
    } 

    free(temp1);
    free(temp2);
}

void mergeSortHelp(long * array, int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2; // find middle index

        mergeSortHelp(array, l, m);
        mergeSortHelp(array, m + 1, r);

        merge(array, l, m, r);
    }
}

void Merge_Sort(long * array, int size)
{
    mergeSortHelp(array, 0, size - 1);
}

void swap(long * a, long * b) // function to swap nodes in an array
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
        while ((low < last) && (array[low] <= pivot)) // finds element that is smaller than pivot
        {
            low++;
        }

        while ((first < high) && (array[high] > pivot)) // finds element higher than pivot
        {
            high--;
        }

        if (low < high) // swaps elements if crossed indexes
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
