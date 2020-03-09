#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char ** argv)
{
    Tree * tree = NULL;
    int upper_bound = 0;

    tree = buildTreeFromPostOrder(argv[1], &upper_bound);

    printPreOrder(argv[2], tree);

    printDimensions(argv[3], tree);

    Pack(argv[4], tree);

    destroyTree(tree);
}
