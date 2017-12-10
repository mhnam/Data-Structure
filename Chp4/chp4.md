# Chapter 4 List
List is another method (one is array) to store set of elements, but it does not have to be sequential as array.
* Pros: Easy to inset and delete between elements
* Cons: Difficult to access the exact element as array using index

## Contents
1. [Introduction](#1-introduction)
2. [Singly Linked Lists](#2-singly-linked-lists)
3. [Queues](#3-queues)
4. [Circular Queues using Dynamic Arrays](#4-circular-queues-using-dynamic-arrays)
5. [Examples](#5-examples)

## 1. Introduction
### Motivation
We have seen a method to store set of elements using _"sequential representation"_ (_i.e.,_array) which is quite powerful.
But it has some difficulties occurs when as follows:
* Insertion, Deletion of an arbitrary element; take time to push or pull all the elements
* Storing several list of varying sizes in different arrays of maximum size; some wast of storage (unused)

Therefore, sequential representation has some problems when we frequently modify its data. (However, it is still powerful
structure when we frequently access data randomly)

### Preliminaries in C
```c
int i = 0;
int* pi = NULL; /* use int* to denote it is a pointer variable that points integer type */
pi = &i; /* assign address to pointer variable using & */
i = 10;
*pi = 5; /* this is equivalent to i = 5 */
```
### Cautions
* Set all pointers to NULL when initialise the pointer or when not in use (b/c it may points unexpected memory location)
```c
if(!pointer) /* check whether pointer is NULL */
```
* Be careful with its type (use type casts to match with the actual variable type)
```c
int* pi = NULL;
pi = (int*)malloc(sizeof(int));
pf = (float*)pi;
```
* Dangling pointer
```c
float* pf = NULL;
pf = (float*)malloc(sizeof(float));
pf = (float*)malloc(sizeof(float)); /* this creates dangling pointer - address of original pointer get missing -, 
so that we can not access this pointer variable so that we cannot free forever.*/
```

## 2. Singly Linked Lists
### Idea
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node* node_pointer; /* called "self reference structure" */
typedef struct{
  int data; /* char data[4] for string with 3 letters */
  node_pointer next;
} node;

#define IS_EMPTY(ptr)(!(ptr))
#define IS_FULL(ptr)(!(ptr))

node_pointer ptr = NULL;
```

We make node to save each data by linked list. Each node has two space, one for actual data, and one for address of 
next data node. 

_i.e._
1) Assume that we need data set in A>B>C order. We do not have to assign each data in A, B, C in memory consequently as array, 
as long as A saves B's address, and B saves C's address.
2) The locations of the nodes may change on the different runs.
3) Insertion: declare new node and let the previous node to point new node, while new node points the one that previous node pointed before.
4) Deletion: just free the node you want to erase and let the node before deleted node to points the node afterward of deleted one.

### Make list
```c
node_pointer first, second;

first = (node_pointer)malloc(sizeof(node));
second = (node_pointer)malloc(sizeof(node));

ptr = first;
first->data = 10; first->next = second; /* first->data is equivalent to (*first).data */
second->data = 20; second->next = NULL; /* strcpy(second->data, "bat") is also possible for string data */
```

### Insertion
```c
temp = (node_pointer)malloc(sizeof(node));

temp->next = first->next; temp->data = 15;
first->next = temp;
```
### Deletion
## 3. Queues
## 4. Circular Queues using Dynamic Arrays
## 5. Examples
### Mazeing Problems

[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp3/maze_solve_v3.cpp)

### Evaluation of Expression

#### Infix

[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp2/)

### String

#### Pattern Matching: KMP Algorithm
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp2/KMP_v2.cpp)


## Useful Macros
