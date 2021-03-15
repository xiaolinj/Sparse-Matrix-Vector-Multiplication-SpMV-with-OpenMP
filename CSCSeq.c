#include "CSC.h"
double* multiplication(struct CSC matrix, double* x, int column_size){
  double* result = malloc(column_size*sizeof(double));
  for(int i = 0; i < column_size; i++){
    result[i] = 0;
  }
  for(int i = 0; i < column_size; i++){
    for(int k = matrix.column_offset[i]; k < matrix.column_offset[i+1]; k++){
      result[matrix.row[k]] += matrix.value[k]*x[i];
    }
  }
  return result;
}

void printMatrix(struct CSC matrix, int valid_size){
  for(int i = 0; i < valid_size; i++)
    printf("%lf ", matrix.value[i]);
  for(int i = 0; i < valid_size; i++)
    printf("%d ", matrix.row[i]);
  for(int i = 0; i <= matrix.row_size; i++)
    printf("%d ", matrix.column_offset[i]);
}

int main(int argc, char *argv[]){
  //./spmv matrix.rft m n
  if(argc != 4){
    printf("error input!");
    exit(0);
  }
  char* filename;
  int ITERATIONS = 0;
  int NUMBER_THREADS = 0;
  filename = argv[1];
  ITERATIONS = atoi(argv[2]);
  NUMBER_THREADS = atoi(argv[3]);
  struct CSC _matrix = convertCSC(filename);
  //printMatrix(_matrix, _matrix.valid_size);

  int _column_size = _matrix.column_size;
  double* x = malloc(_matrix.column_size*sizeof(double));
  for(int i = 0; i < _column_size; i++){
    x[i] = 1;
  }

  for(int i = 1; i <= ITERATIONS; i++){
    x = multiplication(_matrix, x, _column_size);
    char outfile_name[256];
    sprintf(outfile_name, "CSC2Vec%d", i);
    FILE *fp;
    fp = fopen(outfile_name, "w");
    for(int k = 0; k < _column_size; k++)
      fprintf(fp, "%lf\n", x[k]);
    fclose(fp);
  }

}

