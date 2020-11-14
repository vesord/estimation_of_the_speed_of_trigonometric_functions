#ifndef ESTIMATION_H
# define ESTIMATION_H

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

void test_sin_double(double *angle_table, size_t size);
void test_sin_float(float *angle_table, size_t size);
void test_sin_table(double *sin_table, size_t *angle_table, size_t angle_table_size);

void	rand_fill_angle_table(double *table_d, float *table_f,
							  size_t* table_t, size_t table_t_size, size_t size);

void	fill_sin_table(double *table, size_t size);

#endif //ESTIMATION_H
