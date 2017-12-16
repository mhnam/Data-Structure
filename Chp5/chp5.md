# Chapter 5 Tree
Tree is a structure used when there is a hierarchy between data ( _c.f._ We assumed that there is no hierarchy between data
when using array or linked list)
* Pros: Easier than graph, less complex
* Cons: Less general to apply many differnet area as graph

## Contents
1. [Introduction](#1-introduction)
2. [Binary Trees](#2-binary-trees)
3. [Threaded Binary Trees](#3-threaded-binary-trees)
4. [Heaps](#4-heaps)
5. [Binary Search Trees](#5-binary-search-trees)
6. [Examples](#6-examples)

## 1. Introduction
### Motivation
To represent the importance or classification between data, we need a tree representation.
However we implement using linked list by adding two or more node pointer in the defined structure (namely node).

### Terminology
```
[DEFINITION] Tree

A Tree is a finite set of one or more nodes such that:

1) There is a specially designated node called the root
(there is no node that points to the root, but diverges from the root)

2) The remaining nodes (nodes except root) are partitioned into n>=0 disjoint sets 
where each of these sets forms a tree, which we are going to call as subtrees of the root.
```

* Node: **Node** is an item of information and the branches to other nodes

* Degree: Degree of a node is the number of subtrees of the node (we mainly consider 2 node each)

* Degree of a tree: **Degree of a tree** is the maximum degree of the nodes in the tree

* Root / Leaf (Terminal Node): **Root** is the starting point of the tree, while **leaf** is the last node of branches 
whose degree is zero (there is no subtree generated from the leaf)

* Parent / Children / Siblings : A node that has subtrees below, is called **Parent** of the roots of the subtrees,
and subtrees of the root(parent) are the children of the node. The children of the same parent is called **Siblings**.

* Ancestors / Decendants : The **ancestors** of a node are all the nodes along the path from the root to the node. Conversely, 
the **descendants**of a node are all the nodes that are in its subtrees

* Level of the node: Initially letting the root be level one, and for all subsequent nodes, the level is the level of the node's parent plus 1.

* Height(Depth) of a tree: The maximal level of any node in the tree

_c.f._
1) Tree has no node whose parent is more than one.
2) Tree has no cycle(loop) in the tree.

### Rerpesentation
Quite difficult to generally represent tree, because there is a possibility that degree of each node can be all different at this moment. Therefore, we are going to modify tree as 'binary tree' whose degree of a tree is 2 (node can have their children at most 2).

#### List Representation
Represent each node's children in the parenthesis
_e.g._
For complete binary tree where each data is entered alphabetically, (A(B(D,E),C(F,G)))

SEE Horowitz p.?? (fig 5.3) for details

#### Left Child-Right Sibling Representation
Let all node has only one branch that connects their children or sibling, so that parent will be connected to the
first children (namely left-most child) while their left-most child will connect left children of their parent, meaning siblings.

```c
typedef struct node* nodepointer;
typedef struct{
   int data
   nodepointer leftchild;
   nodepointer rightsibling;
}node;
```

_i.e.,_
1) By considering all branches as branch that connects their children, then we can push each node below which will give you
binary representation without losing any tree connection. -> Binary Tree!

## 2. Binary Trees
### Introduction
Binary Tree is introduced to implement tree as a data structure in computer with less complexity. By making constraint on 
the maximum number of degree of node, we can define structure to make the tree.

```
[DEFINITION] Binary Tree
Binary Tree is a finite set of nodes tat is either empty of consists of a root and two disjoint binary trees called the left
subtree and the right subtree
```

_i.e.,_
1) Binary tree is a tree that the degree of any given node must not exceed two.
2) There can be maximum 2^{i-1} where i>=1 number of nodes on level i; 
Hence, the maximum 2^k -1 where k>=1 number of nodes in a whole binary tree (called **full binary tree**)

_c.f.,_
1) There can be **empty** binary tree unlike a tree
2) In a bianry tree, we **distinguish between the order of the children** while in a tree we do not.
3) There are special type of binary tree - Skewed tree, Complete binary tree.
    * Skewed tree: a binary tree which is skewed to one direction (i.e., left or right)
    * Complete binary tree: a binary tree whose node is filled from left to right, top to bottom
    (i.e., each level is completely filled or filled from the left; iff its nodes correspond to the nodes numbered from 1 to n in the full binary tree of depth k)
    * Full binary tree: a bianry tree that is complete and there are 2^{i-1} nodes in each level i, so there are 2^k -1 nodes in the given full binary tree with depth k.

### Implementation
#### Matrix
Easy to implement and access but it can be sparse if it is skewed.

```c
#define MAX_NODES = 100;
tree[MAX_NODES]

/* for i th node, its parent is at floor(i/2)
while its left child is at 2i and right child is at 2i+1*/
```

#### Linked list
No such memory waste as matrix (array), b/c we dynamically allocate memory

```c
define struct tree* tree_pointer;
define struct{
   int data;
   tree_pointer left;
   tree_pointer right;
}tree;
```

### Operation(1): Traversals
There is six possible combinations of traversal, but we only consider three of them - inorder, postorder, preorder, which corresponds to the polynomial expression

* inorder: LVR
* postorder: LRV
* preorder: VLR
_c.f._
1) The name of order depends on the position of V while the order of LR is kept.

#### Inorder
```c
void inorder(tree_pointer prt){
   if(ptr){
      inorder(ptr->left_child); /* goes till no more left child */
      printf("%d", prt->data);
      inorder(ptr->right_child);
   }
}

void iter_inorder(tree_pointer prt){/* need STACK to implement! */
   int top = -1; /* initialise top */
   tree_pointer stack[MAX_STACK_SIZE]; /* declare stack array */
   for(;;){
      for(; node; node = node->left_child) /* keep goes to left */
         add(&top, node); /* save the sequence of path through far left */
      node = delete(&top);
      if(!node) break;
      printf("%d", node->data);
      node = node->right_child;
   }
}
```

#### Postorder (THINK ITERATIVE LOGIC)
```c
void postorder(tree_pointer prt){
   if(ptr){
      inorder(ptr->left_child);
      inorder(ptr->right_child);
      printf("%d", prt->data);      
   }
}


void iter_postorder1(tree_pointer prt){/* need STACK to implement! */
   int top = -1; /* initialise top */
   tree_pointer stack[MAX_STACK_SIZE]; /* declare stack array */
   for(;;){
      for(; node; node = node->left_child) /* keep goes to left */
         printf("%d", node);
         add(&top, node->right); /* save the sequence of path through far left */
      node = delete(&top);
      if(!node) break;
      node = node->left_child;
   }
}

void iter_postorder(tree_pointer prt){/* need STACK to implement! */
   int top = -1; /* initialise top */
   tree_pointer stack[MAX_STACK_SIZE]; /* declare stack array */
   for(;;){
      for(; node; node = node->left_child) /* keep goes to left */
         if(node)
            add(&top, node);
         if(node->right)
            add(&top, node->right); /* save the sequence of path through far left */
      node = delete(&top);
      if(!node) break;
      printf("%d", node->data);
      node = node->right_child;
   }
}

void iter_postorder2(tree_pointer prt){/* need STACK to implement! */
   int top = -1; /* initialise top */
   tree_pointer stack[MAX_STACK_SIZE]; /* declare stack array */
   add(&top, node);
   
   while(1){
      if (node->right)
         add(&top, node->right);
      if (node->left)
         add(&top, node->left);            

      node = delete(&top);
      if(!node) break;
      printf("%d", node->data);

   }
}
```

#### Preorder
```c
void preorder(tree_pointer prt){
   if(ptr){
      printf("%d", prt->data);
      inorder(ptr->left_child);
      inorder(ptr->right_child);
   }
}

void iter_preorder1(tree_pointer prt){/* need STACK to implement! */
   int top = -1; /* initialise top */
   tree_pointer stack[MAX_STACK_SIZE]; /* declare stack array */
   for(;;){
      for(; node; node = node->left_child) /* keep goes to left */
         printf("%d", node);
         add(&top, node->right); /* save the sequence of path through far left */
      node = delete(&top);
      if(!node) break;
      node = node->left_child;
   }
}

void iter_preorder2(tree_pointer prt){/* need STACK to implement! */
   int top = -1; /* initialise top */
   tree_pointer stack[MAX_STACK_SIZE]; /* declare stack array */
   add(&top, node);
   
   while(1){
      node = delete(&top);
      if(!node) break;
      printf("%d", node->data);

      if (node->right)
         add(&top, node->right);
      if (node->left)
         add(&top, node->left);
   }
}
```

#### Levelorder
```c
void levelorder(tree_pointer ptr){
   inf front = rear = 0;
   tree_pointer queue[MAX_QUEUE_SIZE];
   if(!ptr) return;
   addq(front, &rear, ptr); /* save the root in queue */
   for(;;){
      prt = deleteq(&front, rear); /* pop-up each queue element once in a time */
      if(ptr){
         printf("%d", ptr->data); /* print the current queue */
         /* Since the sequence goes from left to right, and saves into queue,
         the printing sequence will always goes from left to right */
         if(ptr->left_child)
            addq(front, &rear, ptr->left_child);
         if(ptr->right_child)
            addq(front, &rear, ptr->right_child);
      }
      else break; /* if there is no more element in queue */
   }
}
```

### Operation(2): Copy
```c
tree_pointer copy(tree_pointer original){
   tree_pointer temp;
   
   if(original){
      temp = (tree_pointer)malloc(sizeof(tree));
      if(IS_FULL(temp)){
         printf("The memory is full\n");
         exit(1);
      }
      
      temp->left_child = copy(original->left_child);
      temp->right_child = copy(original->right_child);
      temp->data = original->data;
      return temp;
   }
   
   retrun NULL;
}
```

### Operation(3): Equality
```c
int equal(tree_pointer first, tree_pointer second){
   /* 1 if the pointer is both NULL or if all the elements including head, data of head, and recursively left and right element are equal*/
   return(!first && !second) || (first && second && (first->data == second->data) && equal(first->left_child, second->left_child) && equal(first->right_child, second->right->child))) 
}
```

### Operation(4): Satisfiability
```c

```

## 3. Threaded Binary Trees
### Introduction
A.J. Perlist and C. Thornton introduced a clever way to utilise n+1 unused NULL link when using n nodes.
They replace the null links by pointers called threads to point nodes that will be or should be visited when using inorder traversal. (let left_child->link to point inorder predecessor while right_child->link to point inorder successor)

### Implementation
```c
typedef struct treaded_tree* treaded_pointer
typedef struct{
   short int left_threaded;
   treaded_pointer left_child; /* flag to mark whether it is left_child or not*/
   char data;
   treaded_pointer right_child;
   short int right_threaded; /* flag to mark whether it is right_child or not*/
}threaded_tree;
```

### Operation(1): Find Inorder Succesor
To implement the threaded binary tree, we need to find inorder successor and predecessor!
```c
threaded_pointer insucc(threaded_pointer tree){
   threaded_pointer temp;
   temp = tree->right_child;
   
   if(tree->right_threaded) /* if the given node is not right last leaf */
      while(!temp->left_thread) /* goes till there is no more right_child */
      temp = temp->left_child
   return temp;
}
```

### Operation(2): Inorder Traversal
```c
void tinorder(threaded_pointer tree){
   threaded_pointer temp;
   
   while(1){
      temp = insucc(temp);
      if(temp == tree) break;
      printf("%3c", temp->data);
   }
   
   return NULL;
}
```

### Operation(3): Insert

## 4. Heaps
### Introduction

### Implementation

### Operation(1): Insert

### Operation(2): Delete


## 5. Binary Search Trees
### Introduction

### Implementation

### Operation(1): Search

### Operation(2): Insert

### Operation(3): Delete

## 6. Examples
### Set Representation
"NOT AVAILABLE AT THIS MOMENT"
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp5/???.cpp)
