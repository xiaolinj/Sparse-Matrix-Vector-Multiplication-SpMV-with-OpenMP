#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CSC
{
  int column_size;
  int row_size;
  int valid_size;
  double* value;
  int* row;
  int* column_offset;
}CSC;

struct CSC convertCSC(char* filename)
{

  FILE *fp = fopen(filename, "r");
  if (fp == NULL){
    printf("bad input file");
    exit(0);
  }
  char line[1024];
  int line_number = 0;
  struct CSC matrix;
  if (fgets(line, sizeof(line), fp)) {
    if(line_number == 0){
      sscanf(line, "%d %d %d", &matrix.row_size, &matrix.column_size, &matrix.valid_size);
      line_number++;
    }
  }

  double* temp_matrix[matrix.row_size];
  for(int i = 0; i < matrix.row_size; i++){
    temp_matrix[i] = (double*)malloc(matrix.column_size*sizeof(double));
  }
  matrix.value = malloc(matrix.valid_size*sizeof(double));
  matrix.row = malloc(matrix.valid_size*sizeof(int));
  matrix.column_offset = malloc((matrix.column_size+1)*sizeof(int));
  int i=0,j=0,prev=-1,row_index=0;
  double value=0.0;
  int offset = 0;
  while(fgets(line, sizeof(line), fp) && line_number < matrix.valid_size+1) {
    sscanf(line, "%d %d %lf", &i, &j, &value);
    temp_matrix[i][j] = value;    
  }

  int k = 0;
  for(int j = 0; j < matrix.column_size; j++){
    matrix.column_offset[j] = offset;
    for(int i = 0; i < matrix.row_size; i++){
      if(temp_matrix[i][j] != 0){
        matrix.value[k] = temp_matrix[i][j];
        matrix.row[k] = i;
        k++;
        offset++;
      }
    }
  }

  matrix.column_offset[matrix.column_size] = matrix.valid_size;
  fclose(fp);
  return matrix;
} 
