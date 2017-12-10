#include <stdio.h>
#include <malloc.h>
//#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

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

	for (i = 0; i < n; i++) {
		out[i] = TRUE; seq[i] = NULL;
	}

	fscanf(fp, "%d%d", &i, &j);
	while (i >= 0) {
		x = (nodepointer)malloc(sizeof(struct node));
		x->data = j; x->link = seq[i]; seq[i] = x;
		x = (nodepointer)malloc(sizeof(struct node));
		x->data = i; x->link = seq[j]; seq[j] = x;
		fscanf(fp, "%d%d", &i, &j);
	}

	for (i = 0; i < n; i++) {
		if (out[i]) {
			printf("New class: %5d", i);
			out[i] = FALSE;
			x = seq[i]; top = NULL;
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j]) {
						printf("%5d", j); out[j] = FALSE;
						push(top, x);
						x=x->link;
					}
					else x = x->link;
				}
				if (!top) break;
				x=pop(&top);
				
			}
			printf("\n");
		}
	}
	fclose(fp);

}

void push(nodepointer* top, nodepointer x) {
	nodepointer y;

	x->link=top;
	top=x;
}

nodepointer pop(nodepointer* top) {
	nodepointer x;

	x=seq[top->data];
	top=top->link;

	return x;
}
