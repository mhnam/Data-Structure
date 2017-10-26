#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define FALSE 0
#define TRUE 1

//type definition
typedef struct {
	short int row;
	short int col;
	short int dir;
} element;

typedef struct {
	short int vert;
	short int horiz;
} offsets;

//declare variables
element stack[MAX_STACK_SIZE];
offsets move[8] = { -1,0, -1,1, 0,1, 1,1, 1,0, 1,-1, 0,-1, -1,-1 };

int mark[102][102];
int maze[102][102];
int EXIT_ROW, EXIT_COL;
int top;

//declare functions
void push(element A);
element pop(void);
void path(void);


//main fucntion
int main() {
	int i, j;
	FILE* fp = fopen("input.txt", "r");

	//initialise maze, mark arrays
	for (i = 0; i<102; i++) {
		for (j = 0; j<102; j++) {
			mark[i][j] = 0;
			maze[i][j] = 1;
		}
	}

	//read maze problem from the file
	fscanf(fp, "%d %d", &EXIT_ROW, &EXIT_COL);

	for (i = 1; i <= EXIT_ROW; i++) {
		for (j = 1; j <= EXIT_COL; j++)
			fscanf(fp, "%d", &(maze[i][j]));
	}

	//fine path
	path();

	system("PAUSE");
	return 0;
}

//define functions
void push(element A) {
	stack[++top] = A;
}

element pop(void) {
	return stack[top--];
}

void path(void) {
	/* output a path through the maze if such a path exists */
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.col, dir = position.dir;

		while (dir < 8 && !found) {
			/* move in direction dir */
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;

			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;

			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}

			else ++dir;
		}
	}

	if (found) {
		printf("The path is : \n");
		printf("row col \n");

		for (i = 0; i <= top; i++)
			printf("%2d %5d\n", stack[i].row, stack[i].col);

		printf("%2d %5d\n", row, col);
		printf("%2d %5d\n", EXIT_ROW, EXIT_COL);
	}

	else printf("The maze does not have a path \n");
}