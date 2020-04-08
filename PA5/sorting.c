#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

long *Array_Load_From_File(char* filename, int* size)
{
    FILE * fptr = fopen(filename, "r");
    long * long_arr = NULL;
    
    if (fptr == NULL) // Check if fopen fails
    {
        *size = 0;
        return(long_arr);
    }

    long_arr = malloc((sizeof(long)) * (*size)); // Define long_arr to hold the exact amount of long ints in the file
    
    if (long_arr == NULL) // Check if malloc fails
    {
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

void splitArray(long * array, long * temp1, long * temp2, int * size1, int * size2)
{

}

long * recombineArray(long * temp1, long * temp2, int * size1, int * size2)
{
    
}

void Merge_Sort(long * array, int size)
{
    if (size == 0 || size == 1)
    {
        return;
    }

    long * temp1 = NULL;
    long * temp2 = NULL;
    int size1 = 0;
    int size2 = 0;

    splitArray(array, temp1, temp2, &size1, &size2);

    Merge_Sort(temp1, size1);
    Merge_Sort(temp2, size2);

    array = recombineArray(temp1, temp2, size1, size2);
}

int Array_Save_To_File(char * filename, long * array, int size)
{
    FILE * fptr = fopen(filename, "wb");
    int write_num = 0;

    if (fptr == NULL) // Checks if fopen fails
    {
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

    free(array);

    return(write_num);
}