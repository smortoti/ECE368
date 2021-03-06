#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char ** argv)
{
    if (argc != 5)
    {
        return(EXIT_FAILURE);
    }
    
    Tree * tree = NULL;
    int upper_bound = 0;

    tree = buildTreeFromPostOrder(argv[1], &upper_bound);

    if (tree == NULL) // empty file check and return
    {
        fprintf(stderr, "EMPTY FILE\n");
        return(EXIT_FAILURE);
    }

    printPreOrder(argv[2], tree);

    printDimensions(argv[3], tree);

    Pack(argv[4], tree);

    destroyTree(tree);

    return (EXIT_SUCCESS);
}
