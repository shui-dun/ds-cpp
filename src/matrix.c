#include <stdlib.h>
#include <stdio.h>
#include "matrix.h"

Matrix * mat_init(double * arr, int m, int n)
{
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	mat->data = (double *)malloc(sizeof(double)* m * n);
	for (int i = 0; i < m * n; i++)
		mat->data[i] = arr[i];
	mat->m = m;
	mat->n = n;
	return mat;
}

void mat_print(Matrix * mat)
{
	int pos = 0;
	for (int x = 0; x < mat->m; x++)
	{
		for (int y = 0; y < mat->n; y++)
			printf("%lf ", mat->data[pos++]);
		putchar('\n');
	}
}

Matrix * mat_add(Matrix * mat1, Matrix * mat2)
{
	if (mat1->m != mat2->m || mat1->n != mat2->n)
		return NULL;
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	mat->m = mat1->m;
	mat->n = mat1->n;
	mat->data = (double *)malloc(sizeof(double) * mat->m * mat->n);
	for (int i = 0; i < mat->m * mat->n; i++)
		mat->data[i] = mat1->data[i] + mat2->data[i];
	return mat;
}

Matrix * mat_subtract(Matrix * mat1, Matrix * mat2)
{
	if (mat1->m != mat2->m || mat1->n != mat2->n)
		return NULL;
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	mat->m = mat1->m;
	mat->n = mat1->n;
	mat->data = (double *)malloc(sizeof(double) * mat->m * mat->n);
	for (int i = 0; i < mat->m * mat->n; i++)
		mat->data[i] = mat1->data[i] - mat2->data[i];
	return mat;
}

Matrix * mat_transpose(Matrix * mat)
{
	if (mat->m != mat->n)
		return NULL;
	Matrix *t = (Matrix *)malloc(sizeof(Matrix));
	t->m = t->n = mat->m;
	t->data = (double *)malloc(sizeof(double) * t->m* t->n);
	for (int x = 0; x < mat->m; x++)
		for (int y = 0; y < mat->n; y++)
			mat_set(t, x, y, mat_get(mat, y, x));
	return t;
}

Matrix * mat_multiple(Matrix * mat1, Matrix * mat2)
{
	if (mat1->m != mat2->m || mat1->n != mat2->n || mat1->m != mat1->n)
		return NULL;
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	mat->n = mat->m = mat1->m;
	mat->data = (double *)calloc(mat->m * mat->n, sizeof(double));
	for (int x = 0; x < mat->m; x++)
		for (int y = 0; y < mat->n; y++)
			for (int z = 0; z < mat->n; z++)
				mat->data[x * mat->n + y] += mat_get(mat1, x, z)*mat_get(mat2, z, y);
	return mat;
}

double mat_get(Matrix * mat, int x, int y)
{
	if (x < 0 || x >= mat->m || y < 0 || y >= mat->n)
		exit(-1);
	return mat->data[x * mat->n + y];
}

int mat_set(Matrix * mat, int x, int y, double value)
{
	if (x < 0 || x >= mat->m || y < 0 || y >= mat->n)
		return 0;
	mat->data[x * mat->n + y] = value;
	return 1;
}

void mat_destroy(Matrix ** matrix)
{
	Matrix *mat = *matrix;
	if (mat->data)
	{
		free(mat->data);
		mat->data = NULL;
	}
	free(mat);
	*matrix = NULL;
}

SquMat * squ_init(double * arr, int m)
{
	SquMat *squ = (SquMat *)malloc(sizeof(SquMat));
	squ->len = m;
	int size = m * (m + 1) / 2;
	squ->data = (double *)malloc(sizeof(double) * size);
	for (int i = 0; i < size; i++)
		squ->data[i] = arr[i];
	return squ;
}

void squ_destroy(SquMat ** matrix)
{
	SquMat *mat = *matrix;
	if (mat->data)
	{
		free(mat->data);
		mat->data = NULL;
	}
	free(mat);
	*matrix = NULL;
}

SymMat * sym_cond(Matrix * mat)
{
	return ltri_cond(mat);
}

UTriMat * utri_cond(Matrix * mat)
{
	if (mat->m != mat->n)
		return NULL;
	UTriMat *tri = (UTriMat *)malloc(sizeof(UTriMat));
	tri->len = mat->m;
	int size = mat->m * (mat->m + 1) / 2;
	tri->data = (double *)malloc(sizeof(double) * size);
	int pos = 0;
	for (int x = 0; x < mat->m; x++)
		for (int y = x; y < tri->len; y++)
			tri->data[pos++] = mat_get(mat, x, y);
	return tri;
}

LTriMat * ltri_cond(Matrix * mat)
{
	if (mat->m != mat->n)
		return NULL;
	LTriMat *tri = (LTriMat *)malloc(sizeof(LTriMat));
	tri->len = mat->m;
	int size = mat->m * (mat->m + 1) / 2;
	tri->data = (double *)malloc(sizeof(double) * size);
	int pos = 0;
	for (int x = 0; x < mat->m; x++)
		for (int y = 0; y <= x; y++)
			tri->data[pos++] = mat_get(mat, x, y);
	return tri;
}

Matrix * sym_unzip(SymMat * sym)
{
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	mat->m = mat->n = sym->len;
	mat->data = (double *)malloc(sizeof(double) * sym->len * sym->len);
	for (int x = 0; x < sym->len; x++)
		for (int y = 0; y < sym->len; y++)
			mat_set(mat, x, y, sym_get(sym, x, y));
	return mat;
}

Matrix * utri_unzip(UTriMat * tri)
{
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	mat->m = mat->n = tri->len;
	mat->data = (double *)malloc(sizeof(double) * tri->len * tri->len);
	for (int x = 0; x < tri->len; x++)
		for (int y = 0; y < tri->len; y++)
			mat_set(mat, x, y, utri_get(tri, x, y));
	return mat;
}

Matrix * ltri_unzip(LTriMat * tri)
{
	Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
	mat->m = mat->n = tri->len;
	mat->data = (double *)malloc(sizeof(double) * tri->len * tri->len);
	for (int x = 0; x < tri->len; x++)
		for (int y = 0; y < tri->len; y++)
			mat_set(mat, x, y, ltri_get(tri, x, y));
	return mat;
}

void sym_print(SymMat * sym)
{
	for (int x = 0; x < sym->len; x++)
	{
		for (int y = 0; y < sym->len; y++)
			printf("%lf ", sym_get(sym, x, y));
		putchar('\n');
	}
}

void utri_print(UTriMat * tri)
{
	for (int x = 0; x < tri->len; x++)
	{
		for (int y = 0; y < tri->len; y++)
			printf("%lf ", utri_get(tri, x, y));
		putchar('\n');
	}
}

void ltri_print(LTriMat * tri)
{
	for (int x = 0; x < tri->len; x++)
	{
		for (int y = 0; y < tri->len; y++)
			printf("%lf ", ltri_get(tri, x, y));
		putchar('\n');
	}
}

double sym_get(SymMat * mat, int x, int y)
{
	if (y > x)
	{
		int temp = x;
		x = y;
		y = temp;
	}
	return mat->data[x * (x + 1) / 2 + y];
}

void sym_set(SymMat * mat, int x, int y, double value)
{
	if (y > x)
	{
		int temp = x;
		x = y;
		y = temp;
	}
	mat->data[x * (x + 1) / 2 + y] = value;
}

double utri_get(UTriMat * mat, int x, int y)
{
	if (y < x)
		return 0.0;
	return mat->data[x * mat->len - x * (x - 1) / 2 + y - x];
}

void utri_set(UTriMat * mat, int x, int y, double value)
{
	if (y >= x)
		mat->data[x * mat->len - x * (x - 1) / 2 + y - x] = value;
}

double ltri_get(LTriMat * mat, int x, int y)
{
	if (y > x)
		return 0;
	return mat->data[x * (x + 1) / 2 + y];
}

void ltri_set(LTriMat * mat, int x, int y, double value)
{
	if (y <= x)
		mat->data[x * (x + 1) / 2 + y] = value;
}

SparseMat * sparse_init(int m, int n, int num, double * arr)
{
	SparseMat *sparse = (SparseMat *)malloc(sizeof(SparseMat));
	sparse->m = m;
	sparse->n = n;
	sparse->num = num;
	sparse->x = (int *)malloc(sizeof(int) * num);
	sparse->y = (int *)malloc(sizeof(int) * num);
	sparse->data = (double *)malloc(sizeof(double) * num);
	for (int i = 0; i < num; i++)
	{
		sparse->x[i] = (int)arr[3 * i];
		sparse->y[i] = (int)arr[3 * i + 1];
		sparse->data[i] = arr[3 * i + 2];
	}
	return sparse;
}

void sparse_print(SparseMat * sparse)
{
	if (!sparse) return;
	int pos = 0;
	for (int x = 0; x < sparse->m; x++)
	{
		for (int y = 0; y < sparse->n; y++)
			if (pos < sparse->num && sparse->x[pos] == x && sparse->y[pos] == y)
				printf("%lf\t", sparse->data[pos++]);
			else
				printf("%lf\t", 0.0);
		putchar('\n');
	}
}

SparseMat * sparse_trans(SparseMat * mat)
{
	if (mat->m != mat->n)
		return NULL;
	SparseMat *t = (SparseMat *)malloc(sizeof(SparseMat));
	t->m = t->n = mat->m;
	t->num = mat->num;
	t->x = (int *)malloc(sizeof(int)*t->num);
	t->y = (int *)malloc(sizeof(int)*t->num);
	t->data = (double *)malloc(sizeof(double) * t->num);
	int *count = (int *)calloc(t->m, sizeof(int));
	for (int i = 0; i < t->num; i++)
		count[mat->y[i]]++;
	int *pot = (int *)calloc(t->m, sizeof(int));
	for (int i = 1; i < t->m; i++)
		pot[i] = pot[i - 1] + count[i - 1];
	for (int i = 0; i < t->num; i++)
	{
		int pos = pot[mat->y[i]];
		t->data[pos] = mat->data[i];
		t->x[pos] = mat->y[i];
		t->y[pos] = mat->x[i];
		pot[mat->y[i]]++;
	}
	free(count);
	free(pot);
	return t;
}
