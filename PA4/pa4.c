#include <stdint.h>
#include <stdio.h>
#include "hbt.h"
#include "hbtfun.h"

int main(int argc, char ** argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Incorrect number of inputs\n");
    }

    FILE * fptr = fopen(argv[1], "r");

    int key = 0;
    char mode = '0';

}