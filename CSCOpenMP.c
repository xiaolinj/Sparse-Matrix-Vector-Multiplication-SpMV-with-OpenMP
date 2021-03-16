#include "CSC.h"
#include <omp.h>


double* multiplication(struct CSC matrix, double* x, int column_size, int thread_number){
  double start, end;
  double* result = malloc(column_size*sizeof(double));
  int i=0, k=0;
  double multiplier = 0;
  for(int i = 0; i < column_size; i++){
    result[i] = 0;
  }
  omp_set_dynamic(0);
  omp_set_num_threads(thread_number);
  start = omp_get_wtime();
  
  
  for(i = 0; i < column_size; i++){
    multiplier = x[i];
    #pragma omp parallel for private(k) shared(matrix)
    for(k = matrix.column_offset[i]; k < matrix.column_offset[i+1]; k++){
      result[matrix.row[k]] += matrix.value[k]*multiplier;
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

  struct CSC _matrix = LinkedCSC(filename);

  int _column_size = _matrix.column_size;
  double* x = malloc(_matrix.column_size*sizeof(double));
  for(int i = 0; i < _column_size; i++){
    x[i] = 1;
  }

  for(int i = 1; i <= ITERATIONS; i++){
    x = multiplication(_matrix, x, _column_size, NUMBER_THREADS);
    char outfile_name[256];
    sprintf(outfile_name, "CSCOpenMPVec%d.txt", i);
    FILE *fp;
    fp = fopen(outfile_name, "w");
    for(int k = 0; k < _column_size; k++)
      fprintf(fp, "%lf\n", x[k]);
    fclose(fp);
  }

}

