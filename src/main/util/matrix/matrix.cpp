#include "matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

Matrix::Matrix(const st rows, const st cols, const double init_val): m_rows(rows), m_cols(cols), m_data(rows * cols, init_val) {}

Matrix::Matrix(const st rows, const st cols, const vector& init): m_rows(rows), m_cols(cols) {
    assert(init.size() == m_rows * m_cols);
    m_data = init;
}

Matrix::Matrix(const std::initializer_list<vector> init) {
    m_rows = init.size();
    m_cols = init.begin()->size();
    m_data.reserve(m_rows * m_cols);

    for (const auto& row : init) {
        assert(row.size() == m_cols);
        m_data.insert(m_data.end(), row.begin(), row.end());
    }
}

st Matrix::rows() const { return m_rows; }
st Matrix::cols() const { return m_cols; }

vector Matrix::row(const st i) const {
    assert(i < m_rows);
    auto begin = m_data.begin() + static_cast<std::ptrdiff_t>(i * m_cols);
    auto end = begin + static_cast<std::ptrdiff_t>(m_cols);
    return {begin, end};
}

vector Matrix::col(const st j) const {
    assert(j < m_cols);
    vector result(m_rows);
    for (st i = 0; i < m_rows; ++i)
        result[i] = (*this)(i, j);
    return result;
}

double& Matrix::operator()(const st i, const st j) {
    assert(i < m_rows && j < m_cols);
    return m_data[i * m_cols + j];
}
double Matrix::operator()(const st i, const st j) const {
    assert(i < m_rows && j < m_cols);
    return m_data[i * m_cols + j];
}

Matrix Matrix::copy() const {
    Matrix result(m_rows, m_cols);
    result.m_data = m_data;
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(m_cols, m_rows);
    for (st i = 0; i < m_rows; ++i)
        for (st j = 0; j < m_cols; ++j)
            result(j, i) = (*this)(i, j);
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    assert(m_cols == other.m_rows);
    Matrix result(m_rows, other.m_cols);
    const Matrix other_transposed = other.transpose();

    for (st i = 0; i < m_rows; ++i) {
        vector row_i = row(i);
        for (st j = 0; j < other.m_cols; ++j)
            result(i, j) = row_i.dot(other_transposed.row(j));
    }

    return result;
}

vector Matrix::operator*(const vector& vec) const {
    assert(m_cols == vec.size());
    vector result(m_rows);

    for (st i = 0; i < m_rows; ++i) {
        double sum = 0.0;
        for (st j = 0; j < m_cols; ++j)
            sum += (*this)(i, j) * vec[j];
        result[i] = sum;
    }

    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(m_rows, m_cols);
    result.m_data = m_data * scalar;
    return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
    assert(m_rows == other.m_rows && m_cols == other.m_cols);
    Matrix result(m_rows, m_cols);
    result.m_data = m_data + other.m_data;
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    assert(m_rows == other.m_rows && m_cols == other.m_cols);
    Matrix result(m_rows, m_cols);
    result.m_data = m_data - other.m_data;
    return result;
}

Matrix Matrix::identity(const st n) {
    Matrix I(n, n);
    for (st i = 0; i < n; ++i) I(i, i) = 1.0;
    return I;
}

Matrix Matrix::zeros(const st rows, const st cols) {
    Matrix Z(rows, cols);
    return Z;
}

double Matrix::frobenius_norm() const {
    double sum = 0.0;
    for(const auto &i : m_data) sum += i*i;
    return sqrt(sum);
}

void Matrix::print(const int precision) const {
    std::cout << std::fixed << std::setprecision(precision);
    for (st i = 0; i < m_rows; ++i) {
        for (st j = 0; j < m_cols; ++j)
            std::cout << (*this)(i, j) << " ";
        std::cout << "\n";
    }
}

void Matrix::resize(const st new_rows, const st new_cols, const bool preserve) {
    vector new_data(new_rows * new_cols, 0.0);

    if (preserve) {
        const st min_rows = std::min(new_rows, m_rows);
        const st min_cols = std::min(new_cols, m_cols);
        for (st i = 0; i < min_rows; ++i)
            for (st j = 0; j < min_cols; ++j)
                new_data[i * new_cols + j] = (*this)(i, j);
    }

    m_data = std::move(new_data);
    m_rows = new_rows;
    m_cols = new_cols;
}

Matrix Matrix::slice(const st row_start, const st row_end, const st col_start, const st col_end) const {
    assert(row_end > row_start && row_end <= m_rows);
    assert(col_end > col_start && col_end <= m_cols);

    const st new_rows = row_end - row_start, new_cols = col_end - col_start;
    Matrix result(new_rows, new_cols);

    for (st i = 0; i < new_rows; ++i)
        for (st j = 0; j < new_cols; ++j)
            result(i, j) = (*this)(row_start + i, col_start + j);

    return result;
}
