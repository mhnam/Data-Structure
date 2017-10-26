#include<stdio.h>
#include<stdlib.h>

typedef struct {
	float coef;
	int expon;
}polynomial;

//void readpoly;
//void printpoly;
//void padd(polynomial a[], polynomial b[], polynomial c[], int size_a, int size_b);

int main() {
	FILE *filea = fopen("A.txt", "r");
	FILE *fileb = fopen("B.txt", "r");
	
	polynomial a[100], b[100], c[100];
	int res_a, res_b;
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int m = 0;
	float temp1;
	int temp2, size_a, size_b;

	//opening file
	if (filea == NULL) {
		printf("file open error\n");
		return 1;
	}

	if (fileb == NULL) {
		printf("file open error\n");
		return 1;
	}

	//reading file
	while (1) {
		res_a = fscanf(filea, "%f %d", &temp1, &temp2);
		a[i].coef = temp1;
		a[i].expon = temp2;
		i++;
		if (res_a == EOF) break;
	}

	while (1) {
		res_b = fscanf(fileb, "%f %d", &temp1, &temp2);
		b[j].coef = temp1;
		b[j].expon = temp2;
		j++;
		if (res_b == EOF) break;
	}
	
	size_a = i - 1;
	size_b = j - 1;

	//checking input
	printf("INPUT DATA\n");
	printf("A.txt\nsize: %d\n", size_a);
	for (int x = 0; x < size_a; x++)
		printf("%.0f %d\n", a[x].coef, a[x].expon);
	printf("\n");
	
	printf("B.txt\nsize: %d\n", size_b);
	for (int y = 0; y < size_b; y++)
		printf("%.0f %d\n", b[y].coef, b[y].expon);

	//calculating result
	while ((l < size_a) && (m < size_b)) {
		if (a[l].expon>b[m].expon) {
			c[k].coef = a[l].coef;
			c[k].expon = a[l].expon;
			l++; k++;
			}
		else if (a[l].expon<b[m].expon) {
			c[k].coef = b[m].coef;
			c[k].expon = b[m].expon;
			m++; k++;
		}
		else {
			if (a[l].coef + b[m].coef == 0) {
				l++; m++; continue;
			}
			c[k].coef = a[l].coef + b[m].coef;
			c[k].expon = a[l].expon;
			l++; m++; k++;
		}
	}
	
	if (l>=size_a) {
		while (1) {
			c[k].coef = b[m].coef;
			c[k].expon = b[m].expon;
			k++; m++;
			if (m > size_b-1) break;
		}
	}
	else {
		while (1) {
			c[k].coef = a[l].coef;
			c[k].expon = a[l].expon;
			k++; l++;
			if (l == size_a-1) break;
		}
	}
	
	//print result
	printf("\n\nOUTPUT DATA\n");
	for (int z = 0; z < k; z++)
		printf("%.0f %d\n", c[z].coef, c[z].expon);
	printf("\n");

	//closing file
	fclose(filea);
	fclose(fileb);

	///*if (fclose_state == NULL) {
	//printf("file close error\n");
	//return 1;
	//}*/

	//system("PAUSE");
	return 0;
}

//
//void readpoly{
//
//}
//
//void printpoly{
//
//}
//
//void padd(polynomial* a, polynomial* b, polynomial* c, int size_a, int size_b) {
//	int k = 0, l = 0, m = 0;
//
//	while ((l <= size_a) && (m <= size_b)) {
//		if (a[l].expon>b[m].expon) {
//			c[k].coef = a[l].coef;
//			c[k].expon = a[l].coef;
//			l++; k++;
//		}
//		else if (a[l].expon<b[m].expon) {
//			c[k].coef = b[m].coef;
//			c[k].expon = b[m].coef;
//			m++; k++;
//		}
//		else {
//			if (a[l].coef + b[m].coef == 0) {
//				l++; m++; k++; continue;
//			}
//
//			c[k].coef = a[l].coef + b[m].coef;
//			c[k].expon = a[l].expon;
//			l++; m++; k++;
//		}
//	}
//
//	if (l<i) {
//		while (1) {
//			c[k].coef = b[m].coef;
//			c[k].expon = b[m].coef;
//			k++; m++;
//			if (m = size_b + 1) break;
//		}
//	}
//	else {
//		while (1) {
//			c[k].coef = a[l].coef;
//			c[k].expon = a[l].coef;
//			k++; l++;
//			if (l = size_a + 1) break;
//		}
//	}
//
//}
