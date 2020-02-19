
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
    struct Tree * treeptr;
} TreeList;

List * Read_From_File(char * filename);
List * Add_Node(List * head, char chr);

void Read_Freq(char * filename, List * head);

List * sort_List(List * head);

Tree * Build_Tree(TreeList * head);
Tree * Add_TreeNode(char chr, long freq);
Tree * Merge_Tree(Tree * node1, Tree * node2);
Tree * createBranch(Tree * node1, Tree * node2);

void PreOrder_Traverse(char * filename, Tree * treenode);

void PreOrder_Traverse_Code(char * filename, Tree * treenode);

void Compress(char * filenamein, char * filenameout, Tree * treenode);

void swap(List * node1, List * node2);

List * Free_Node(List * head, List * nodeToDelete);
List * Destroy_List(List * head);
