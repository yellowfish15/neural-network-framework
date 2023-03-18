#include <cmath>
#include <random>
#include <vector>
#include "utilities.hpp"

// random number generator to generate numbers [-1.0, 1.0]
std::mt19937 gen(1729);
std::uniform_real_distribution<float> distribution(-1.0,1.0);

/*
    Matrix class implementation
    (Child of ColumnVector class)
*/
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols) {
    matrix = (double**)malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++)
        matrix[i] = (double*)malloc(cols * sizeof(double));
}

// constructor for preset values
Matrix::Matrix(int rows, int cols, double ** values) : Matrix(rows, cols) {
    for (int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++)
            matrix[i][j] = values[i][j];
    }
}

// randomize the weights in the matrix
void Matrix::randomize() {
    for(int i = 0; i < rows; i++)
        for(int j = 0; j < cols; j++) 
            matrix[i][j] = distribution(gen);
}

// set the values of the matrix
void Matrix::set(const std::vector<std::vector<double>>& v) {
    for(int i = 0; i < rows; i++) 
        for(int j = 0; j < cols; j++)
            matrix[i][j] = v[i][j];
}

// free malloc memory when finished
void Matrix::destruct() {
    for(int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}


/*
    ColumnVector class implementation:
    (Child of Matrix class)
*/
ColumnVector::ColumnVector(int rows) : Matrix(rows, 1) {}

ColumnVector::ColumnVector(int rows, double * values) : Matrix(rows, 1) {
    for(int i = 0; i < rows; i++)
        matrix[i][0] = values[i];
}

// set column vector given array of doubles
void ColumnVector::set(const std::vector<double>& v) {
    for(int i = 0; i < rows; i++)
        matrix[i][0] = v[i];
}

// vector_i = t_i - vector_i
void ColumnVector::calculateError(double * t) {
        for(int i = 0; i < rows; i++)
        matrix[i][0] = t[i] - matrix[i][0];
}


/*
    Global Functions
*/
// perform A+B (both are the same dimensions), result stored in B
void add(const Matrix& A, Matrix& B) {
    if(A.rows != B.rows || A.cols != B.cols)
        return;

    for(int r = 0; r < A.rows; r++)
        for(int c = 0; c < A.cols; c++)
            B.matrix[r][c] += A.matrix[r][c];
}

// perform A-B = y, result stored in y
void subtract(const Matrix& A, const Matrix& B, Matrix & y) {
    if(A.rows != B.rows || A.cols != B.cols)
        return;
    for(int r = 0; r < A.rows; r++)
        for(int c = 0; c < A.cols; c++)
            y.matrix[r][c] = A.matrix[r][c] - B.matrix[r][c];
}

// element-wise multiplication A*B, result stored in B
void multiply(const Matrix& A, Matrix& B) {
    if(A.rows != B.rows || A.cols != B.cols)
        return;
    for(int r = 0; r < A.rows; r++)
        for(int c = 0; c < A.cols; c++)
            B.matrix[r][c] = A.matrix[r][c] * B.matrix[r][c];

}

 // perform A*B = y, result stored in y
void multiply(const Matrix& A, const Matrix& B, Matrix& y) {
     // check dimensionality
    if(A.cols != B.rows || y.rows != A.rows || y.cols != B.cols)
        return;
    for(int i = 0; i < A.rows; i++) {
        for(int j = 0; j < B.cols; j++) {
            double sum = 0;
            for(int k = 0; k < A.cols; k++)
                sum += A.matrix[i][k] * B.matrix[k][j];
            y.matrix[i][j] = sum;
        }
    }
}

// pass all cells in x through sigmoid(x)
void sigmoid(Matrix& x) {
    for(int i = 0; i < x.rows; i++) 
        for(int j = 0; j < x.cols; j++)
            x.matrix[i][j] = 1/(1+exp(-x.matrix[i][j]));
}

// pass all cells in x through d(sigmoid)/dx
void dsigmoid(Matrix& x) {
    for(int i = 0; i < x.rows; i++) 
        for(int j = 0; j < x.cols; j++)
            x.matrix[i][j] *= (1-x.matrix[i][j]);
}