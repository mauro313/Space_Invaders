#include "CharMatrix.h"

CharMatrix_t* charMatrix_New(int rows,int columns){
    CharMatrix_t* newOne = (CharMatrix_t*)malloc(sizeof(CharMatrix_t));
    newOne->matrix = matrix_new(rows,columns);
    return newOne;
}

void charMatrix_Delete(CharMatrix_t** cMatrix){
    free(*cMatrix);
    *cMatrix = NULL;
}

int charMatrix_getRows(CharMatrix_t* cMatrix){
    return matrix_rows(cMatrix->matrix);
}

int charMatrix_getColumns(CharMatrix_t* cMatrix){
    return matrix_columns(cMatrix->matrix);
}

bool charMatrix_set(CharMatrix_t* cMatrix,int row,int column,char value){
    char* pointer = (char*)malloc(sizeof(char));
    *pointer = value;
    return matrix_set(cMatrix->matrix,row,column,pointer);
}

char charMatrix_get(CharMatrix_t* cMatrix,int row,int columns){
    return *(char*)matrix_get(cMatrix->matrix,row,columns);
}

char charMatrix_exchange(CharMatrix_t* cMatrix,int row,int columns,char value){
    char* toExchange = matrix_get(cMatrix->matrix,row,columns);
    char toReturn = *toExchange;
    *toExchange = value;
    matrix_exchangeElement(cMatrix->matrix,row,columns,toExchange);
    return toReturn;
}

bool charMatrix_deleteElement(CharMatrix_t* cMatrix,int row,int column){
    return matrix_delete(cMatrix->matrix,row,column,free_charPointer);
}

void free_charPointer(void* pointer){
    free(pointer);
}