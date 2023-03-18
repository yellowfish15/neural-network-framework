#include <vector>

// header file for utilities library
#ifndef UTILITIES_H
#define UTILITIES_H

// Matrix class (parent of ColumnVector)
#ifndef MATRIX_H
#define MATRIX_H
class Matrix {
    public:
        double ** matrix;
        int rows, cols;
        Matrix(int rows, int cols);
        Matrix(int rows, int cols, double ** values);
        void randomize();
        void set(const std::vector<std::vector<double>>& v);
        void destruct();
};
#endif

// Column Vector class (child of Matrix)
#ifndef COLUMN_VECTOR_H
#define COLUMN_VECTOR_H
class ColumnVector: public Matrix {
    public:
        ColumnVector(int rows);
        ColumnVector(int rows, double * values);
        // set column vector given array of doubles
        void set(const std::vector<double>& v);
        // vector_i = t_i - vector_i
        void calculateError(double * t);
};
#endif

// Global Functions
void add(const Matrix& A, Matrix& B);
void subtract(const Matrix& A, const Matrix& B, Matrix & y);
void multiply(const Matrix& A, Matrix& B);
void multiply(const Matrix& A, const Matrix& B, Matrix& y);
void sigmoid(Matrix& x);
void dsigmoid(Matrix& x);

#endif