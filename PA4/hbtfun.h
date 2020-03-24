int isBST(Tnode * root, int min, int max);

int isBal(Tnode * root);

Tnode * insertNode(Tnode * root, Tnode * newNode);
void insertNodeHelp(Tnode * root, Tnode * newNode);
Tnode * createNode(int key);