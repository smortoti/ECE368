#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "h_comp.h"

#define ASCIIMAX 256

List * Read_From_File(char * filename)
{
    FILE * fptr = fopen(filename, "rb"); // opens file
    
    if (fptr == NULL)
    {
        return(NULL);
    }

    List * chr_list = NULL;
    unsigned char chr = 'a';

    while (!feof(fptr)) // creates a new node for each character read
    {
        chr = fgetc(fptr);

        if (!feof(fptr)) // ensures eof isn't added to nodes
        {
            chr_list = Add_Node(chr_list, chr);
        }
    }

    fclose(fptr);

    return(chr_list);

}

List * Add_Node(List * head, unsigned char chr) // adds new node with char chr to linked list
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
            (tmpNode -> freq)++; // incremented freq of character
            free(newNode); // New node wasn't used, freed to preserve memory

            return(head);
        }
        if (tmpNode -> next == NULL)
        {
            secondTemp = tmpNode; // reassignment
        }
        tmpNode = tmpNode -> next;
        
    }

    secondTemp -> next = newNode; // assigns new node to end of list
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

    long zero = 0;
    int i = 0;

    if (head == NULL)
    {
        while (i < ASCIIMAX)
        {
            fwrite(&zero, sizeof(long), 1, fptr);
            i++;
        }
        fclose(fptr);
        return;
    }

    List * tmpNode = head;
    int write = 0;

    while(i < ASCIIMAX) // checks for all ascii values
    {
        if ((tmpNode -> chr) == i)
        {
            write = fwrite(&(tmpNode -> freq), sizeof(long), 1, fptr); // writes if character exists in list
            i++;
        }
        else if (tmpNode -> next == NULL) // writes last of list
        {
            write = fwrite(&zero, sizeof(long), 1, fptr);
            i++;
        }
        if (write == 1) // reassignment after writing
        {
            tmpNode = head;
            write = 0;
        }
        else
        {
            tmpNode = tmpNode -> next; // increment list
        }

    }

    fclose(fptr);

}

void MergeSort(List ** headRef) // Merge sort character linked list
{ 
    
    List * head = *headRef; 
    List * a; 
    List * b; 
    
    // Base case -- length 0 or 1 
    if ((head == NULL) || (head -> next == NULL)) 
    { 
        return; 
    } 
    
    // Split head into 'a' and 'b' sublists 
    FrontBackSplit(head, &a, &b); 

    // Recursively sort the sublists 
    MergeSort(&a); 
    MergeSort(&b); 

    // answer = merge the two sorted lists together 
    *headRef = SortedMerge(a, b); 
} 

List * SortedMerge(List * a, List * b) 
{ 
    List * result = NULL; 
  
    // Base cases 
    if (a == NULL)
    {
        return b;
    } 
    else if (b == NULL) 
    {
        return a; 
    }
  
    // Pick either a or b, and recur 
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
  
    // Advance 'fast' two nodes, and advance 'slow' one node 
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

long countNode(List * head) // counts linked list nodes
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

Tree * Add_TreeNode(char chr, long freq) // adds a node to the binary tree
{
    Tree * root = malloc(sizeof(Tree));

    root -> freq = freq;
    root -> chr = chr;
    root -> code = 0;
    root -> length = 0;
    root -> diff = 'L';
    root -> left = NULL;
    root -> right = NULL;

    return root; 
}

Tree * Merge_Tree(Tree * node1, Tree * node2) // merges two tree nodes from the forest into the tree
{
    Tree * root = malloc(sizeof(*root));

    root -> left = node1;
    root -> right = node2;
    root -> chr = '\0';
    root -> diff = 'B';
    root -> freq = node1 -> freq + node2 -> freq;
    root -> code = 0;
    root -> length = 0;

    return root;
}

TreeList * createTLNode(Tree * root) // creates a treeList node to bridge between linked list and tree
{
    TreeList * head = malloc(sizeof(*head));

    head -> next = NULL;
    head -> treeptr = root;

    return head;
}

TreeList * TL_Insert(TreeList * head, TreeList * node) // inserts treelist node
{
    if (head == NULL)
    {
        return node;
    }

    if (node -> treeptr == NULL)
    {
        fprintf(stderr, "NULL\n");
    }


    long freq1 = (head -> treeptr -> freq); 
    long freq2 = (node -> treeptr -> freq); 

    if (freq1 > freq2) // ensures sorted order
    {
        node -> next = head;
        return node;
    }

    head -> next = TL_Insert(head -> next, node);

    return head;
}

TreeList * TL_Build(Tree ** treeArray, long size) // builds tree list
{

    if (treeArray == NULL)
    {
      return NULL;
    }

    long i = 0;
    TreeList * head = NULL;
    
    for (i = 0; i < size; i++) // creates forest of tree nodes
    {
        if (treeArray[i] == NULL)
        {
            fprintf(stderr, "treearray is null\n");
        }
        TreeList * node1 = createTLNode(treeArray[i]);

        if (node1 -> treeptr == NULL)
        {
            fprintf(stderr, "node1 tree is null\n");
        }
        head = TL_Insert(head, node1); 

    }

    return head;
}
List * Free_Node(List * head, List * nodeToDelete) // node to free from linked list
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

Tree * Build_Tree(List * head) // builds binary tree from forest
{
    long size = countNode(head);
    Tree ** treeArray = NULL;

    if (size != 0)
    {
      treeArray = malloc(sizeof(Tree *) * size);
    }
    List * tempNode = head;
    long i = 0;

    while(tempNode != NULL) // Fills treeArray with tree nodes
    {
        treeArray[i] = Add_TreeNode(tempNode -> chr, tempNode -> freq);
        tempNode = tempNode -> next;
        i++;
    }

    TreeList * headTree = TL_Build(treeArray, size);

    if (headTree == NULL)
    {
        fprintf(stderr, "headTree alloc fail\n");
        return NULL;
    }

    while (headTree -> next != NULL) // recurses through to build nodes under the root
    {
        TreeList * second = headTree -> next;
        TreeList * third = second -> next;
        Tree * tn1 = headTree -> treeptr;
        Tree * tn2 = second -> treeptr;

        free(headTree);
        free(second);

        headTree = third;
        Tree * mrg = Merge_Tree(tn1, tn2); // branch nodes are created with '\0' as chr value
        TreeList * ln = createTLNode(mrg);

        headTree = TL_Insert(headTree, ln);
    }

    Tree * root = malloc(sizeof(*root));

    root -> chr = headTree -> treeptr -> chr;
    root -> freq = headTree -> treeptr -> freq;
    root -> left = headTree -> treeptr -> left;
    root -> right = headTree -> treeptr -> right;
    root -> code = headTree -> treeptr -> code;
    root -> length = headTree -> treeptr -> length;
    root -> diff = headTree -> treeptr -> diff;

    TreeList_Destroy(headTree); // frees treelist memory
    free(treeArray);
    return (root);
}

void printTreeNode(FILE * filename, Tree * node)
{
    if ((node -> left == NULL) && (node -> right == NULL))
    {
        fprintf(filename, "1%c", node -> chr);
    }
    else
    {
        fprintf(filename, "0");
    }
}

void PreOrder_Traverse(FILE * filename, Tree * node) // preorder traversal
{
    if (node == NULL)
    {
        return;
    }

    printTreeNode(filename, node);
    PreOrder_Traverse(filename, node -> left);
    PreOrder_Traverse(filename, node -> right);

}

void PreOrder_Traverse_Write(char * filename, Tree * root) // writes header using preorder traversal
{
    FILE * fptr = fopen(filename, "w");

    if (fptr == NULL)
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    if (root == NULL)
    {
        fclose(fptr);
        return;
    }

    PreOrder_Traverse(fptr, root);
    
    fclose(fptr);
}

void PreOrder_Traverse_Code(char * filename, Tree * root) // writes codes using preorder traversal
{
    FILE * fptr = fopen(filename, "wb");

    if (fptr == NULL)
    {
        fprintf(stderr, "fopen fail\n");
        return;
    }

    if (root == NULL)
    {
        fclose(fptr);
        return;
    }

    long zero = 0;
    long depth = 0;

    printCodes(root, zero, depth, fptr);

    fclose(fptr);
}

void printCodes(Tree * node, long zero_bin, long depth, FILE * filename)
{
    long i;
    unsigned char un_chr;
    long temp = zero_bin;

    if ((node -> left == NULL) && (node -> right == NULL)) // print leaf node
    {
        fprintf(filename, "%c:", node -> chr);

        node -> code = zero_bin;
        node -> length = depth;

        for(i = 0; i < depth; i++) // add one bit at a time
        {
            temp = zero_bin >> (depth - (i + 1)); // use binary to store codes
            un_chr = temp & 0x01;
            fprintf(filename, "%d", un_chr);
        }
        fprintf(filename, "\n");
        return;
    }

    zero_bin = zero_bin << 1;
    depth++;
    printCodes(node -> left, zero_bin, depth, filename);

    zero_bin = zero_bin | 0x01;
    printCodes(node -> right, zero_bin, depth, filename);
}

Tree * searchTree(Tree * root, char chr) // searches binary tree for a node and returns it
{
    Tree * temp = NULL;

    if (root != NULL)
    {
        if ((root -> chr == chr) && (root -> diff =='L'))
        {
            if (root -> left == NULL && root -> right == NULL)
            {
                return root;
            }
        }
        else
        {
            temp = searchTree(root -> left, chr);
            if (temp == NULL)
            {
                temp = searchTree(root -> right, chr);
            }
            return temp;
        }
    }
    else
    {
        return NULL;
    }
    return NULL;
}

int reverseBinary(int bin) // reverses a binary sequence
{
    int BITS = 8; 
    int reverse = 0, i, temp; 
  
    for (i = 0; i < BITS; i++) 
    { 
        temp = (bin & (1 << i)); 
        if(temp) 
            reverse |= (1 << ((BITS - 1) - i)); 
    } 
   
    return reverse; 
}

void Compress(char * filenamein, char * filenamehead, char * filenameout, Tree * root)
{
    /* 
    line 1: a long with the total number of bytes in the file after compression
    line 2: a long with the total number of bytes in the header
    line 3: a long with the number of chars in the uncompressed file
    line 4: header
    line 5 - end: compressed file
    */
    FILE * fptrin = fopen(filenamein, "r");

    if (fptrin == NULL)
    {
        fprintf(stderr, "fopen input fail\n");
    }

    FILE * fptrhead = fopen(filenamehead, "r");

    if (fptrhead == NULL)
    {
        fprintf(stderr, "fopen head fail\n");
    }

    FILE * fptrout = fopen(filenameout, "w");

    if (fptrout == NULL)
    {
        fprintf(stderr, "fopen output fail\n");
    }

    if (root == NULL)
    {
        fclose(fptrin);
        fclose(fptrhead);
        fclose(fptrout);
        return;
    }

    char chr = 'a';
    Tree * node = NULL;
    long headOut = 0;
    long bitCounter = 0;
    long temp = 0;
    int binholder = 0;
    long codeOutput = 0;
    long letter = 0;
    long pos_end = 0;
    long byteCounter = 0;

    fseek(fptrout, sizeof(long) * 3, SEEK_SET); // sets offset for lines 1-3 of output

    while(!(feof(fptrhead))) // prints header file in binary
    {
        chr = fgetc(fptrhead);

        if (chr == EOF)
        {
            break;
        }

        switch (chr) // uses switch to read header
        {
        case '0':
            headOut = headOut << 1;
            bitCounter++;
            break;

        case '1':
            headOut = headOut << 1;
            headOut |= 0x01;
            bitCounter++;
            break;
    
        default:
            headOut = headOut << 8;
            headOut |= chr;
            bitCounter += 8;
            break;
        }

        if (bitCounter >= 8)
        {
            temp = headOut >> (bitCounter - 8); // use bit storage for output
            binholder = reverseBinary(temp);
            fwrite(&binholder, 1, 1, fptrout);
            byteCounter++;
            bitCounter -= 8;

        }
    }

    if (bitCounter > 0) // prints remaining bits
    {
        byteCounter++;
        headOut = headOut << (8 - bitCounter);
        binholder = reverseBinary(headOut);
        fwrite(&binholder, 1, 1, fptrout);
    }

    chr = 'a';
    bitCounter = 0;

    while ((chr != EOF)) // reads input and prints code using tree
    {
        chr = fgetc(fptrin);

        if (feof(fptrin))
        {
        
        }
        else
        {
            node = searchTree(root, chr); // searches through tree for char

            if (node == NULL)
            {
                fprintf(stderr, "search node is NULL\n");
            }

            letter = 0;
            letter = letter | node -> code; // storage in binary sequence

            codeOutput = codeOutput << node -> length;
            codeOutput |= letter;
            bitCounter += node -> length;

            if (bitCounter >= 8) // prints byte
            {
                temp = codeOutput >> (bitCounter - 8);
                fwrite(&temp, sizeof(char), 1, fptrout);
                bitCounter -= 8;
            }

        }

    }

    if (bitCounter > 0) // prints remaining bits
    {
        temp = codeOutput << (8 - bitCounter);
        temp = reverseBinary(temp);
        fwrite(&temp, 1, 1, fptrout);
        bitCounter = 0;
    }
    
    // fseek is used to arrange for various output lines

    fseek(fptrout, 0, SEEK_END);
    pos_end = ftell(fptrout);

    fseek(fptrout, 0, SEEK_SET);
    fwrite(&pos_end, sizeof(long), 1, fptrout);

    fwrite(&byteCounter, sizeof(long), 1, fptrout);

    fseek(fptrin, 0, SEEK_END);
    pos_end = ftell(fptrin);

    fwrite(&pos_end, sizeof(long), 1, fptrout);

    fclose(fptrin);
    fclose(fptrhead);
    fclose(fptrout);
}

// Memory freeing functions
void List_Destroy(List * head)
{
    while (head != NULL)
    {
        List * temp = head -> next;
        free (head);
        head = temp;
    }
}

void Tree_Destroy(Tree * root)
{
    if (root == NULL)
    {
        return;
    }
    Tree_Destroy(root -> left);
    Tree_Destroy(root -> right);

    free(root);
}

void TreeList_Destroy(TreeList * head)
{
    while (head != NULL)
    {
        TreeList * temp = head -> next;
        free(head -> treeptr);
        free (head);
        head = temp;
    }
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
    fprintf(stderr, "%ld, %c:\n", root->freq, root -> chr); 
  
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
