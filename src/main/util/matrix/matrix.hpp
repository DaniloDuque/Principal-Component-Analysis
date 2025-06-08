#pragma once
#include "../util.hpp"
#include "../vector/vector.hpp"
#include <cassert>
#include <initializer_list>

class Matrix {
public:
    Matrix(st rows, st cols, double init_val = 0.0);
    Matrix(st rows, st cols, vector init);
    Matrix(std::initializer_list<vector> init);

    st rows() const;
    st cols() const;

    double& operator()(st i, st j);
    double operator()(st i, st j) const;
    vector row(st i) const;
    vector col(st j) const;

    Matrix copy() const;
    Matrix transpose() const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    vector operator*(const vector& vec) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    void print(st precision = 3) const;
    void resize(st new_rows, st new_cols, bool preserve);
    Matrix slice(st row_start, st row_end, st col_start, st col_end) const;

    double frobenius_norm() const;

    static Matrix identity(st n);
    static Matrix zeros(st rows, st cols);

private:
    st m_rows, m_cols;
    vector m_data;
};
