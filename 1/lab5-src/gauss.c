#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DEBUG_ON 1
#define EPSILON 1E-6
#define MAXROWS 100
#define MAXCOLS 101

void printMatrix(int rows, int columns, double matrix[][MAXCOLS]);
double elements[MAXROWS][MAXCOLS];
/* Add htelper functions and global variables here */

int main(int argc, char ** argv)
{
	/* Add your implementation here */
	int rowS = 0;

	scanf("%d", &rowS);
	if(rowS == 0 || rowS > 100){
		printf("Expected N (number of equations)\n");
		exit(1);
	}

	int i;
	int j;
	int colS = rowS + 1;
	for (i = 0; i < rowS; i++){
		for(j = 0; j < colS; j++){
			if(scanf("%lf", &elements[i][j]) != EOF){
				continue;
			}
			else{
				printf("Element a[%d][%d] is missing\n",i,j);
				exit(1);
			}
		}
	}
	printf("initial matrix\n");
	printMatrix(rowS, colS, elements);


	int step1;
	for(step1 = 0; step1 < rowS;step1++){
		int step = step1;
		int maxrow = step1;
		double change = fabs(elements[step1][step1]);
		for(;step < rowS; step++){
			if(fabs(elements[step][step1]) > change){
				maxrow = step;
				change = fabs(elements[step][step1]);
			}
		}
		
		if(elements[maxrow][step1] == 0) {
			printf("Error: Matrix is singular\n");
			exit(1);
		}
	
		int step2;
		if(maxrow >= step1){
			int count = colS;
			for(step2 = 0; step2 < colS; step2++){
				double save = elements[step1][step2];
				elements[step1][step2] = elements[maxrow][step2];
				elements[maxrow][step2] = save;
			}
		}
		printf("swapped %d and %d\n",step1,maxrow);
		printMatrix(rowS,colS,elements);

		int step3;
		double save2 = elements[step1][step1];
		for(step3 = step1; step3 < colS; step3++){
			elements[step1][step3] = (elements[step1][step3])/save2;
		}
		printf("row %d /= %lf\n",step1,save2);
		printMatrix(rowS,colS,elements);
	
		int compare = 0;
		while(compare < rowS){
			if(compare == step1){
				++compare;
				continue;
			}
			int compare2;
			double save3 = elements[compare][step1];
			for(compare2 = 0; compare2 < colS; compare2++){
				elements[compare][compare2] =
					elements[compare][compare2] - save3*elements[step1][compare2];
			}
			printf("row %d -= %lf row %d\n", compare, save3, step1);
			printMatrix(rowS, colS,elements);
			compare++;
		}
	
	}
	int step4 = 0;
	for(; step4 < rowS; step4 ++){
		printf("%lf ", elements[step4][colS - 1]);
	}
	printf("\n");
	return 0;
}

void printMatrix(int rows, int columns, double matrix[][MAXCOLS])
{
	/* Add your implementation here */
	int n;
	printf("MATRIX:\n");
	for(n = 0; n < rows; n++){
		int m;
		for(m = 0; m < columns;m++){
			printf("%lf ",matrix[n][m]);
		}
		printf("\n");
	}
	printf("\n");
}
