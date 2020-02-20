
typedef struct _Tree // Binary Tree definition
{
    char chr; // Stores char value
    char * bin_code; // Stores binary code when obtained
    long freq; // Frequency of char
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

List * Read_From_File(char * filename);
List * Add_Node(List * head, char chr);

void Read_Freq(char * filename, List * head);

void sort_List(List * head);
void swap(List * node1, List * node2);

long countNode(List * head);

Tree * Build_Tree(List * head);
Tree * Add_TreeNode(char chr, long freq);
Tree * Merge_Tree(Tree * node1, Tree * node2);
List * Free_Node(List * head, List * nodeToDelete);


TreeList * createTLNode(Tree * root);
TreeList * TL_Insert(TreeList * head, TreeList * node);
TreeList * TL_Build(Tree ** treeArray, long size);


void PreOrder_Traverse_Write(char * filename, Tree * treenode);
void PreOrder_Traverse(Tree * treenode);
void printPreOrder(Tree * node);
void printTreeNode(Tree * node);

void PreOrder_Traverse_Code(char * filename, Tree * treenode);
void PreOrder_Traverse2(Tree * root, char chr);
void printCodes(Tree * root, long * indl, long * indr);

void Compress(char * filenamein, char * filenameout, Tree * treenode);
