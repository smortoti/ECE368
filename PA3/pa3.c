#include <stdio.h>
#include <stdlib.h>
#include "packing.h"

int main(int argc, char ** argv)
{
    Tree * tree = NULL;

    tree = buildTreeFromPostOrder(argv[1]);

    printPreOrder(argv[2], tree);
}