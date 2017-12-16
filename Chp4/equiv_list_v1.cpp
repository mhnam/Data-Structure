#include <stdio.h>
#include <malloc.h>
//#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

// The algorithm goes through two different phases
// 1) Read the all input and store the equivalence pairs
// 2) Expand into classes start from 0

// We use linked list because there may be huge waste of memory if we use as array, but it is easy to implement
// However, we need easy access for each number, we use one-dimensional array rather two dimensional

typedef struct node *nodepointer;
typedef struct node {
	int data;
	nodepointer link;
};

void push(nodepointer* top, nodepointer x);
nodepointer pop(nodepointer* top);

void main() {
	short int out[MAX_SIZE];
	nodepointer seq[MAX_SIZE];
	nodepointer x, y, top;
	int i, j, n;

	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);
	
	//initialise array
	for (i = 0; i < n; i++) {
		out[i] = TRUE; seq[i] = NULL;
	}
	
	//FIRST PHASE: read all the inputs and add linked list after each array
	fscanf(fp, "%d%d", &i, &j);
	while (i >= 0) {
		//for i
		x = (nodepointer)malloc(sizeof(struct node));
		x->data = j; x->link = seq[i];seq[i] = x;
		/* give nodepointer saved in the array to new node's link and update array to new node */
		
		//for j
		x = (nodepointer)malloc(sizeof(struct node));
		x->data = i; x->link = seq[j]; seq[j] = x;
		
		//read next
		fscanf(fp, "%d%d", &i, &j);
	}

	//SECOND PHASE: print each elements once if the element is in the class
	for (i = 0; i < n; i++) {
		if (out[i]) {
			printf("New class: %5d", i);
			out[i] = FALSE; /* update to FALSE after print */
			x = seq[i]; top = NULL; /* start using stack */
			for (;;) {
				while (x) { /* go over linked list connected after each array and save to stack */
					j = x->data;
					if (out[j]) { /* if the given element is not printed yet */
						printf("%5d", j); out[j] = FALSE;
						push(top, x); 
						x = x->link;
					}
					else x = x->link; /* if the element is printed go to next element */
				}
				if (!top) break;
				x = pop(&top); /* go over till stack is empty */
			}
			printf("\n");
		}
	}
	fclose(fp);

}

void push(nodepointer* top, nodepointer x) {
	nodepointer y;

	x->link = top;
	top = x;
}

nodepointer pop(nodepointer* top) {
	nodepointer x;

	x=seq[top->data];
	top=top->link;

	return x;
}
