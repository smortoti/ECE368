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


    //test for github -------------------------------

    long pos_num = 0;
    long element_num = 0;
    long array = NULL;
    int size = 0;

    FILE * fptr = fopen(argv[1], 'rb');

    fseek(fptr, 0, SEEK_END); // Find the position of the eof and use ftell to find the amount of bytes in the file
    pos_num = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);

    size = pos_num / sizeof(long); // Calculate the amount of long ints in the file

    fclose(fptr);

    array = Array_Load_From_File(argv[1], &size);
}