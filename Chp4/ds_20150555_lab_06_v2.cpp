#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 50	/* MAX SIZE */
typedef enum {head, entry} tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
        int row;
        int col;
        int value;
};
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		entry_node entry;
	} u;
};
matrix_pointer hdnode[MAX_SIZE];


// For "Openlab #6 : Matrix with linked list representation"
matrix_pointer new_node(void);		// Allocate Memory for matrix_pointer
matrix_pointer mread(FILE*);		// Read Matrix from File
void mwrite(FILE*, matrix_pointer);	// Write Matrix to File
void merase(matrix_pointer*);		// Free Matrix from Main Memory

// For "Homework #2 : Sparse Matrix"
matrix_pointer msub(matrix_pointer, matrix_pointer);	// Do Matrix Subtraction
matrix_pointer mtranspose(matrix_pointer);				// Do Matrix Transpose


void main(void)
{
    matrix_pointer a, b;

	FILE *fp_a, *fp_b;
	FILE *fp_a_write, *fp_b_write;
	FILE *fp_a_erase, *fp_b_erase;

	// File Open
	fp_a = fopen("A.txt", "r");
	fp_b = fopen("B.txt", "r");
	fp_a_write = fopen("A_write.txt", "w");
	fp_b_write = fopen("B_write.txt", "w");
	fp_a_erase = fopen("A_erase.txt", "w");
	fp_b_erase = fopen("B_erase.txt", "w");

	// Main Program Start
    a = mread(fp_a);
    b = mread(fp_b);
    mwrite(fp_a_write, a);
    mwrite(fp_b_write, b);
	merase(&a);
	merase(&b);
	mwrite(fp_a_erase, a);
	mwrite(fp_b_erase, b);

	// File Close
	fclose(fp_a); fclose(fp_b);
	fclose(fp_a_write); fclose(fp_b_write);
	fclose(fp_a_erase); fclose(fp_b_erase);
}


matrix_pointer new_node(void){
	matrix_pointer ptr;
	ptr = (matrix_pointer)malloc(sizeof(matrix_node));

	return ptr;
}

matrix_pointer mread(FILE* fp) {
	int num_rows, num_cols, num_heads, i;
	int row, col, value, current_row;
	matrix_pointer temp, last, node;

	fscanf(fp, "%d %d", &num_rows, &num_cols); /*reading the size of the martix*/
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	node = new_node(); node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if (!num_heads)
		node->right = node;
	else {
		//initialise head node
		for (i = 0; i < num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next = temp;
		}

		current_row = 0; last = hdnode[0];

		//getting input, and asign elements
		for (row = 0; row < num_rows; row++) {
			for (col = 0; col < num_cols; col++) {
				fscanf(fp, "%d", &value);

				if (value == 0)	continue;
				else {
					if (row > current_row) {
						last->right = hdnode[current_row];
						current_row = row; last = hdnode[row];
					}

					temp = new_node(); temp->tag = entry;
					temp->u.entry.row = row; temp->u.entry.col = col;
					temp->u.entry.value = value; last->right = temp; last = temp;
					hdnode[col]->u.next->down = temp;
					hdnode[col]->u.next = temp;
				}			
			}
		}
		
		//close last row
		last->right = hdnode[current_row];

		//close all column lists
		for (i = 0; i < num_cols; i++)
			hdnode[i]->u.next->down = hdnode[i];

		//link all head nodes together
		for (i = 0; i < num_heads - 1; i++)
			hdnode[i]->u.next = hdnode[i + 1];
		hdnode[num_heads - 1]->u.next = node;
		node->right = hdnode[0];
	}

	return node;
}

void mwrite(FILE* fp, matrix_pointer node)
{
	if (!node)
		return;
	else {
		int i;
		matrix_pointer temp, head = node->right;
		for (i = 0; i < node->u.entry.row; i++) {
			for (temp = head->right; temp != head; temp = temp->right)
				fprintf(fp, "%d %d %d\n", temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
			head = head->u.next;
		}
		return;
	}
}

void merase(matrix_pointer* node)
{
	int i, num_heads;
	matrix_pointer x, y, head = (*node)->right;

	for (i = 0; i<(*node)->u.entry.row; i++) {
		y = head->right;
		while (y != head) {
			x = y; y = y->right; free(x);
		}
		x = head; head = head->u.next; free(x);
	}

	//free remaining head nodes
	y = head;
	while (y != *node) {
		x = y; y = y->u.next; free(x);
	}
	free(*node); *node = NULL;
	
	return;
}

matrix_pointer msub(matrix_pointer A, matrix_pointer B)
{
	// TODO Homework #2
	return NULL;
}

matrix_pointer mtranspose(matrix_pointer node)
{
	// TODO Homework #2
	return NULL;
}
