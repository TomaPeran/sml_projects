#include "matrix.h"


int** create_Matrix(int a, int b) {
	int** matrix = (int**)malloc(sizeof(int*) * 2);
	matrix[0] = (int*)malloc(3 * sizeof(int));
	matrix[1] = (int*)malloc(3 * sizeof(int));

	matrix[0][0] = a;
	matrix[0][1] = 1;
	matrix[0][2] = 0;

	matrix[1][0] = b;
	matrix[1][1] = 0;
	matrix[1][2] = 1;

	return matrix;
}

void execute_Shiftter(int*** matrix, int quotient, int state) {
	if (!state) {

		(*(matrix))[1][0] = (*(matrix))[1][0] - ((*(matrix))[0][0] * quotient);
		(*(matrix))[1][1] = (*(matrix))[1][1] - ((*(matrix))[0][1] * quotient);
		(*(matrix))[1][2] = (*(matrix))[1][2] - ((*(matrix))[0][2] * quotient);

		printf("%d\n", (*(matrix))[1][0]);
	}
	else {
		(*(matrix))[0][0] = (*(matrix))[0][0] - ((*(matrix))[1][0] * quotient);
		(*(matrix))[0][1] = (*(matrix))[0][1] - ((*(matrix))[1][1] * quotient);
		(*(matrix))[0][2] = (*(matrix))[0][2] - ((*(matrix))[1][2] * quotient);

	}
}


int euclids_Matrix(int a, int b) {
	int result = 0, s = 0, t = 0;
	int** matrix = create_Matrix(b, a);


	if (matrix[0][0] != matrix[1][0]) {
		while (matrix[0][0] > 0 && matrix[1][0] > 0) {
			int bigger, smaller;

			if (matrix[0][0] > matrix[1][0]) {
				bigger = matrix[0][0];
				smaller = matrix[1][0];
			}

			else {
				bigger = matrix[1][0];
				smaller = matrix[0][0];
			}


			if (smaller == matrix[0][0]) {
				execute_Shiftter(&matrix, bigger / smaller, 0); // 0 oznacava da se radi na nultom indexu
				result = matrix[0][0];
				s = matrix[0][1];
				t = matrix[0][2];
			}
			else {
				execute_Shiftter(&matrix, bigger / smaller, 1);
				result = matrix[1][0];
				t = matrix[1][1];
				s = matrix[1][2];
			}


			//printf("%d, %d\n", matrix[0][0], matrix[1][0]);
		}

	}
	else {
		result = matrix[1][0];
		s = matrix[1][1];
		t = matrix[1][2];
	}
	printf("\nM(%d, %d)\n\nResult: %d\nParameter S: %d\nParameter T: %d\n", a, b, result, s, t);

	return result;
}

int pure_Euclids_Algorithm(int a, int b) {
	int bigger = a, smaller = b;
	
	if (bigger < smaller) {
		int tmp = smaller;
		smaller = bigger;
		bigger = tmp;
	}


	if (!(a) && !(b))
		return 1;
	else if (!(smaller) || !(bigger % smaller) || bigger == smaller)
		return smaller;

	int result = pure_Euclids_Algorithm(smaller, bigger % smaller);
	return result;
}