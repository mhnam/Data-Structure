#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sort(int input[], int output[], int n);

int main() {
	FILE *file = fopen("lab1.txt", "r");
	int *u, *s, i, j;
	int temp, size;
	double duration;
	clock_t start;

	//opening file
	if (file == NULL) {
		printf("file open error\n");
		return 1;
	}

	//reading file
	fscanf(file, "%d", &size);

	u = (int*)malloc(size * sizeof(int));
	s = (int*)malloc(size * sizeof(int));

	for (int i = 0; i < size; i++) {
		fscanf(file, "%d\n", &temp);
		u[i] = temp;
	}

	//checking input
	printf("INPUT DATA\n");
	for (int j = 0; j < size; j++)
		printf("%d", u[j]);
	printf("\n");

	//sorting
	start = clock();

	//sort(u, s, size);
	s[0] = u[0];
	for (i = 1; i < size; i++) {
		for (j = i-1; j>=0; j--) {
			if (u[i] < s[j])
				s[j + 1] = s[j];
			else
				break;
		}
		s[j+1] = u[i];
	}
	duration = ((double)(clock() - start));

	//checking output
	printf("OUTPUT DATA\n");
	for(int j = 0; j < size; j++)
		printf("%d", s[j]);
	printf("\n\nDuration of the program: %f\n\n", duration);
	
	//closing file
	fclose(file);
	
	/*if (fclose_state == NULL) {
		printf("file close error\n");
		return 1;
	}*/

	system("PAUSE");
	return 0;
}

/**********
insertion sorting function
**********/

void sort(int** input, int** output, int n) {
	
}