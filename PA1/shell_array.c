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