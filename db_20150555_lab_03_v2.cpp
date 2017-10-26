#include <stdio.h>
#include <string.h>

#define max_string_size 100
#define max_pattern_size 100

int pmatch(char *string, char *pat, int *failure);
void fail(char *pat, int *failure);

int main() {
	//Create variables
	FILE *filea = fopen("Kmp.txt", "r");
	int failure[max_pattern_size];
	char string[max_string_size];
	char pat[max_pattern_size];
	int r;
	//Opening file
	if (filea == NULL) {
		printf("file open error\n");
		return 1;
	}

	//Getting input
	fscanf(filea, "%s", string);
	fscanf(filea, "%s", pat);

	puts(string);
	puts(pat);

	fail(pat, failure);
	
	//PRINT RESULT
	r = pmatch(string, pat, failure);
	printf("\n%d\n", r);

	//closing file
	fclose(filea);
	return 0;
}


/* compute the pattern in failure function */
void fail(char *pat, int *failure) {
	int i, n = strlen(pat);
	failure[0] = -1;
	for (int j = 1; j < n; j++) {
		i = failure[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if (pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else failure[j] = -1;
	}
}

/* Knuth, Morris, Pratt string matching algorithm */
int pmatch(char *string, char *pat, int *failure) {
	int i = 0;
	int j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) { /*repeat until starting point is longer than the lens and matching pattern is not finished*/
		if (string[i] == pat[j]) { /*whether the string and pat array is element-wise same*/
			i++; j++;
		}
		else if(j == 0) i++; /*if the pattern matching is not started yet -i.e. even the first element is not matched*/
		else j = failure[j - 1] + 1; /*if the element is not matched, then check the pattern array based on the failure function*/
	}

	return ((j == lenp) ? (i - lenp) : -1);
}