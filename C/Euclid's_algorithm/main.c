#include "matrix.h"


int main() {
	int a = 3, b = 2;
	printf("M(%d, %d)\n\n", a, b);

	// timing
	int stime, etime, result;

	stime = clock();
	printf("Using matrix:    ");
	result = euclids_Matrix(a, b);
	etime = clock();
	printf("Result=%d  Time=%f\n", result, ((float)(etime - stime)) / CLOCKS_PER_SEC);


	stime = clock();
	printf("Using recursion:    ");
	result = pure_Euclids_Algorithm(a, b);
	etime = clock();
	printf("Result=%d  Time=%f\n", result, ((float)(etime - stime)) / CLOCKS_PER_SEC);

	return 0;
}