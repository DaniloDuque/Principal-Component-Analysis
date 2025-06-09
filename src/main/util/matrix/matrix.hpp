#pragma once
#include "../util.hpp"
#include "../vector/vector.hpp"
#include <initializer_list>

class Matrix {
public:
    Matrix(st rows, st cols, double init_val = 0.0);
    Matrix(st rows, st cols, const vector& init);
    Matrix(std::initializer_list<vector> init);

    [[nodiscard]] st rows() const;
    [[nodiscard]] st cols() const;

    double& operator()(st i, st j);
    double operator()(st i, st j) const;
    [[nodiscard]] vector row(st i) const;
    [[nodiscard]] vector col(st j) const;

    [[nodiscard]] Matrix copy() const;
    [[nodiscard]] Matrix transpose() const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    vector operator*(const vector& vec) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;

    void print(int precision = 3) const;
    void resize(st new_rows, st new_cols, bool preserve);
    [[nodiscard]] Matrix slice(st row_start, st row_end, st col_start, st col_end) const;

    [[nodiscard]] double frobenius_norm() const;

    static Matrix identity(st n);
    static Matrix zeros(st rows, st cols);

private:
    st m_rows, m_cols;
    vector m_data;
};
