typedef struct _Tree
{
    int label;
    int height;
    int width;
    char nodeLabel;
    struct _Tree * left;
    struct _Tree * right;
} Tree;

typedef struct _List
{
    int label;
    int height;
    int width;
    char nodeLabel;
    struct _List * next;
    struct _List * previous;
} List;


Tree * buildTreeFromPostOrder(char * filename, int * upper_bound); // builds tree from given postorder traversal
List * createNode(List * head, int label, int width, int height);
Tree * constructTree(Tree ** treeArray, int * upper_bound);

Tree ** LLtoArray(List * head, int * size);
void freeLL(List * head);

void freeNode(List * toDelete);

void printPreOrder(char * filename, Tree * root); // prints tree with preorder traversal
void printTreeNode(FILE * fptr, Tree * root);

void Pack(char * filename, Tree * root); // packs tree
void PackHelper(FILE * fptr, Tree * root, int xorigin, int yorigin);

void printDimensions(char * filename, Tree * root);
void printDimHelper(FILE * fptr, Tree * root);

void print2DUtil(Tree *root, int space);
