#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "shell_array.h"

long *Array_Load_From_File(char* filename, int* size)
{
    FILE * fptr = fopen(filename, "r");
    long * long_arr = NULL;
    
    if (fptr == NULL) // Check if fopen fails
    {
     //   fprintf(stderr, "fopen failed\n");
        *size = 0;
        return(long_arr);
    }

    long_arr = malloc((sizeof(long)) * (*size)); // Define long_arr to hold the exact amount of long ints in the file
    
    if (long_arr == NULL) // Check if malloc fails
    {
    //    fprintf(stderr, "malloc failed\n");
        (*size) = 0;
    }
    
    if ((*size) == 0) // Check if size is 0
    {
        return (long_arr);
    }
    
    fread(long_arr, sizeof(long), *size, fptr); // Reads from file into array

    fclose(fptr);

    return(long_arr);

}

void Array_Shellsort(long *array, int size, long *n_comp)
{
    int i = 0;
    int j = 0;
    long k = 0;
    long holder = 0;
    int sequence = 0;

    do
    {
        sequence = 3 * sequence + 1;
    }while(sequence < size);

    sequence = (sequence - 1) / 3;

    for(k = sequence; k > 0; k = (k - 1) / 3)
    {
        for(j = k; j < size; j++)
        {
            holder = array[j];
            i = j;

            while ((i >= k) && (array[i-k] > holder))
            {
                array[i] = array[i - k];
                i = i - k;
                (*n_comp)++;
            }
            (*n_comp)++;
            array[i] = holder;
        }
    }
}

int Array_Save_To_File(char * filename, long * array, int size)
{
    FILE * fptr = fopen(filename, "wb");
    int write_num = 0;

    if (fptr == NULL) // Checks if fopen fails
    {
        //fprintf(stderr, 'fopen fail\n');
        size = 0;
    }

    if (array == NULL) // Checks if array is valid
    {
        size = 0;
    }
    
    if ((size) == 0) // Checks valid size
    {
        return(fwrite(array, sizeof(long), size, fptr)); // Creates empty output file if any error occurs
    }

    write_num = fwrite(array, sizeof(long), size, fptr); // Writes to the new output file

    fclose(fptr); // Closes file

    return(write_num);
}