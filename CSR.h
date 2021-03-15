#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct CSR
{
  int column_size;
  int row_size;
  int valid_size;
  double* value;
  int* column;
  int* row_offset;
}CSR;

struct CSR convertCSR(char* filename)
{

  FILE *fp = fopen(filename, "r");
  if (fp == NULL){
    printf("bad input file");
    exit(0);
  }
  char line[1024];
  int line_number = 0;
  struct CSR matrix;
  if (fgets(line, sizeof(line), fp)) {
    if(line_number == 0){
      sscanf(line, "%d %d %d", &matrix.row_size, &matrix.column_size, &matrix.valid_size);
      line_number++;
    }
  }
  matrix.value = malloc(matrix.valid_size*sizeof(double));
  matrix.column = malloc(matrix.valid_size*sizeof(int));
  matrix.row_offset = malloc((matrix.row_size+1)*sizeof(int));
  int i=0,j=0,prev=-1,row_index=0;
  double value=0.0;
  int offset = 0;
  while(fgets(line, sizeof(line), fp) && line_number < matrix.valid_size+1) {
    sscanf(line, "%d %d %lf", &i, &j, &value);
    if(i > prev){
      offset = line_number-1;
      matrix.row_offset[row_index] = offset;
      row_index++;
      prev = i;
    }
    matrix.column[line_number-1] = j;
    matrix.value[line_number-1] = value;
    line_number++;
  }
  matrix.row_offset[matrix.row_size] = matrix.valid_size;
  fclose(fp);
  return matrix;
} 
