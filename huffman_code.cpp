//
// Title: Huffman Coding
// Author: Minhyuk Nam
// Purpose: Compress the text file which is written in ASCII code into binary number, using tree structure
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TREE_HT 30

typedef struct node *node_pointer;
typedef struct node {
	node_pointer right;
	node_pointer left;
	int freq; //frequency of the character
	int letter; //character
};

int freq_count[127] = { 0 };
int num_actives = 0;
int before = 0;
int after = 0;
int count = 0;
node_pointer freq_pt;
int top = 0;
int code[MAX_TREE_HT];
int huffman_code[127][MAX_TREE_HT];

int tree(FILE*, FILE*);
void generate_code(FILE*, node_pointer* head, int top);
void free_node(node_pointer head);
void decode(FILE*, FILE*);
node_pointer new_node(void);
void merge(int, node_pointer*, node_pointer, node_pointer);
int findmin(node_pointer*, node_pointer*);

int main() {
	float rate = 0;
	float compress = 0;
	char filename[80];
	scanf("%s", filename);

	FILE *fp, *fp_tree, *fp_code;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Error opening file"); return 1;
	}

	fp_tree = fopen("huffman_tree.txt", "w");
	if (fp_tree == NULL) {
		printf("Error opening file"); return 1;
	}

	fp_code = fopen("huffman_coding.txt", "w");
	if (fp_code == NULL) {
		printf("Error opening file"); return 1;
	}

	tree(fp, fp_tree);
	decode(fp, fp_code);

	before = count*8;
	rate = (float)after / (float)before;
	compress = (1 - rate)*100;
	printf("%d\t%d\t%.2lf%%\n", before, after, compress);

	fclose(fp); fclose(fp_tree); fclose(fp_code);

	return 0;
}

int tree(FILE* fp, FILE* fp_tree) {
	int c = 0;
	int i = 0;
	int j = 0;
	int blank=0;
	node_pointer *nodes = NULL;
	node_pointer temp = NULL;
	node_pointer first = NULL;
	node_pointer second = NULL;
	node_pointer head = NULL;
	
	//determine frequency
	while (1) {
		c = fgetc(fp); if (c == EOF) break;
		freq_count[c]++; count++;
	}

	//determine # of activated characters
	for (i = 0; i<127; i++){
		if (freq_count[i]>0){
			num_actives++;
		}
	}
	
	//preparation for head nodes and parent index
	nodes = (node_pointer*)malloc(sizeof(node_pointer*)*num_actives);

	for (i = 0; i < num_actives; i++) {
		nodes[i] = NULL;
	}

	//prepare for leaves
	i = 0;
	for (j = 0; j < 127; j++){
		if (freq_count[j] > 0) {
			temp = new_node(); temp->right = NULL; temp->left = NULL;
			temp->freq = freq_count[j]; temp->letter = j;
			nodes[i++] = temp;
		}
	}

	i = num_actives;

	//make tree
	while (i > 1) {
		blank = findmin(nodes, &first);
		nodes[blank] = NULL;
		nodes[findmin(nodes, &second)] = NULL;
		merge(blank, nodes, first, second);
		i--;
	}

	//find head node
	for (i = 0; i<num_actives; i++){
		if (nodes[i] != NULL) break;
	}
	
	head = nodes[i];

	generate_code(fp_tree, &head, top);

	free(nodes);
	free_node(head);
	head == NULL;

	return 0;
}

void decode(FILE* fp, FILE* fp_code) {
	char c = 0;
	int i = 0;
	int j = 0;
	
	rewind(fp);
	while (1) {
		c = fgetc(fp);
		i = (int)c;
		if (i == -1) break;
		j = 0;
		while (huffman_code[i][j] != -1) {
			fprintf(fp_code, "%d", huffman_code[i][j++]);
			after++;
		}
	}
}

node_pointer new_node(void) {
	node_pointer ptr;
	ptr = (node_pointer)malloc(sizeof(node));

	return ptr;
}

void free_node(node_pointer head) {
	if (head == NULL) return;
	free_node(head->left);
	free_node(head->right);

	free(head);
}

void merge(int blank, node_pointer* nodes, node_pointer first, node_pointer second) {
	int i = blank;
	node_pointer temp = new_node(); temp->left = first; temp->right = second;
	temp->freq = first->freq + second->freq;
	nodes[i] = temp;
}

int findmin(node_pointer *nodes, node_pointer *return_node) {
	int i = 0;
	int min = 0;
	for (min = 0; min < num_actives; min++) {
		if (nodes[min] != NULL) break;
	}
	for (i = 0; i<num_actives; i++) {
		if (nodes[i] == NULL) continue;
		else if ((nodes[i]->freq) <= (nodes[min]->freq))
			min = i;
	}
	*return_node = nodes[min];

	return min;
}

void generate_code(FILE* fp_code, node_pointer* head, int top) {
	int i = 0;
	int j = 0;

	if ((*head)->left) {
		code[top] = 0;
		generate_code(fp_code, &(*head)->left, top + 1);
	}

	if ((*head)->right) {
		code[top] = 1;
		generate_code(fp_code, &(*head)->right, top + 1);
	}

	if (!((*head)->right) && !((*head)->left)) {
		//save in huffman_code array
		i = (*head)->letter;
		for (j = 0; j < top; j++) {
			huffman_code[i][j] = code[j];
		}
		huffman_code[i][j] = -1;

		fprintf(fp_code, "%5c", (*head)->letter);
		fprintf(fp_code, "%5d\t", (*head)->freq);
		for (i = 0; i < top; i++) {
			fprintf(fp_code, "%d", code[i]);
		}
		for (j=i; i < 30; i++) {
			fprintf(fp_code, " ");
		}
		fprintf(fp_code, "%5d\n", top);
	}
}
