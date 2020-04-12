#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sorting.h"

int main(int argc, char ** argv)
{
    char m[] = "-m";
    char q[] = "-q";
    if (!(strcmp(argv[1], m)))
    {

    }
    else if (!(strcmp(argv[1], q)))
    {

    }
    else
    {
        return EXIT_FAILURE;
    }
    
}

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