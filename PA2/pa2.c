#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "h_comp.h"

int main(int argc, char ** argv)
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

    fprintf(stderr, "read success\n");

    printLinkedList(chr_freqs);

    Read_Freq(argv[2], chr_freqs);

    fprintf(stderr, "freq success\n");

    printLinkedList(chr_freqs);

    MergeSort(&chr_freqs);

    fprintf(stderr, "sort success\n");

    printLinkedList(chr_freqs);

    huff_tree = Build_Tree(chr_freqs);

    fprintf(stderr, "build tree success\n");

    if (huff_tree == NULL)
    {
        fprintf(stderr, "Tree failure\n");
        return (EXIT_FAILURE);
    }

    print2DUtil(huff_tree, 0);

    PreOrder_Traverse_Write(argv[3], huff_tree);

    fprintf(stderr, "header write success\n");

    PreOrder_Traverse_Code(argv[4], huff_tree);

    fprintf(stderr, "code and write success\n");

   // CodeList * codeList = makeCodeList(huff_tree);

   // printCodeList(codeList);

    Compress(argv[1], argv[3], argv[5], huff_tree);

    fprintf(stderr, "compress success\n");

    return(EXIT_SUCCESS);
}
