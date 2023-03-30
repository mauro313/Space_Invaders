#ifndef TDAMATRIX_H_INCLUDED
#define TDAMATRIX_H_INCLUDED
#include <stdbool.h>

typedef struct{
 void** m;
 int rows;
 int columns;
}matrix_t;

matrix_t* matrix_new(int rows,int columns);

void matrix_free(matrix_t** mtrx);

int matrix_rows(matrix_t* mtrx);

int matrix_columns(matrix_t* mtrx);

void* matrix_get(matrix_t* mtrx,int row,int column);

bool matrix_set(matrix_t* mtrx,int row,int column,void* value);

bool matrix_delete(matrix_t* mtrx,int row,int column,void (*freeElement)(void* element));

void* matrix_exchangeElement(matrix_t* mtrx,int row,int column,void* element);

void matrix_printf(matrix_t* mtrx,void (*print)(void*));

void matrix_traverse(matrix_t* matrix, bool matrix_do(void* element,void* ctx),void* context);

#include "Matrix.c"
#endif // TDAMATRIX_H_INCLUDED
