#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "shell_array.h"

long *Array_Load_From_File(char* filename, int* size)
{
    FILE * fptr = fopen(filename, 'r');
    long * long_arr = NULL;
    
    if (fptr == NULL) // Check if fopen fails
    {
        printf("fopen failed\n");
        *size = 0;
        return(long_arr);
    }

    long_arr = malloc((sizeof(long)) * (*size)); // Define long_arr to hold the exact amount of long ints in the file
    
    if (long_arr == NULL) // Check if malloc fails
    {
        printf("malloc failed\n");
        (*size) = 0;
    }
    
    if ((*size) == 0)
    {
        return (long_arr);
    }
    
    fread(long_arr, sizeof(long), size, fptr);

    return(long_arr);

}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    int i = 0;
    int j = 0;
    int h = 0;
    long holder = 0;

    for (h = 1; h <= (n_comp - 1) / 9; h = 3 * h + 1);
    for ( ; h > 0; h /= 3)
    {
        for (i = h + size; i <= n_comp; i++)
        {
            j = i;
            holder = array[i];
            while (j >= h + size && less(holder, array[j - h]))
            {
                array[j] = array[j - h];
                j -= h;
            }
            array[j] = holder;
        }
    }
}