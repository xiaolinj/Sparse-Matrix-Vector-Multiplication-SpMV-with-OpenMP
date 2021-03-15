#include "CSR.h"
#include <omp.h>
double* multiplication(struct CSR matrix, double* x, int row_size, int thread_number){
  double start, end;
  int i=0,k=0;
  double* result = malloc(row_size*sizeof(double));
  for(i = 0; i < row_size; i++){
    result[i] = 0;
  }
  omp_set_dynamic(0);
  omp_set_num_threads(thread_number);
  start = omp_get_wtime();
  #pragma omp parallel for private(i,k) shared(matrix)
    for(i = 0; i < row_size; i++){
      for(k = matrix.row_offset[i]; k < matrix.row_offset[i+1]; k++){
        result[i] += matrix.value[k]*x[matrix.column[k]];
      }
    }
  
  end = omp_get_wtime();
  printf("Time of computation: %f seconds\n", (end-start)/10);
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
    x = multiplication(_matrix, x, _row_size, NUMBER_THREADS);
    char outfile_name[256];
    sprintf(outfile_name, "CSRVecopenmp%d", i);
    FILE *fp;
    fp = fopen(outfile_name, "w");
    for(int k = 0; k < _row_size; k++)
      fprintf(fp, "%lf\n", x[k]);
    fclose(fp);
  }
}

