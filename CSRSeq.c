#include "CSR.h"
#include <sys/time.h>
double* multiplication(struct CSR matrix, double* x, int row_size){
  double* result = malloc(row_size*sizeof(double));
  for(int i = 0; i < row_size; i++){
    result[i] = 0;
  }
  struct timeval start, end;
  gettimeofday(&start, NULL); 
  for(int i = 0; i < row_size; i++){
    for(int k = matrix.row_offset[i]; k < matrix.row_offset[i+1]; k++){
      result[i] += matrix.value[k]*x[matrix.column[k]];
    }
  }
  gettimeofday(&end, NULL);
  printf("Time of computation: %lf microseconds\n", end.tv_sec-start.tv_sec + (end.tv_usec-start.tv_usec)/1000000.0);
  return result;
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
  struct CSR _matrix = convertCSR(filename);
  //printMatrix(_matrix, _matrix.valid_size);
  int _row_size = _matrix.row_size;
  double* x = malloc(_matrix.row_size*sizeof(double));
  for(int i = 0; i < _row_size; i++){
    x[i] = 1;
  }

  for(int i = 1; i <= ITERATIONS; i++){
    x = multiplication(_matrix, x, _row_size);
    char outfile_name[256];
    sprintf(outfile_name, "CSRVecseq%d", i);
    FILE *fp;
    fp = fopen(outfile_name, "w");
    for(int k = 0; k < _row_size; k++)
      fprintf(fp, "%lf\n", x[k]);
    fclose(fp);
  }
}

