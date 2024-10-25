#pragma once
#ifndef MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** create_Matrix(int a, int b);

void execute_Shiftter(int*** matrix, int quotient, int state);

int euclids_Matrix(int a, int b);

int pure_Euclids_Algorithm(int a, int b);


#endif // !MATRIX_H

