#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
    clock_t begin = clock();
    Array_Shellsort(array, size, &num_comp);
    clock_t end = clock();
    double timeSpend = (double)(end - begin) / CLOCKS_PER_SEC;
    fprintf(stderr ,"list sorted in: %fs\n", timeSpend);

    Array_Save_To_File(argv[3], array, size);

    printf("%ld\n", num_comp);

    num_comp = 0; // resets comparisons to zero for linked list

   fprintf(stderr, "enter load\n");

    list = List_Load_From_File(argv[2]);
    fprintf(stderr, "load success\n");

    list = List_Shellsort(list, &num_comp);
    fprintf(stderr, "shellsort success\n");

    num_written = List_Save_To_File(argv[3], list);

    printf("%ld\n", num_comp);
    
    return(0);
}
