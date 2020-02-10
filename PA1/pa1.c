#include <stdlib.h>
#include <stdio.h>
#include "shell_array.h"
#include "shell_list.h"
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        return (EXIT_FAILURE); // not enough arguments for function (i.e. no i/o file)
    }

    int pos_num = 0;
    long element_num = 0;
    long * array = NULL;
    int size = 0;
    long num_comp = 0;

    FILE * fptr = fopen(argv[2], "r");

    if (fptr == NULL)
    {
        fprintf(stderr, "%s", "fopen fail\n");
    }

    fseek(fptr, 0, SEEK_END); // Find the position of the eof and use ftell to find the amount of bytes in the file
    pos_num = ftell(fptr);
    rewind(fptr);


    size = pos_num / sizeof(long); // Calculate the amount of long ints in the file

    fclose(fptr);

    array = Array_Load_From_File(argv[2], &size); // Array sorting

    Array_Shellsort(array, size, &num_comp);

    Array_Save_To_File(argv[3], array, size);

    printf("%ld\n", num_comp);

    return(0);
}