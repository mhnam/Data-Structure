# Chapter 4 List
List is another method (one is array) to store set of elements, but it does not have to be sequential as array.
* Pros: Easy to inset and delete between elements
* Cons: Difficult to access the exact element as array using index

## Contents
1. [Introduction](#1-introduction)
2. [Singly Linked Lists](#2-singly-linked-lists)
3. [Dynamically Linked Stacks and Queues](#3-dynamically-linked-stacks-and-queues)
4. [Additional Operations](#4-additional-operations)
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
### Introduction
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

void insert(node_pointer *ptr, node_pointer before, int data);
void delete(node_pointer *ptr, node_pointer before, node_pointer want_to_delete);

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
void insert(node_pointer *ptr, node_pointer before, int data){ /* insert new node after before, while ptr is the first node */
  temp = (node_pointer)malloc(sizeof(node));
  
  if(IS_FULL(temp)){ /* memory allocation error */
    printf("the memory is full");
    exit(1);
  }

  if(*ptr){ /* if there is at least one node in the list */
    temp->next = before->next; temp->data = data;
    before->next = temp;
  }
  else{
    temp->next = NULL; temp->data = data;
    *ptr = temp;
  }
}
```

### Deletion
```c
void delete(node_pointer *ptr, node_pointer before, node_pointer want_to_delete){ /* delete node after before, while ptr is the first node*/

  if (before)
    before->next = want_to_delete->next;
    
  else /* if the want_to_delete is the first node in the linked list */
    *ptr = (*ptr)->link;
    
  free(want_to_delete);
}
```

### Print
```c
void print(node_pointer ptr){
  printf("The list contains: ");
  for(; ptr; ptr = ptr->next)
    printf("%4d", ptr->data);
  printr("\n");
}
```

### Search
```c
node_pointer search(node_pointer ptr, int want_to_find){
  for(;ptr;ptr = ptr->next)
    if(ptr->data == want_to_find) return ptr;
  return ptr;
}
```

### Merge
```c
void merge(node_pointer x, node_pointer y, node_pointer* z){ /* merge two list in asscending order */
  node_pointer last;
  last = (node_pointer)malloc(sizeof(node));
  *z = last; /* new sorted list will be start from z */
  
  while(x && y){ /* x and y move and point each linked list */
    if(x->data <= y->data)
      last->link = x; last = x; x = x->next;
    else
      last->link = y; last = y; y=y->next;
  }
    if(x) last->next = x; /* to connect left nodes connected after x, to newly declared list */
    if(y) last->next = y; /* for y */
    last = *z; *z = last->next; free(last);
}
```

## 3. Dynamically Linked Stacks and Queues

## 4. Additional Operations

## 5. Examples
### Polynomials
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp4/maze_solve_v3.cpp)

### Equivalence Class


#### Sparse Matrix
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp4/)
