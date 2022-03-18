# Sparse Matrix Vector Multiplication SpMV with OpenMP
Improve the performance of sparse matrix-vector multiplication using OpenMP, in format CSR(Compressed sparse row), CSC(Compressed sparse column). \
To execute, use ```./spmv matrix.rft m n```.\
matrix.rft” is the matrix file name, m is the number of iterations, and n is the number of threads.\
Example of matrix.rft: \
5 5 4 ->(col, row, total number of elements)\
1 1 3 ->(col, row, value)\
2 2 1\
3 5 0\
4 2 4
