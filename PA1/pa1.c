#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        return (EXIT_FAILURE); // not enough arguments for function (i.e. no i/o file)
    }

    int pos_num = 0;
    long * array = NULL;
    int size = 0;
    long num_comp = 0;
    Node * list = NULL;
    int num_written = 0;
    char a[] = "-a";
    char l[] = "-l";

    FILE * fptr = fopen(argv[2], "r");

    if (!(strcmp(argv[1], a)))
    {

        if (fptr == NULL)
        {
            fprintf(stderr, "%s", "fopen fail\n");
            return EXIT_FAILURE;
        }

        fseek(fptr, 0, SEEK_END); // Find the position of the eof and use ftell to find the amount of bytes in the file
        pos_num = ftell(fptr);
        rewind(fptr);


        size = pos_num / sizeof(long); // Calculate the amount of long ints in the file

        fclose(fptr);

        array = Array_Load_From_File(argv[2], &size); // Array sorting
        Array_Shellsort(array, size, &num_comp);

        Array_Save_To_File(argv[3], array, size);

        fprintf(stdout, "%ld\n", num_comp);

        return 0;

    }
    else if (!(strcmp(argv[1], l)))
    {

        list = List_Load_From_File(argv[2]);
        list = List_Shellsort(list, &num_comp);

        num_written = List_Save_To_File(argv[3], list);

        fprintf(stdout, "%ld\n", num_comp);

		fclose(fptr);

        return 0;
    }
    else
    {
      return EXIT_FAILURE;
    }
}
