#ifndef CHARMATRIX_H_INCLUDED
#define CHARMATRIX_H_INCLUDED
#include "Matrix.h"

typedef struct _charMatrix{
    matrix_t* matrix;
}CharMatrix_t;

CharMatrix_t* charMatrix_New(int rows,int columns);

void charMatrix_Delete(CharMatrix_t** cMatrix);

int charMatrix_getRows(CharMatrix_t* cMatrix);

int charMatrix_getColumns(CharMatrix_t* cMatrix);

bool charMatrix_set(CharMatrix_t* cMatrix,int row,int column,char value);

char charMatrix_get(CharMatrix_t* cMatrix,int row,int columns);

char charMatrix_exchange(CharMatrix_t* cMatrix,int row,int columns,char value);

bool charMatrix_deleteElement(CharMatrix_t* cMatrix,int row,int column);

void free_charPointer(void* pointer);

#include "CharMatrix.c"
#endif //CHARMATRIX_H_INLCUDED