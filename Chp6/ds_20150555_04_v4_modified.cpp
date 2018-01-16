#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 100

int simpleFind(int i, int* parent);
void simpleUnion(int i, int j, int* parent);
void KruskalMCST(int num_vertex, int num_edge, int edgeList[][3], int TreeEdge[][2], int* parent);

void main() {
	int n, graph[MAX_VERTICES][MAX_VERTICES];
	int m = 0;
	int i, j, temp;
	int parent[MAX_VERTICES];
	int edgeList[MAX_EDGES][3]; /* consists edge */
	int TreeEdge[MAX_EDGES][2]; /* save result */

	//file open
	FILE* fp_in = fopen("input.txt", "r");
	FILE* fp_out = fopen("output_20150555.txt", "w");
	fscanf(fp_in, "%d", &n);

	//save cost adjaceny matrix in the arryay, save vertices in n
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			fscanf(fp_in, "%d", &graph[i][j]);
			if (j > i && graph[i][j] < 1000) {
				edgeList[m][0] = i; edgeList[m][1] = j;
				edgeList[m++][2] = graph[i][j];
			}
		}
	}

	//sort edge list in non-decreasing order
	for (i = 1; i <= m; i++) {
		for (j = 0; j < m - 1; j++) {
			if (edgeList[j + 1][2] < edgeList[j][2]) {
				temp = edgeList[j][0]; edgeList[j][0] = edgeList[j + 1][0]; edgeList[j + 1][0] = temp;
				temp = edgeList[j][1]; edgeList[j][1] = edgeList[j + 1][1]; edgeList[j + 1][1] = temp;
				temp = edgeList[j][2]; edgeList[j][2] = edgeList[j + 1][2]; edgeList[j + 1][2] = temp;
			}
		}
	}

	//initialise parent
	for (i = 0; i < n; i++)
		parent[i] = -1;

	KruskalMCST(n, m, edgeList, TreeEdge, parent);

	//sort edge list in non-decreasing order
	for (i = 1; i < n; i++) {
		for (j = 0; j < n - 2; j++) {
			if (TreeEdge[j + 1][1] < TreeEdge[j][1]) {
				temp = TreeEdge[j][0]; TreeEdge[j][0] = TreeEdge[j + 1][0]; TreeEdge[j + 1][0] = temp;
				temp = TreeEdge[j][1]; TreeEdge[j][1] = TreeEdge[j + 1][1]; TreeEdge[j + 1][1] = temp;
			}
		}
	}

	//sort edge list in non-decreasing order
	for (i = 1; i < n; i++) {
		for (j = 0; j < n - 2; j++) {
			if (TreeEdge[j + 1][0] < TreeEdge[j][0]) {
				temp = TreeEdge[j][0]; TreeEdge[j][0] = TreeEdge[j + 1][0]; TreeEdge[j + 1][0] = temp;
				temp = TreeEdge[j][1]; TreeEdge[j][1] = TreeEdge[j + 1][1]; TreeEdge[j + 1][1] = temp;
			}
		}
	}

	//print all end nodes of the edge
	for (i = 0; i < n - 1; i++)
		fprintf(fp_out, "%d %d\n", TreeEdge[i][0], TreeEdge[i][1]);

}

int simpleFind(int i, int* parent) {
	for (; parent[i] >= 0; i = parent[i])
		;
	return i;
}

void simpleUnion(int i, int j, int* parent) {
	parent[i] = j;
}

void KruskalMCST(int num_vertex, int num_edge, int edgeList[][3], int TreeEdge[][2], int* parent) {
	int i = 0; 	int j = 0; 	int n = 0;
	int temp = 0; 	int temp_first = 0; 	int temp_second = 0;
	int temp_second_ = 0; int temp_index = 0;

	if (edgeList) { /* if edgelist is not NULL */
		while (i < num_vertex-1 && n <= num_edge) { /* till the num edge does not exceeds the #vertex - 1 */
			temp_first = edgeList[n][0]; temp_second = edgeList[n][1];
			temp_second_ = edgeList[n][1]; temp_index = temp_second_;

			while (1) {
				if (parent[temp_first] == -1) break;
				temp_first = parent[temp_first];
			}
			while (1) {
				if (parent[temp_second] == -1) break;
				temp_second = parent[temp_second];
			}

			if (temp_first != temp_second) { /* if it does not create a loop - end point is not in  */
				TreeEdge[i][0] = edgeList[n][0]; TreeEdge[i][1] = edgeList[n][1];
				
				if (parent[temp_index] != -1) {
					while(1){
						parent[parent[temp_index]] = temp_index;
						temp_index = parent[temp_index];
						if(temp_index == temp_second_) break;
					}
				}

				parent[temp_second_] = -1;

				simpleUnion(TreeEdge[i][1], TreeEdge[i][0], parent); i++; n++;
			}
			else n++;
		}
	}
}