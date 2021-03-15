#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
  int row;
  double value;
  struct Node* next;
}Node;

struct CSC
{
  int column_size;
  int row_size;
  int valid_size;
  double* value;
  int* row;
  int* column_offset;
}CSC;

void printMatrix(struct CSC matrix, int valid_size){
  for(int i = 0; i < valid_size; i++)
    printf("%lf ", matrix.value[i]);
  for(int i = 0; i < valid_size; i++)
    printf("%d ", matrix.row[i]);
  for(int i = 0; i <= matrix.row_size; i++)
    printf("%d ", matrix.column_offset[i]);
}

struct CSC LinkedCSC(char* filename){
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
  matrix.value = malloc(matrix.valid_size*sizeof(double));
  matrix.row = malloc(matrix.valid_size*sizeof(int));
  matrix.column_offset = malloc((matrix.column_size+1)*sizeof(int));

  Node** temp_matrix = (Node**)malloc(matrix.row_size*sizeof(Node*));
  Node** dummy_head = (Node**)malloc(matrix.row_size*sizeof(Node*));

  for(int init = 0; init < matrix.row_size; init++){
    temp_matrix[init] = (Node*)malloc(matrix.row_size*sizeof(Node));
    dummy_head[init] = (Node*)malloc(matrix.row_size*sizeof(Node));
    dummy_head[init] = temp_matrix[init];
  }
  int i=0,j=0,prev=-1,row_index=0;
  double value=0.0;
  int offset = 0;
  while(fgets(line, sizeof(line), fp) && line_number < matrix.valid_size+1) {
    sscanf(line, "%d %d %lf", &i, &j, &value);
    Node* cur_node = malloc(sizeof(Node));
    cur_node->row = i-1;
    cur_node->value = value;
    cur_node->next = NULL;
    temp_matrix[j-1]->next = cur_node;
    temp_matrix[j-1] = cur_node;
    
    line_number++;
  }

  int valid_k = 0;
  for(int init = 0; init < matrix.row_size; init++){
    temp_matrix[init] = dummy_head[init]->next;
    matrix.column_offset[init] = offset;
    while(temp_matrix[init] != NULL){
      matrix.value[valid_k] = temp_matrix[init]->value;
      matrix.row[valid_k] = temp_matrix[init]->row;
      temp_matrix[init] = temp_matrix[init]->next;
      offset++;
      valid_k++;
    }
    free(temp_matrix[init]);
    free(dummy_head[init]);
  }
  matrix.column_offset[matrix.row_size] = matrix.valid_size;
  fclose(fp);
  return matrix;
}


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

  double** temp_matrix = (double**)malloc(sizeof(double*)*matrix.column_size);
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
