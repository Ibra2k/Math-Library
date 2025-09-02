//
// Created by ibrahim on 8/31/25.
//

#ifndef MATH_LIBRARY_MAIN_H
#define MATH_LIBRARY_MAIN_H
#include <vector>
#include <iostream>
#include <cmath>

class Matrix {
    int m,n;
    std::vector<std::vector<int>> two_d;
public:

    // Accessor Functions
    std::vector<std::vector<int>> &matrix() { return two_d;}
    const std::vector<std::vector<int>> &matrix() const { return two_d;}
    const int getRows() { return m; }
    const int getColumns() { return n; }
    bool isSquare() const { return m==n; }


    Matrix(const int &rows, const int &columns, const int &fill_value=0):
        m(rows), n(columns), two_d(rows, std::vector<int>(columns, fill_value)){}

    Matrix(const std::vector<std::vector<int>> &values):
        m(values.size()), n(values[0].size()), two_d(values) {}
    // Core Functions

    inline void setValues(const std::vector<std::vector<int>> &user_matrix);
    Matrix getTranspose();
    int getDeterminant(const std::vector<std::vector<int>> &matrix);
    std::vector<std::vector<int>> getMinor(const std::vector<std::vector<int>> &matrix, int excludeRow, int excludeColumn);

    //Operation Overloaders
    Matrix operator+(const Matrix &obj) const;
    Matrix operator-(const Matrix &obj) const;
    Matrix operator*(const int &x) const; // Scalar Multiplication
    Matrix operator*(Matrix &obj); // Matrix Multiplication

    friend std::ostream& operator<<(std::ostream &stream, const Matrix &obj);
};

// Class functions

void Matrix::setValues(const std::vector<std::vector<int>> &user_matrix) {
    if (user_matrix.size() != getRows() || user_matrix[0].size() != getColumns()) {
        throw std::runtime_error("Dimension mismatch in setValues()");
    }
    matrix() = user_matrix;
}

inline Matrix Matrix::getTranspose() {
    Matrix transpose(getColumns(), getRows());

    for (int i=0; i<getRows(); i++) {
        for (int j=0; j<getColumns(); j++) {
            transpose.matrix()[j][i] = matrix()[i][j];
        }
    }
    return transpose;
}

inline std::vector<std::vector<int> > Matrix::getMinor(const std::vector<std::vector<int>> &matrix, int excludeRow, int excludeColumn) {

    std::vector<std::vector<int>> minorMatrix(matrix.size()-1, std::vector<int>(matrix.size()-1, 0));

    int mi =0;
    for (int i=0; i<matrix.size(); i++) {
        if (i==excludeRow) continue;
        int mj =0;
        for (int j=0; j<matrix.size(); j++) {
            if (j==excludeColumn) continue;
            minorMatrix[mi][mj] = matrix[i][j];
            mj++;
        }
        mi++;
    }
    return minorMatrix;
}

inline int Matrix::getDeterminant(const std::vector<std::vector<int>> &matrix) {
    int size = matrix.size();
    int deter_result=0;
    if (size == 1) return (matrix[0][0]);
    if (size == 2) return (matrix[0][0] * matrix[1][1]) - ( matrix[0][1] * matrix[1][0] );

    for (int j=0; j<size; j++) {
        std::vector<std::vector<int>> minorMatrix = getMinor(matrix, 0, j);
        deter_result += ( j%2 == 0 ? 1 : -1 ) * matrix[0][j] * getDeterminant(minorMatrix);
    }
    return deter_result;
}




// Operator overloading
inline std::ostream& operator<<(std::ostream &stream, const Matrix &obj) {
    for (const auto &row: obj.matrix()) {
        for (const int &element: row) {
            stream << element << " ";
        }
        stream << '\n';
    }
    return stream;
}

Matrix Matrix::operator+(const Matrix &obj) const {
    if (m != obj.m || n != obj.n) throw std::runtime_error("Dimension mistach");
    Matrix result(m, n);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            result.matrix()[i][j] = matrix()[i][j]+obj.matrix()[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &obj) const {
    if (m != obj.m || n != obj.n) throw std::runtime_error("Dimension mistach");
    Matrix result(m, n);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            result.matrix()[i][j] = matrix()[i][j]-obj.matrix()[i][j];
        }
    }
    return result;
}


Matrix Matrix::operator*(const int &x) const {
    Matrix result(m, n);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            result.matrix()[i][j] = matrix()[i][j] * x;
        }
    }

    return result;
}

Matrix Matrix::operator*(Matrix &obj) {

    if (m != obj.m || n != obj.n) throw std::runtime_error("Dimension mistach");
    Matrix result(getRows(), obj.getColumns());

    for (int i=0; i<getRows(); i++) {
        for (int j=0; j<obj.getColumns(); j++) {
            for (int k=0; k<getColumns(); k++) {
                result.matrix()[i][j] += matrix()[i][k] * obj.matrix()[k][j];
            }
        }
    }
    return result;
}

#endif //MATH_LIBRARY_MAIN_H