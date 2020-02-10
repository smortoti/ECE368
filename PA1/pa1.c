#include <stdlib.h>
#include <stdio.h>
#include "shell_array.h"
#include "shell_list.h"
int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return (EXIT_FAILURE); // not enough arguments for function (i.e. no i/o file)
    }

    long pos_num = 0;
    long element_num = 0;
    long * array = NULL;
    int size = 0;
    long num_comp = 0;

    FILE * fptr = fopen(argv[1], "rb");

    fprintf(stderr, "%s", "fopen success\n");

    fseek(fptr, 0, SEEK_END); // Find the position of the eof and use ftell to find the amount of bytes in the file
    pos_num = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    fprintf(stderr, "%s", "fseek success\n");

    size = pos_num / sizeof(long); // Calculate the amount of long ints in the file

    fclose(fptr);

    fprintf(stderr, "%s", "size success\n");

    array = Array_Load_From_File(argv[1], &size); // Array sorting

    fprintf(stderr, "%s", "array load success\n");

    Array_Shellsort(array, size, &num_comp);

    fprintf(stderr, "%s", "array shellsort success\n");

    Array_Save_To_File(argv[1], array, size);

    fprintf(stderr, "%s", "array write success\n");

    return(0);
}