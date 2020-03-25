#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"
#include "hbtfun.h"

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Incorrect number of inputs\n");
        return EXIT_FAILURE;
    }

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

    while(fscanf(fptr, "%d %c\n", &key, &mode))
    {
        if (mode = 'i')
        {
            newNode = createNode(key);
            root = insertNode(root, newNode);
        }
        else
        {
            deleteNode(root, key);  
        }
    }

    deleteTree(root);

    return EXIT_SUCCESS;

}