#include "estimation.h"

#define SIN_TABLE_SIZE 20000
#define ANGLES_TABLE_SIZE 2000000
#define TESTS_COUNT 20

int main()
{
	double	*sin_table = (double*)malloc(sizeof(double) * SIN_TABLE_SIZE);
	double	*angle_table_d = (double*)malloc(sizeof(double) * ANGLES_TABLE_SIZE);
	float	*angle_table_f = (float*)malloc(sizeof(float) * ANGLES_TABLE_SIZE);
	size_t	*angle_table_t = (size_t*)malloc(sizeof(size_t) * ANGLES_TABLE_SIZE);

	srand(1);

	fill_sin_table(sin_table, SIN_TABLE_SIZE);
	rand_fill_angle_table(angle_table_d, angle_table_f,
						  angle_table_t, SIN_TABLE_SIZE, ANGLES_TABLE_SIZE);

	printf("Test info:\nTest table size: %d\n", ANGLES_TABLE_SIZE);
	printf("Sin table size:  %d\n\n", SIN_TABLE_SIZE);
	printf("%10s%10s%10s\n", "double", "float", "table");
	for (int i = 0; i < TESTS_COUNT; ++i)
	{
		test_sin_double(angle_table_d, ANGLES_TABLE_SIZE);
		test_sin_float(angle_table_f, ANGLES_TABLE_SIZE);
		test_sin_table(sin_table, angle_table_t, ANGLES_TABLE_SIZE);
		printf("\n");
	}
}

void	fill_sin_table(double *table, size_t size)
{
	double angle_cur = 0.;
	double angle_stp = 2. * M_PI / size;

	for (size_t i = 0; i < size; ++i)
	{
		table[i] = sin(angle_cur);
		angle_cur += angle_stp;
	}
}

void	rand_fill_angle_table(double *table_d, float *table_f,
							  size_t* table_t, size_t table_t_size, size_t size)
{
	double	angle_steps;
	double	angle_step = 2. * M_PI / table_t_size;
	int		divisor;

	for (size_t i = 0; i < size; ++i)
	{
		divisor = rand();
		divisor = divisor == 0 ? 1 : divisor;
		table_d[i] = (double)rand() / (double)divisor;
		table_f[i] = (float)table_d[i];
		modf(table_d[i] / angle_step, &angle_steps);
		table_t[i] = (int)angle_steps % table_t_size;
	}
}

void test_sin_double(double *angle_table, size_t size)
{
	clock_t start, stop;
	double tmp = 0;

	start = clock();
	for (size_t i = 0; i < size ; ++i)
	{
		tmp += sin(angle_table[i]);
	}
	stop = clock();
	printf("%10f", (double)(stop - start) / (double)(CLOCKS_PER_SEC));
}

void test_sin_float(float *angle_table, size_t size)
{
	clock_t start, stop;
	float tmp = 0;

	start = clock();
	for (size_t i = 0; i < size ; ++i)
	{
		tmp += sinf(angle_table[i]);
	}
	stop = clock();
	printf("%10f", (double)(stop - start) / (double)(CLOCKS_PER_SEC));
}

void test_sin_table(double *sin_table,
					size_t *angle_table, size_t angle_table_size)
{
	clock_t start, stop;
	double tmp = 0;

	start = clock();
	for (size_t i = 0; i < angle_table_size ; ++i)
	{
		tmp += sin_table[angle_table[i]];
	}
	stop = clock();
	printf("%10f", (double)(stop - start) / (double)(CLOCKS_PER_SEC));
}
