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
        fprintf(stderr, "enter b\n");
        FILE * fptr = fopen(argv[2], "rb");

        if (fptr == NULL)
        {
            fprintf(stdout, "%d\n", -1);
            return EXIT_FAILURE;
        }

        int key = 0;
        char mode = 0;
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
	    fclose(fptr);

        return EXIT_SUCCESS;
    }

    else if (!(strcmp(argv[1], e)))
    {
        int out1 = 0;
        int out2 = 0;
        int out3 = 0;
        int * key_array = NULL;
        char * pattern_array = NULL;
        int i = 0;
        char pattern = 0;
        long size = 0;
        long ncount = 0;
        int key = 0;
        int BSTeval = 1;

        Tnode * root = NULL;

        FILE * fptr = fopen(argv[2], "rb");

        if (fptr == NULL)
        {
            out1 = -1;
            fprintf(stdout, "%d,%d,%d\n", out1, out2, out3);
            return EXIT_FAILURE;
        }

        fseek(fptr, 0, SEEK_END);
        size = ftell(fptr);
        fseek(fptr, 0, SEEK_SET);

        ncount = size / (sizeof(int) + sizeof(char));

        key_array = malloc(sizeof(int) * ncount);
        pattern_array = malloc(sizeof(char) * ncount);

        while(!(feof(fptr)))
        {
            fread(&key, sizeof(int), 1, fptr);

            if(!(feof(fptr)))
            {
                fread(&pattern, sizeof(char), 1, fptr);
                key_array[i] = key;
                pattern_array[i] = pattern;
                i++;
            }
        }

        root = buildPreOrder(key_array, pattern_array, 0);

        if (root != NULL)
        {
            out1 = 1;
        }
        else
        {
            out1 = 0;
        }
        

        if(out1 == 1)
        {
            isBST(root, &BSTeval);
            out3 = isBal(root);

            fprintf(stdout, "%d,%d,%d\n", out1, BSTeval, out3);
            fclose(fptr);
            free(pattern_array);
            free(key_array);

            return EXIT_SUCCESS; 
        }
        else
        {
            fclose(fptr);
            free(pattern_array);
            free(key_array);
            fprintf(stdout, "%d,%d,%d\n", out1, out2, out3);

            return EXIT_FAILURE;
        }

    }
    else
    {
        fprintf(stderr, "Please check inputs to program\n");
        return EXIT_FAILURE;
    }
}
