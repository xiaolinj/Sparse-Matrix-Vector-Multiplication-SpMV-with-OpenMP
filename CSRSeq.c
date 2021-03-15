#include "CSR.h"
double* multiplication(struct CSR matrix, double* x, int column_size){
    double* result = malloc(column_size*sizeof(double));
    for(int i = 0; i < column_size; i++){
        for(int k = matrix.row_offset[i]; k < matrix.row_offset[i+1]; k++){
            result[i] += matrix.value[k]*x[matrix.column[k]];
        }
    }
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
    int _column_size = _matrix.column_size;
    double* x = malloc(_matrix.column_size*sizeof(double));
    for(int i = 0; i < _column_size; i++){
        x[i] = 1;
    }

    for(int i = 1; i <= ITERATIONS; i++){
        x = multiplication(_matrix, x, _column_size);
        char outfile_name[256];
        sprintf(outfile_name, "CSR2Vec%d", i);
        FILE *fp;
        fp = fopen(outfile_name, "w");
        for(int k = 0; k < _column_size; k++)
            fprintf(fp, "%lf\n", x[k]);
        fclose(fp);
    }
    //printf("%d %lf %d\n", _matrix.column[_matrix.matrix_valid-1], _matrix.value[_matrix.matrix_valid-1], _matrix.row_offset[_matrix.matrix_column-1]);
}

