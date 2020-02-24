#define COUNT 8

typedef struct _Tree // Binary Tree definition
{
    char chr; // Stores char value
    long freq; // Frequency of char
    long code;
    long length;
    struct _Tree * left;
    struct _Tree * right;
} Tree;

typedef struct _Node // Dynamic memory for frequency
{
    char chr; // Stores char value
    long freq; // Stored freq of char
    struct _Node * next;
} List;

typedef struct _List
{
    struct _List * next;
    Tree * treeptr;
} TreeList;

typedef struct _Code
{
    char chr;
    long code;
    long length;
    struct _Code * next;
} CodeList;

List * Read_From_File(char * filename);
List * Add_Node(List * head, char chr);

void Read_Freq(char * filename, List * head);

long countNode(List * head);

Tree * Build_Tree(List * head);
Tree * Add_TreeNode(char chr, long freq);
Tree * Merge_Tree(Tree * node1, Tree * node2);
List * Free_Node(List * head, List * nodeToDelete);


TreeList * createTLNode(Tree * root);
TreeList * TL_Insert(TreeList * head, TreeList * node);
TreeList * TL_Build(Tree ** treeArray, long size);


void PreOrder_Traverse_Write(char * filename, Tree * treenode);
void PreOrder_Traverse(FILE * filename, Tree * treenode);
void printPreOrder(Tree * node);
void printTreeNode(FILE * filename, Tree * node);

void PreOrder_Traverse_Code(char * filename, Tree * treenode);
void PreOrder_Traverse2(Tree * root, char chr);
void printCodes(Tree * root, long zero, long depth, FILE * filename);

void makeCodeList(CodeList * codeList, Tree * root);

void Add_CodeNode(CodeList * head, char chr, long bin_code, long length);
Tree * searchTree(Tree * root, char chr);
void Compress(char * filenamein, char * filenameout, Tree * root);

void FrontBackSplit(List * source, List ** frontRef, List ** backRef);
List * SortedMerge(List * a, List * b);
void MergeSort(List ** headRef);

// Debugging functions
void print2DUtil(Tree *root, int space);
void printLinkedList(List * head);
void printCodeList(CodeList * head);
