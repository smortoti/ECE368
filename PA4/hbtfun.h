#include "hbt.h"

void isBST(Tnode * root, int * BSTeval);
int isBal(Tnode * root);

void findHeights(Tnode * root, int * leftBal, int * rightBal);

Tnode * insertNode(Tnode * root, Tnode * newNode);
void insertNodeHelp(Tnode * root, Tnode * newNode, Tnode * unbalNode, Tnode * prevUnbal);
Tnode * createNode(int key);

void printPreOrder(char * filename, Tnode * root);
void printPreOrderHelp(FILE * fptr, Tnode * root);

Tnode * CCWRotate(Tnode * root);
Tnode * CWRotate(Tnode * root);

Tnode * buildPreOrder(int * key_array, char * pattern_array, int index);

Tnode * deleteNode(Tnode * root, int toDelete);

void destroyTree(Tnode * root);

void print2DUtil(Tnode * root, int space);
