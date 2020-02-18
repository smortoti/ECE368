#include <stdio.h>
#include <stdlib.h>

int main();

int main()
{
int * array = malloc(4 * sizeof(int));
int i = 0;

for (i = 0; i < 4; i++)
{
    array[i] = i;
}
array = realloc((array + 1), 3 * sizeof(int));
for (i = 0; i < 3; i++)
{
    printf("%d\n", array[i]);
}
return 0;
}