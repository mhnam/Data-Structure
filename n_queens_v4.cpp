//
// Title: N-Queens Problem
// Author: Minhyuk Nam
// Purpose: Find the solution for n-queens problem.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool Solve(int answer[], int MAX_col, int row);
bool Pass(int answer[], int TRY_col, int row, int MAX_col);
bool ColumnIsClear(int answer[], int TRY_col, int row);
bool RightDiagnoalIsClear(int answer[], int TRY_col, int row, int MAX_col);
bool LeftDiagnoalIsClear(int answer[], int TRY_col, int row);
void Save(int answer[], int TRY_col, int row);
void Remove(int answer[], int TRY_col, int row);

int main() {
	int MAX_col;
	int temp;
	int *solution;
	double time;
	clock_t start;

	printf("Input N: ");
	scanf("%d", &MAX_col);

	solution = (int*)calloc(MAX_col, sizeof(int));

	start = clock();
	temp = Solve(solution, MAX_col, 0);
	time = ((double)(clock() - start)) / CLOCKS_PER_SEC;

	printf("\n");
	if (temp) {
		for (int i = 0; i < MAX_col; i++)
			printf("%d ", solution[i]);
		printf("\n");
	}
	else
		printf("No solution\n\n");

	printf("\nTime: %.3fsec\n\n", time);

	free(solution);
	system("PAUSE");

	return 0;
}

/***
* Function: Solve(int answer[], int MAX_col, int row)
*
* Purpose:
* This function checks each row by trying each column to find appropriate one,
* and returns 1 if there is a solution, otherwise 0.
***/

bool Solve(int answer[], int MAX_col, int row) {
	if (row >= MAX_col) return true;
	for (int TRY_col = 0; TRY_col < MAX_col; TRY_col++) {
		if (Pass(answer, TRY_col, row, MAX_col)) {
			Save(answer, TRY_col, row);
			if (Solve(answer, MAX_col, row + 1)) return true;
			Remove(answer, TRY_col, row);
		}
	}
	return false;
}

/***
* Function: Pass(int answer[], int TRY_col, int row, int MAX_col)
*
* Purpose:
* This function checks given trial from 'Solve' funcion satisfies conditions -
* No duplicates on same column, and upper right and left diagonal -,
* and returns 1 if there is a solution, otherwise 0.
***/

bool Pass(int answer[], int TRY_col, int row, int MAX_col) {
	if (ColumnIsClear(answer, TRY_col, row) &&
		RightDiagnoalIsClear(answer, TRY_col, row, MAX_col) &&
		LeftDiagnoalIsClear(answer, TRY_col, row))
		return true;
}

/***
* Function: ColumnIsClear(int answer[], int TRY_col, int row)
*
* Purpose:
* This function checks given trial from 'Solve' funcion satisfies a condition -
* No duplicates on same column - and returns 1 if there is a solution, otherwise 0.
***/

bool ColumnIsClear(int answer[], int TRY_col, int row) {
	int i = row - 1;

	while (i >= 0) {
		if (answer[i] == TRY_col) return false;
		i--;
	}

	return true;
}

/***
* Function: RightDiagnoalIsClear(int answer[], int TRY_col, int row, int MAX_col)
*
* Purpose:
* This function checks given trial from 'Solve' funcion satisfies a condition -
* No duplicates on upper right diagonal - and returns 1 if there is a solution, otherwise 0.
***/

bool RightDiagnoalIsClear(int answer[], int TRY_col, int row, int MAX_col) {
	int i = row - 1;
	int j = TRY_col + 1;
	while (1) {
		if (i < 0 || j > MAX_col) break;
		if (answer[i] == j) return false;
		i--; j++;
	}
	return true;
}

/***
* Function: LeftDiagnoalIsClear(int answer[], int TRY_col, int row)
*
* Purpose:
* This function checks given trial from 'Solve' funcion satisfies a condition -
* No duplicates on upper left diagonal - and returns 1 if there is a solution, otherwise 0.
***/

bool LeftDiagnoalIsClear(int answer[], int TRY_col, int row) {
	int i = row - 1;
	int j = TRY_col - 1;
	while (1) {
		if (i < 0 || j < 0) break;
		if (answer[i] == j) return false;
		i--; j--;
	}
	return true;
}

/***
* Function: Save(int answer[], int TRY_col, int row)
*
* Purpose:
* This function saves given trial from 'Solve' funcion that satisfies a conditions -
* No duplicates on same column, and upper right and left diagonal - without any return values.
***/

void Save(int answer[], int TRY_col, int row) {
	answer[row] = TRY_col;
}

/***
* Function: Remove(int answer[], int TRY_col, int row)
*
* Purpose:
* This function removes (replace to -1) given trial from 'Solve' funcion without any return values, 
* if next row does not have any column(solution) that satisfies a conditions - 
* No duplicates on same column, and upper right and left diagonal. 
***/

void Remove(int answer[], int TRY_col, int row) {
	answer[row] = -1;
}
