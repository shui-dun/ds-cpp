#pragma once

typedef struct {
	double *data;
	int m;
	int n;
}Matrix;

typedef struct {
	double *data;
	int len;
}SquMat, SymMat, UTriMat, LTriMat;

Matrix *mat_init(double *arr, int m, int n);

void mat_print(Matrix *mat);

Matrix *mat_add(Matrix *mat1, Matrix *mat2);

Matrix *mat_subtract(Matrix *mat1, Matrix *mat2);

Matrix *mat_transpose(Matrix *mat);

Matrix *mat_multiple(Matrix *mat1, Matrix *mat2);

double mat_get(Matrix *mat, int x, int y);

int mat_set(Matrix *mat, int x, int y, double value);

void mat_destroy(Matrix **mat);

SquMat *squ_init(double *arr, int m);

void squ_destroy(SquMat ** matrix);

SymMat *sym_cond(Matrix *mat);

UTriMat *utri_cond(Matrix *mat);

LTriMat *ltri_cond(Matrix *mat);

Matrix *sym_unzip(SymMat *sym);

Matrix *utri_unzip(UTriMat *tri);

Matrix *ltri_unzip(LTriMat *tri);

void sym_print(SymMat *sym);

void utri_print(UTriMat *tri);

void ltri_print(LTriMat *tri);

double sym_get(SymMat *mat, int x, int y);

void sym_set(SymMat *mat, int x, int y, double value);

double utri_get(UTriMat *mat, int x, int y);

void utri_set(UTriMat *mat, int x, int y, double value);

double ltri_get(LTriMat *mat, int x, int y);

void ltri_set(LTriMat *mat, int x, int y, double value);

typedef struct {
	int m;
	int n;
	int num;
	int *x;
	int *y;
	double *data;
}SparseMat;

SparseMat *sparse_init(int m, int n, int num, double *arr);

void sparse_print(SparseMat *sparse);

SparseMat *sparse_trans(SparseMat *mat);