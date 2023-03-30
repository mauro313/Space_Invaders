#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"


/**
 * @brief creation of a matrix of the specified size (rows,columns)
 * 
 * @param rows 
 * @param columns 
 * @return matrix_t* 
 */
matrix_t* matrix_new(int rows,int columns){
  matrix_t* matrix = (matrix_t*)malloc(sizeof(matrix_t));
  if(matrix == NULL){
    printf("\nmemory cannot be reserved for a new matrix\n");
    exit(EXIT_FAILURE);
  }
  matrix->m =(void**)malloc((rows*columns)*sizeof(void*));
  if(matrix->m == NULL){
    free(matrix);
    matrix = NULL;
    printf("\nmemory cannot be reserved for a vector of elements\n");
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<rows;i++){
    for(int j=0;j<columns;j++){
      matrix->m[i*columns+j] = NULL;  
    }  
  }
  matrix->rows = rows;
  matrix->columns = columns;
  return matrix;
}

/**
 * @brief free the memory of a matrix.
 * 
 * @param mtrx 
 */
void matrix_free(matrix_t** mtrx){
  if(mtrx != NULL && *mtrx != NULL){
    free((*mtrx)->m);
    (*mtrx)->m = NULL;
    free(*mtrx);
    *mtrx = NULL;
  }
}

/**
 * @brief return the rows of a matrix.
 * 
 * @param mtrx 
 * @return int 
 */
int matrix_rows(matrix_t* mtrx){
  if(mtrx == NULL){
    printf("\nmatrix pointer is NULL(1)\n");
    exit(EXIT_FAILURE);  
  }
  return mtrx->rows;
}

/**
 * @brief return the columns of a matrix.
 * 
 * @param mtrx 
 * @return int 
 */
int matrix_columns(matrix_t* mtrx){
  if(mtrx == NULL){
    printf("\nmatrix pointer is NULL(2)\n");
    exit(EXIT_FAILURE);  
  }
  return mtrx->columns;
}

/**
 * @brief getter for the element in the specified position.
 * 
 * @param mtrx 
 * @param row 
 * @param column 
 * @return void* 
 */
void* matrix_get(matrix_t* mtrx,int row,int column){
  if(mtrx == NULL){
    printf("\nmatrix pointer is NULL(3)\n");
    exit(EXIT_FAILURE);
  }
  if(row<0 || row>=mtrx->rows){
    printf("\ninvalid row(1)\n");
    exit(EXIT_FAILURE);  
  }
  if(column<0 || column>=mtrx->columns){
    printf("\ninvalid column(1)\n");
    exit(EXIT_FAILURE);
  }
  return mtrx->m[row*mtrx->columns+column];
}

/**
 * @brief setter for an element in the specified position.Return true if it was added and false
 * if the position is alredy busy.
 * 
 * @param mtrx 
 * @param row 
 * @param column 
 * @param value 
 * @return true 
 * @return false 
 */
bool matrix_set(matrix_t* mtrx,int row,int column,void* value){
  if(mtrx == NULL){
    printf("\nmatrix pointer is NULL(4)\n");
    exit(EXIT_FAILURE);    
  }
  if(row<0 || row>=mtrx->rows){
    printf("\ninvalid row(2)\n");
    exit(EXIT_FAILURE);  
  }
  if(column<0 || column>=mtrx->columns){
    printf("\ninvalid column(2)\n");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(mtrx->m[row*mtrx->columns+column] == NULL){
    mtrx->m[row*mtrx->columns+column] = value;
    returned = true;
  }
  return returned;
}

/**
 * @brief delete an element from the specified position.Return true if it was deleted and false
 * if the element does not exist.
 * 
 * @param mtrx 
 * @param row 
 * @param column 
 * @param freeElement 
 * @return true 
 * @return false 
 */
bool matrix_delete(matrix_t* mtrx,int row,int column,void (*freeElement)(void* element)){
  if(mtrx == NULL){
    printf("matrix pointer is NULL(5)");
    exit(EXIT_FAILURE);    
  }   
  if(row<0 || row>=mtrx->rows){
    printf("invalid row(3)");
    exit(EXIT_FAILURE);  
  }
  if(column<0 || column>=mtrx->columns){
    printf("invalid column(3)");
    exit(EXIT_FAILURE);
  }
  bool returned = false;
  if(mtrx->m[row*mtrx->columns+column]!=NULL){
    freeElement(mtrx->m[row*mtrx->columns+column]);
    mtrx->m[row*mtrx->columns+column] = NULL;
    returned = true;    
  }
  return returned;
}

/**
 * @brief exchange the element from the specified position.Return the exchanged element.
 * 
 * @param mtrx 
 * @param row 
 * @param column 
 * @param element 
 * @return void* 
 */
void* matrix_exchangeElement(matrix_t* mtrx,int row,int column,void* element){
  if(mtrx == NULL){
    printf("matrix pointer is NULL(6)");
    exit(EXIT_FAILURE);    
  }   
  if(row<0 || row>=mtrx->rows){
    printf("invalid row(4)");
    exit(EXIT_FAILURE);  
  }
  if(column<0 || column>=mtrx->columns){
    printf("invalid column(4)");
    exit(EXIT_FAILURE);
  }
  void* returned = NULL;
  if(mtrx->m[row*mtrx->columns+column]!=NULL){
    returned = mtrx->m[row*mtrx->columns+column];
    mtrx->m[row*mtrx->columns+column] = element; 
  }
  return returned; 
}

/**
 * @brief print the matrix.
 * 
 * @param mtrx 
 * @param print 
 */
void matrix_printf(matrix_t* mtrx,void(*print)(void*)){
  if(mtrx == NULL){
    printf("\nmatrix pointer is NULL(7)\n");
    return;
  }
  for(int i=0;i<matrix_rows(mtrx);i++){
    for(int j=0;j<matrix_columns(mtrx);j++){
       print(mtrx->m[i*matrix_columns(mtrx)+j]);
       if(j == matrix_columns(mtrx)-1)
        printf("\n");
    }
  }
}

/**
 * @brief traverse the matrix using a context variable.
 * 
 * @param matrix 
 * @param matrix_do 
 * @param context 
 */
void matrix_traverse(matrix_t* matrix, bool matrix_do(void* element,void* ctx),void* context){
  if(matrix == NULL){
    printf("\nmatrix pointer is NULL(8)\n");
    return;   
  }
  int rows = 0;
  int columns = 0;
  while(rows<matrix_rows(matrix)){
    while(columns<matrix_columns(matrix) && matrix_do(matrix_get(matrix,rows,columns),context)){
      columns++; 
    }
    if(columns == matrix_columns(matrix)){
      columns = 0;  
    }
    rows++;  
  }
}




