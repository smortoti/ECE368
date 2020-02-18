#ifndef __H_COMP_H__
#define __H_COMP_H__

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

List * Read_From_File(char * filename);
List * Add_Node(List * head, char chr);

void Read_Freq(char * filename, List * head);

List * sort_List(List * head);

Tree * Build_Tree(List * head);
Tree * Add_TreeNode(List * head);

void PreOrder_Traverse(char * filename, Tree * treenode);

void PreOrder_Traverse_Code(char * filename, Tree * treenode);

void Compress(char * filenamein, char * filenameout, Tree * treenode);

List * Free_Node(List * head, List * nodeToDelete);
List * Destroy_List(List * head);

#endif