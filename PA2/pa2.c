#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "h_comp.h"

int main(int argc, char * argv)
{
    if (argc != 6)
    {
        fprintf(stderr, "%s", "Incorrect number of inputs\n");
        return(EXIT_FAILURE);
    }

    List * chr_freqs = NULL;
    Tree * huff_tree = NULL;

    chr_freqs = Read_From_File(argv[1]);

    if (chr_freqs == NULL)
    {
        fprintf(stderr, "List failure\n" );
        return(EXIT_FAILURE);
    }

    Read_Freq(argv[2], chr_freqs);

    huff_tree = Build_Tree(chr_freqs);

    if (huff_tree == NULL)
    {
        fprintf(stderr, "Tree failure\n");
        return (EXIT_FAILURE);
    }

    PreOrder_Traverse(argv[3], huff_tree);
    PreOrder_Traverse_Code(argv[4], huff_tree);

    Compress(argv[1], argv[5], huff_tree);

    return(EXIT_SUCCESS);
}