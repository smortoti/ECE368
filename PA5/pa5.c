#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sorting.h"


long * Array_Load_From_File(char * filename, int * size)
{
    FILE * fptr = fopen(filename, "rb");
    long * long_arr = NULL;

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    (*size) = fileSize / sizeof(long);

    if (fptr == NULL) // Check if fopen fails
    {
        fprintf(stderr, "fptr is NULL\n");
        *size = 0;
        return(long_arr);
    }

    if ((*size) == 0) // Check if size is 0
    {
        fprintf(stderr, "size is zero\n");
        return (long_arr);
    }

    long_arr = malloc((sizeof(long)) * (*size)); // Define long_arr to hold the exact amount of long ints in the file
    
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

int main(int argc, char ** argv)
{
    if (argc != 4)
    {
        return EXIT_FAILURE;
    }
    
    char m[] = "-m";
    char q[] = "-q";
    long * array = NULL;
    int size;

    array = Array_Load_From_File(argv[2], &size);

    if (!(strcmp(argv[1], m)))
    {
        Merge_Sort(array, size);
    }
    else if (!(strcmp(argv[1], q)))
    {
        Quick_Sort(array, size);
    }
    else
    {
        return EXIT_FAILURE;
    }

    Array_Save_To_File(argv[3], array, size);

    return EXIT_SUCCESS;
}
