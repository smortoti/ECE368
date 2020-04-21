typedef struct _Tree
{
    int label; // holds label
    int height; // holds height
    int width; // holdds width
    char nodeLabel; // determines if block is a branch or leaf, useful for cases where the int labels will conflict with the (int) of character labels of H and V
    struct _Tree * left; // left child
    struct _Tree * right; // right child
} Tree;

typedef struct _List
{
    int label; // holds label
    int height; // holds height
    int width; // holds width
    char nodeLabel; // same label as above
    struct _List * next; // double-linked list
    struct _List * previous;
} List;


Tree * buildTreeFromPostOrder(char * filename, int * upper_bound); // builds tree from given postorder traversal
List * createNode(List * head, int label, int width, int height); // creates LL node
Tree * constructTree(Tree ** treeArray, int * upper_bound); // constructs tree within top function

Tree ** LLtoArray(List * head, int size); // converts LL to array for easier build
void freeLL(List * head); // frees LL

void printPreOrder(char * filename, Tree * root); // prints tree with preorder traversal
void printTreeNode(FILE * fptr, Tree * root); // recursive helper

void Pack(char * filename, Tree * root); // packs tree
void PackHelper(FILE * fptr, Tree * root, int xorigin, int yorigin); // recursive helper

void printDimensions(char * filename, Tree * root); // prints dimensions
void printDimHelper(FILE * fptr, Tree * root); // recursive helper

void print2DUtil(Tree *root, int space); // debugging tree function

void destroyTree(Tree * root); // destroys tree
