int isBST(Tnode * root, int min, int max);
int isBal(Tnode * root);

void findHeights(Tnode * root, int * leftBal, int * rightBal);

Tnode * insertNode(Tnode * root, Tnode * newNode);
void insertNodeHelp(Tnode * root, Tnode * newNode, Tnode * unbalNode);
Tnode * createNode(int key);

void printPreOrder(char * filename, Tnode * root);
void printPreOrderHelp(FILE * fptr, Tnode * root);

void deleteNode(Tnode * root, int toDelete);

void destroyTree(Tnode * root);