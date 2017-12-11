# Chapter 5 Tree
Tree is a structure used when there is a hierarchy between data ( _c.f._ We assumed that there is no hierarchy between data
when using array or linked list)
* Pros: Easy to use compare to graph, less complex
* Cons: Less general to apply many differnet area as graph

## Contents
1. [Introduction](#1-introduction)
2. [Binary Trees](#2-binary-trees)
-traversals
3. [Threaded Binary Trees](#3-threaded-binary-trees)
4. [Heaps](#4-heaps)
5. [Binary Search Trees](#5-binary-search-trees)
6. [Examples] (#6-examples)

## 1. Introduction
### Motivation
To represent the importance or classification between data, we need a tree representation.
However we implement using linked list by adding two or more node pointer in the defined structure.

### Terminology
```
[DEFINITION] Tree

A Tree is a finite set of one or more nodes such that:

1) There is a specially designated node called the root
(no such node that points to the root, but diverges from the root)

2) The remaining nodes are partitioned into n>=0 disjoint sets 
where each of these sets is a tree, which we are going to call as subtrees of the root.
```

* Node: Node is an item of information and the branches to other nodes
* Degree: Degree of a node is the number of subtrees of the node (we mainly consider 2 node each)
* Degree of a tree: Degree of a tree is the maximum degree of the nodes in the tree
* Root / Leaf (Terminal Node): **Root** is the starting point of the tree, while **leaf** is the last node of branches 
whose degree is zero
* Parent / Children / Siblings : A node that has subtrees below it is the **Parent** of the roots of the subtrees,
and the roots of the subtrees are the children of the node. The children of the same parent is called **Siblings**.
* Ancestors / Decendants : The **ancestors** of a node are all the nodes along the path from the root to the node. Conversely, 
the **descendants**of a node are all the nodes that are in its subtrees
* Level of the node: Initially let the root be at level one, and for all subsequent nodes,
the level is the level of the node's parent plus 1.
* Height(Depth) of a tree: The maximal level of any node in the tree

_c.f._
1) There can not be a node whose parent is more than one.
2) There can not be a cycle in the tree.

### Rerpesentation
Quite difficult to generally represent tree, because there is degree of each node are all different at this moment.
Therefore, we are going to generalise tree as 'binary tree' whose degree of every node is 2.

#### List Representation
See Horowitz p.??

#### Left Child-Right Sibling Representation
Let all node has only one branch that connects their children or sibling, so that parent will be connected to the
first children while their left children will be connected through their first child.

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
Hence, the maximum 2^k -1 where k>=1 number of nodes in a whole binary tree

_c.f.,_
1) There can be empty binary tree unlike a tree
2) In a bianry tree, we distringuish between the order of the children while in a tree we do not.
3) There are special type of binary tree - Skewed tree, Complete binary tree.
    * Skewed tree: a binary tree which is skewed to one direction (i.e., left or right)
    * Complete binary tree: a binary tree whose node is filled from left to right, top to bottom
    (i.e., each level is completely filled or filled from the left)


### Implementation
#### Matrix

#### Linked list

### Operation(1): Traversals
#### Inorder

#### Postorder

#### Preorder

### Operation(2): Copy

### Operation(3): Equality

### Operation(4): Satisfiability

## 3. Threaded Binary Trees
### Introduction

### Implementation

### Operation(1): Traversal

### Operation(2): Insert

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
