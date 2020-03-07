#include <stdio.h>

typedef struct _Tree
{
    int label;
    int height;
    int width;
    _Tree * left;
    _Tree * right;
} Tree;

typedef struct _List
{
    int label;
    int height;
    int width;
    _List * next;
} List;


Tree * buildTreeFromPostOrder(char * filename); // builds tree from given postorder traversal
List * createNode(List * head, int label, int width, int height)

void * printPreOrder(char * filename, Tree * root); // prints tree with preorder traversal

void Pack(Tree * root); // packs tree

void printDimesions(Tree * root);