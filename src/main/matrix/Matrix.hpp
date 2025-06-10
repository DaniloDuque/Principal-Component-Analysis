#pragma once
#include "main/util.hpp"
#include "main/vector/Vector.hpp"
#include <initializer_list>

class Matrix {
public:
    Matrix(st rows, st cols, double init_val = 0.0);
    Matrix(st rows, st cols, const Vector& init);
    Matrix(std::initializer_list<Vector> init);

    [[nodiscard]] st rows() const;
    [[nodiscard]] st cols() const;

    double& operator()(st i, st j);
    double operator()(st i, st j) const;
    [[nodiscard]] Vector row(st i) const;
    [[nodiscard]] Vector col(st j) const;

    [[nodiscard]] Matrix copy() const;
    [[nodiscard]] Matrix transpose() const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    Vector operator*(const Vector& vec) const;

    void print(int precision = 3) const;
    void resize(st new_rows, st new_cols, bool preserve);
    void clean_values_close_to_zero();
    [[nodiscard]] Matrix slice(st row_start, st row_end, st col_start, st col_end) const;
    [[nodiscard]] double frobenius_norm() const;

    static Matrix identity(st n);
    static Matrix zeros(st rows, st cols);

    [[nodiscard]] Matrix covariance_matrix() const;

    bool is_identity() const;
    bool is_orthogonal() const;
    bool is_upper_triangular() const;

private:
    void center_data();
    st m_rows, m_cols;
    Vector m_data;
    const double EPSILON = 1e-10;
};
