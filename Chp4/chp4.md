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
We have seen a method to store set of elements using _"sequential representation"_ ( _i.e.,_ array) which is quite powerful.
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

### Merge two list in assending order
```c
void sort_merge(node_pointer x, node_pointer y, node_pointer* z){ /* merge two list in asscending order */
  node_pointer last;
  last = (node_pointer)malloc(sizeof(node));
  *z = last; /* new sorted list will be start from z */
  
  while(x && y){ /* x and y move and point each linked list */
    if(x->data <= y->data) /* change <= to >= for descending order */
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
We can also operate stacks and queues with linked list rather array!

### Stacks
#### Declare
```c
#define MAX_STACKS 10 /* maximum number of stacks */
#define IS_EMPTY(ptr)(!(ptr))
#define IS_FULL(ptr)(!(ptr))

typedef struct{
  /* some fields */
} element;

typedef struct stack* stack_pointer;
typedef struct{
  element data;
  stack_pointer link;  
} stack;

stack_pointer top[MAX_STACKS]; /* purpose? SEE P22 */
```

#### Push
```c
void pushs(stak_pointer *top, element item){
  stack_pointer temp = (stack_pointer)malloc(sizeof(stack));
  if(IS_FULL(temp)){
    printf("the memory is full");
    exit(1);
  }
  
  temp->item = item;
  temp->link = *top; *top = temp; /* temp become the first element in stack */
}
```

#### Pop
```c
element pops(stak_pointer *top){
  stack_pointer temp = *top;
  element item;
  
  if(IS_EMPTY(temp)){
    printf("the stack is empty");
    exit(1);
  }
  
  item = temp->item; /* get data */
  *top = temp->link; /* change top */
  free(temp);
  return item;
}
```

### Queues
Similiar to stack!

#### Declare
```c
#define MAX_QUEUES 10 /* maximum number of stacks */
#define IS_EMPTY(ptr)(!(ptr))
#define IS_FULL(ptr)(!(ptr))

typedef struct{
  /* some fields */
} element;

typedef struct queue* queue_pointer;
typedef struct{
  element data;
  queue_pointer link;  
} queue;

queue_pointer top[MAX_QUEUES]; /* purpose? SEE P22 */
```

#### Push
```c
void pushq(queue_pointer *top, queue_pointer *rear, element item){
  queue_pointer temp = (queue_pointer)malloc(sizeof(queue));
  if(IS_FULL(temp)){
    printf("the memory is full");
    exit(1);
  }
  
  temp->item = item; temp->link = NULL;
  
  //seperate the cases when queue is empty or not
  if(*top) (*rear)->link = temp; /*if queue is not empty, connect rear and temp */
  else *top = temp; /*if not, let the temp become the first queue */
  
  *rear = temp; /* temp become the last element in the queue */
}
```

#### Pop
```c
element popq(queue_pointer *top){ /* perfectly same with pops */
  queue_pointer temp = *top;
  element item;
  
  if(IS_EMPTY(temp)){
    printf("the queue is empty");
    exit(1);
  }
  
  item = temp->item; /* get data */
  *top = temp->link; /* change top */
  free(temp);
  return item;
}
```

## 4. Additional Operations
### Non-Circular Linked List: Chain
#### Invert Nodes
This function change the sequence of the linked list in circular

```c
node_pointer inver(node_pointer lead){
  node_pointer middle = NULL;
  node_pointer trail = NULL;
  
  while(lead){
    trail = middle; /* update trail from middle */
    middle = lead; /* update middle to lead */
    middle->link = trail;
    lead = lead->link; /* update lead */
}
```

#### Concatenate two chains
This function links to given pointer as circular linked list.

```c
//note that the ptr2 concatenate at the end of the linked list started from ptr1 
node_pointer concatenate(node_pointer ptr1, node_pointer ptr2){
  node_pointer temp;
  if(IS_EMPTY(ptr1)) return ptr2; /* if there is nothing after ptr1 */
  else{
    if(IS_EMPTY(ptr2)){
      for(temp = prt1; temp->link; temp = temp->link)
        ; /* goes to the end of ptr1; temp->link means as long as there is a link after temp */
      temp->link = ptr2;
    }
    return ptr1;
  }
}
```

### Circular Linked List
#### Motivation
To operate the list more efficiently, such as reusing the freed node, we introduce new idea **Circular Linked List**.

#### Adding new node at the front
This function add new node at the front of the circular list

```c
//assume that ptr is the last of the circular list
void insert_front(node_pointer *ptr, node_pointer node){
  if(IS_EMPTY(*ptr)){
   *ptr = node;
   node->link = node;
  }
  else{
    node->link = (*ptr)->link;
    (*ptr)->link = node;
  }
}
```

#### Counting the length of the list
This function counts the length of the circular list

```c
//assume that ptr is the begining of the circular list
int length(node_pointer ptr){
  node_pointer temp = NULL;
  int counter = 0;
  
  if(ptr){
    temp = ptr;
    
    do{
      count++; /* because there is at least one node 'ptr' */
      temp = temp->link;
    }while (temp != ptr);
    
    retrun count;  
}
```

#### Applications: Using freed node
##### Getting Node from avail
The function gets the freed node that are not in use if it is available, otherwise declare new node

```c
//assume that avail is the node_pointer that points to the first node in the list of freed nodes
node_pointer get_node(void){
  node_pointer node;
  if(avail){
    node = avail;
    avail = avail->link;
  }
  else{
    node = (node_pointer) malloc(sizeof(node));
    if(IS_FULL(node)){
      printf("The memory is full");
      exit(1);
  }
  return node;
}
```

##### Add Node to avail
This function frees node and add to link of usuable nodes

```c
//assume that avail is the node_pointer that points to the first node in the list of freed nodes
void ret_node(node_pointer ptr){
  ptr->link = avail;
  avail = ptr;
}
```

##### Erase Nodes***
This function erase unwanted node in between linked list in circular

```c
void cerase(node_pointer ptr){
  node_pointer temp;
  if(*ptr){
    temp = (*ptr)->link;
    (*ptr)->link = avail;
    avail = temp;
    *ptr = NULL;    
  }
}
```



## 5. Examples
### Polynomials
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp4/polynomial_list_v1.cpp)

### Equivalence Class
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp4/equiv_list_v1.cpp)

#### Sparse Matrix
[Implementation](https://github.com/mhnam/Data-Structure/blob/master/Chp4/matrix_list_v2.cpp)
