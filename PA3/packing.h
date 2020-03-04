typedef struct _Tree
{
    long name;
    long length;
    long width;
    _Tree * left;
    _Tree * right;
} Tree;

Tree * buildTreeFromPostOrder(char * filename); // builds tree from given postorder traversal

void * printPreOrder(char * filename, Tree * root); // prints tree with preorder traversal

void Pack(Tree * root); // packs tree

void printDimesions(Tree * root);