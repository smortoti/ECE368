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
        char mode = '0';
        Tnode * root = NULL;
        Tnode * newNode = NULL;

        while(!(feof(fptr)))
        {
            fread(&key, sizeof(int), 1, fptr);
            fread(&mode, sizeof(char), 1, fptr);

            fprintf(stderr, "read success - key: %d, mode: %c\n", key, mode);

            if(!(feof(fptr)))
            {
                if (mode == 'i')
                {
                    newNode = createNode(key);
                    fprintf(stderr, "create success\n");
                    root = insertNode(root, newNode);
                    fprintf(stderr, "insert success\n");
                }
                else
                {
                   // deleteNode(root, key);  
                }
            }
        }

        fprintf(stdout, "%d\n", 1);

        print2DUtil(root, 5);

        printPreOrder(argv[3], root);

        destroyTree(root);

        return EXIT_SUCCESS;
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
        long count = 0;
        int key = 0;

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

        count = size / (sizeof(int) + sizeof(char));

        key_array = malloc(sizeof(int) * count);

        while(!(feof(fptr)))
        {
            fread(&key, sizeof(int), 1, fptr);

            if(!(feof(fptr)))
            {
                fread(&pattern, sizeof(char), 1, fptr);
                key_array[i] = key;
                i++;
            }
        }

        root = buildPreOrder(key_array, 0, count - 1);

        if (root != NULL)
        {
            out1 = 1;
        }

        if(out1 == 1)
        {
            out2 = isBST(root, INT32_MIN, INT32_MAX);
            out3 = isBal(root);

            fprintf(stdout, "%d,%d,%d\n", out1, out2, out3);
            fclose(fptr);

            return EXIT_SUCCESS; 
        }
        else
        {
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
