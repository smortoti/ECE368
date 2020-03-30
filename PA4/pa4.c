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
        FILE * fptr = fopen(argv[1], "rb");

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

        printPreOrder(argv[2], root);

        destroyTree(root);
    }

    else if (!(strcmp(argv[1], e)))
    {
        
    }

    return EXIT_SUCCESS;

}