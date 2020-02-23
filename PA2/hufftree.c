#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "h_comp.h"

#define ASCIIMAX 256

List * Read_From_File(char * filename)
{
    FILE * fptr = fopen(filename, "r");
    
    if (fptr == NULL)
    {
        return(NULL);
    }

    List * chr_list = NULL;
    char chr = 'a';

    while ((chr != EOF)) // creates a new node for 
    {
        chr = fgetc(fptr);
        if (!feof(fptr))
        {
            chr_list = Add_Node(chr_list, chr);
        }
    }

    fclose(fptr);

    return(chr_list);

}

List * Add_Node(List * head, char chr)
{
    List * newNode = malloc(sizeof(*newNode));

    if (head == NULL) // checks if list has a head node
    {
        head = newNode;
        head -> next = NULL;
        head -> chr = chr;
        head -> freq = 1;

        return(head);
    }

    List * tmpNode = head;
    List * secondTemp = NULL;

    while(tmpNode != NULL) // checks if the character has already been read
    {
        if (chr == tmpNode -> chr)
        {
            (tmpNode -> freq)++;
            free(newNode); // New node wasn't used, freed to preserve memory

            return(head);
        }
        if (tmpNode -> next == NULL)
        {
            secondTemp = tmpNode;
        }
        tmpNode = tmpNode -> next;
        
    }

    secondTemp -> next = newNode;
    newNode -> next = NULL;
    newNode -> chr = chr;
    newNode -> freq = 1;

    return(head);

}

void Read_Freq(char * filename, List * head)
{
    FILE * fptr = fopen(filename, "wb");
    
    if (fptr == NULL) // checks if open succeeds
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    List * tmpNode = head;
    int i = 0;
    long zero = 0;
    int write = 0;

    while(i < ASCIIMAX)
    {
        if ((tmpNode -> chr) == i)
        {
            write = fwrite(&(tmpNode -> freq), sizeof(long), 1, fptr);
            i++;
        }
        else if (tmpNode -> next == NULL)
        {
            write = fwrite(&zero, sizeof(long), 1, fptr);
            i++;
        }
        if (write == 1)
        {
            tmpNode = head;
            write = 0;
        }
        else
        {
            tmpNode = tmpNode -> next;
        }

    }

    fclose(fptr);

}

void MergeSort(List ** headRef) 
{ 
    
    List * head = *headRef; 
    List * a; 
    List * b; 
    
    /* Base case -- length 0 or 1 */
    if ((head == NULL) || (head -> next == NULL)) 
    { 
        return; 
    } 
    
    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head, &a, &b); 

    /* Recursively sort the sublists */
    MergeSort(&a); 
    MergeSort(&b); 

    /* answer = merge the two sorted lists together */
    *headRef = SortedMerge(a, b); 
} 

List * SortedMerge(List * a, List * b) 
{ 
    List * result = NULL; 
  
    /* Base cases */
    if (a == NULL)
    {
        return b;
    } 
    else if (b == NULL) 
    {
        return a; 
    }
  
    /* Pick either a or b, and recur */
    if (a -> freq <= b -> freq) 
    { 
        result = a; 
        result -> next = SortedMerge(a -> next, b); 
    } 
    else 
    { 
        result = b; 
        result -> next = SortedMerge(a, b -> next); 
    } 
    return result; 
} 

void FrontBackSplit(List * source, List ** frontRef, List ** backRef) 
{ 
    List * fast; 
    List * slow; 
    slow = source; 
    fast = source -> next; 
  
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) 
    { 
        fast = fast -> next; 
        if (fast != NULL) 
        { 
            slow = slow -> next; 
            fast = fast -> next; 
        } 
    } 
  
    /* 'slow' is before the midpoint in the list, so split it in two 
    at that point. */
    *frontRef = source; 
    *backRef = slow -> next; 
    slow -> next = NULL; 
} 

long countNode(List * head)
{
    long count = 0;

    List * tempNode = head;

    while(tempNode != NULL)
    {
        tempNode = tempNode -> next;
        count++;
    }

    return(count);
}

Tree * Add_TreeNode(char chr, long freq)
{
    Tree * root = malloc(sizeof(Tree));

    root -> freq = freq;
    root -> chr = chr;
    root -> bin_code = NULL;
    root -> left = root -> right = NULL;

    return root; 
}

Tree * Merge_Tree(Tree * node1, Tree * node2)
{
    Tree * root = malloc(sizeof(*root));

    root -> left = node1;
    root -> right = node2;
    root -> chr = '\0';
    root -> freq = node1 -> freq + node2 -> freq;

    return root;
}

TreeList * createTLNode(Tree * root)
{
    TreeList * head = malloc(sizeof(*head));

    head -> next = NULL;
    head -> treeptr = root;

    return head;
}

TreeList * TL_Insert(TreeList * head, TreeList * node)
{
    if (head == NULL)
    {
       // fprintf(stderr, "head is NULL\n");
        return node;
    }

 //   fprintf(stderr, "entering assign\n");
 //   fprintf(stderr, "head: %ld\n", head -> treeptr -> freq);
    if (node -> treeptr == NULL)
    {
        fprintf(stderr, "NULL\n");
    }
 //   fprintf(stderr, "node: %ld\n", node -> treeptr -> freq);

    long freq1 = (head -> treeptr -> freq); 
    long freq2 = (node -> treeptr -> freq); // SEG FAULTS HERE, CANNOT FIND A REASON

  //  fprintf(stderr, "assignment success\n");

    if (freq1 > freq2)
    {
        node -> next = head;
        return node;
    }

    head -> next = TL_Insert(head -> next, node);

    return head;
}

TreeList * TL_Build(Tree ** treeArray, long size)
{
    long i = 0;
    TreeList * head = NULL;
 //   fprintf(stderr, "%ld\n", size);
    
    for (i = 0; i < size; i++)
    {
   //     fprintf(stderr, "enter array\n");
        if (treeArray[i] == NULL)
        {
            fprintf(stderr, "treearray is null\n");
        }
        TreeList * node1 = createTLNode(treeArray[i]);
    //    fprintf(stderr, "addnode success\n");
        if (node1 -> treeptr == NULL)
        {
            fprintf(stderr, "node1 tree is null\n");
        }
        head = TL_Insert(head, node1);
        //fprintf(stderr, "insert success\n");

    }
   // fprintf(stderr, "for loop completion\n");

    return head;
}
List * Free_Node(List * head, List * nodeToDelete)
{
    List * temp = head;

    if (head == nodeToDelete)
    {   
        free(head);

        return (temp -> next);
    }
    
    while (temp -> next != nodeToDelete)
    {
        temp = temp -> next;
    }

    List * ln = temp -> next;

    free(temp -> next);

    temp -> next = ln -> next;

    return(head);

}

Tree * Build_Tree(List * head)
{
    long size = countNode(head);

    Tree ** treeArray = malloc(sizeof(Tree *) * size);
    List * tempNode = head;
    long i = 0;

    while(tempNode != NULL) // Fills treeArray with tree nodes
    {
        treeArray[i] = Add_TreeNode(tempNode -> chr, tempNode -> freq);
        tempNode = tempNode -> next;
        i++;
    }

    TreeList * headTree = TL_Build(treeArray, size);

  //  fprintf(stderr, "build success\n");

    if (headTree == NULL)
    {
        fprintf(stderr, "headTree alloc fail\n");
    }

    while (headTree -> next != NULL)
    {
        TreeList * second = headTree -> next;
        TreeList * third = second -> next;
        Tree * tn1 = headTree -> treeptr;
        Tree * tn2 = second -> treeptr;

        free(headTree);
        free(second);

        headTree = third;
      //  fprintf(stderr, "headtree reassign success\n");
        Tree * mrg = Merge_Tree(tn1, tn2); // branch nodes are created with '\0' as chr value
       // fprintf(stderr, "merge success\n");
        TreeList * ln = createTLNode(mrg);
       // fprintf(stderr, "newnode success\n");

        headTree = TL_Insert(headTree, ln);
       // fprintf(stderr, "insert success\n");
    }

    return (headTree -> treeptr);
}

void printTreeNode(FILE * filename, Tree * node)
{
    if (node -> chr == '\0')
    {
        fprintf(filename, "0");
    }
    else
    {
        fprintf(filename, "1%c", node -> chr);
    }
}

void PreOrder_Traverse(FILE * filename, Tree * node)
{
    if (node == NULL)
    {
        return;
    }

    printTreeNode(filename, node);
    PreOrder_Traverse(filename, node -> left);
    PreOrder_Traverse(filename, node -> right);

}

void PreOrder_Traverse_Write(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, "w");

    if (fptr == NULL)
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    PreOrder_Traverse(fptr, root);
    
    fclose(fptr);
}

void PreOrder_Traverse_Code(char * filename, Tree * root)
{
    FILE * fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        fprintf(stderr, "fopen fail\n");
    }

    long zero = 0;
    long depth = 0;

    printCodes(root, zero, depth, fptr);
 
}

void printCodes(Tree * node, long zero_bin, long depth, FILE * filename)
{
    long i;
    unsigned char un_chr;
    long temp = zero_bin;

    if ((node -> left == NULL) && (node -> right == NULL))
    {
        fprintf(filename, "%c:", node -> chr);
        node -> bin_code = zero_bin;
        for(i = 0; i < depth; i++)
        {
            temp = zero_bin >> (depth - (i + 1));
            un_chr = temp & 0x01;
            fprintf(filename, "%d", un_chr);
        }
        fprintf(filename, "\n");
        return;
    }

    zero_bin = zero_bin << 1;
    depth++;
    printCodes(node -> left, zero_bin, depth, filename);

    zero_bin = zero_bin + 0x01;
    printCodes(node -> right, zero_bin, depth, filename);

}

void print2DUtil(Tree *root, int space) 
{ 
    // Base case 
    if (root == NULL) 
        return; 
  
    // Increase distance between levels 
    space += COUNT; 
  
    // Process right child first 
    print2DUtil(root->right, space); 
  
    // Print current node after space 
    // count 
    fprintf(stderr, "\n"); 
    for (int i = COUNT; i < space; i++) 
        fprintf(stderr, " "); 
    fprintf(stderr, "%ld, %c\n", root->freq, root -> chr); 
  
    // Process left child 
    print2DUtil(root->left, space); 
} 

void printLinkedList(List * head)
{
    List * tmpNode = head;
    while (tmpNode != NULL)
    {
        fprintf(stderr, "chr: %c\nfreq: %ld\n", tmpNode -> chr, tmpNode -> freq);
        tmpNode = tmpNode -> next;
    }
}
