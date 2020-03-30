#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"
#include "hbtfun.h"

int main(int argc, char ** argv)
{
    char b[] = "-b";
    char e[] = "-e";

    if (!(strcmp(argv[1], b)))
    {
        FILE * fptr = fopen(argv[2], "rb");

        if (fptr == NULL)
        {
            fprintf(stdout, "%d\n", -1);
            return EXIT_FAILURE;
        }

        int key = 0;
        char mode = '0';
        Tnode * root = NULL;
        Tnode * newNode = NULL;

        while(!(feof(fptr)))
        {
            fread(&key, sizeof(int), 1, fptr);
            fread(&mode, sizeof(char), 1, fptr);

            if(!(feof(fptr)))
            {
                if (mode == 'i')
                {
                    newNode = createNode(key);
                    root = insertNode(root, newNode);
                }
                else
                {
                    deleteNode(root, key);  
                }
            }
        }

        fprintf(stdout, "%d\n", 1);

        printPreOrder(argv[3], root);

        destroyTree(root);
    }

    else if (!(strcmp(argv[1], e)))
    {
        int out1 = 0;
        int out2 = 0;
        int out3 = 0;
        int * key_array = NULL;
        int i = 0;
        char pattern = 0;
        long size = 0;
        Tnode * root = NULL;

        FILE * fptr = fopen(argv[2], "rb");

        if (fptr = NULL)
        {
            out1 = -1;
        }

        fseek(fptr, 0, SEEK_END);
        size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);


        while(!(feof(fptr)))
        {
            fread(key_array[i], sizeof(int), 1, fptr);
            fread(&pattern, sizeof(char), 1, fptr);

            buildPreOrder(root, key, pattern);
        }
    }

    return EXIT_SUCCESS;

}