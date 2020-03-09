typedef struct _Tree
{
    int label;
    int height;
    int width;
    struct _Tree * left;
    struct _Tree * right;
} Tree;

typedef struct _List
{
    int label;
    int height;
    int width;
    struct _List * next;
    struct _List * previous;
} List;


Tree * buildTreeFromPostOrder(char * filename); // builds tree from given postorder traversal
List * createNode(List * head, int label, int width, int height);

Tree ** LLtoArray(List * head, int * size);
void freeLL(List * head);

void freeNode(List * toDelete);

void printPreOrder(char * filename, Tree * root); // prints tree with preorder traversal

void Pack(Tree * root); // packs tree

void printDimesions(Tree * root);

void print2DUtil(Tree *root, int space);
