#pragma once
#include "main/util.hpp"
#include "main/vector/Vector.hpp"
#include <initializer_list>

class Matrix {
public:
    Matrix(st rows, st cols, double init_val = 0.0);
    Matrix(std::initializer_list<Vector> init);
    Matrix() = default;

    [[nodiscard]] st rows() const;
    [[nodiscard]] st cols() const;
    [[nodiscard]] Vector row(st i, st start = 0) const;
    [[nodiscard]] Vector col(st j, st start = 0) const;  [[nodiscard]] Matrix copy() const;
    [[nodiscard]] Matrix transpose() const;
    [[nodiscard]] Vector column_means() const;
    [[nodiscard]] Matrix covariance_matrix() const;
    [[nodiscard]] double frobenius_norm() const;

    double& operator()(st i, st j);
    double operator()(st i, st j) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix& operator=(const Matrix& other);
    Vector operator*(const Vector& vec) const;

    void set_col(st j, const Vector& col, st start = 0);
    void set_row(st i, const Vector& row, st start = 0);
    void print(int precision = 3) const;
    void center_data();
    void add_mean(Vector const& column_means);

    static Matrix identity(st n);
    static Matrix zeros(st rows, st cols);

private:
    st m_rows{}, m_cols{};
    Vector m_data;
    const double EPSILON = 1e-5;
};
