#include "Matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

Matrix::Matrix(const st rows, const st cols, const double init_val): m_rows(rows), m_cols(cols), m_data(rows * cols, init_val) {}

Matrix::Matrix(const std::initializer_list<Vector> init) {
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

Vector Matrix::row(const st i, const st start) const {
    assert(i < m_rows && start <= m_cols);
    auto begin = m_data.begin() + static_cast<std::ptrdiff_t>(i * m_cols + start);
    auto end = m_data.begin() + static_cast<std::ptrdiff_t>(i * m_cols + m_cols);
    return {begin, end};
}

void Matrix::set_row(const st i, const Vector& row, const st start) {
    assert(i < m_rows);
    assert(start <= m_cols);
    assert(row.size() <= m_cols - start);
    std::ranges::copy(row, m_data.begin() + static_cast<std::ptrdiff_t>(i * m_cols + start));
}

Vector Matrix::col(const st j, const st start) const {
    assert(j < m_cols);
    assert(start <= m_rows);
    Vector result;
    result.reserve(m_rows - start);
    for (st i = start; i < m_rows; ++i)
        result.push_back((*this)(i, j));
    return result;
}

void Matrix::set_col(const st j, const Vector& col, const st start) {
    assert(j < m_cols);
    assert(start <= m_rows);
    assert(col.size() <= m_rows - start);
    for (st i = 0; i < col.size(); ++i)
        (*this)(start + i, j) = col[i];
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

    for (st i = 0; i < m_rows; ++i)
        for (st j = 0; j < other.m_cols; ++j) {
            double sum = 0.0;
            for (st k = 0; k < m_cols; ++k)
                sum += (*this)(i, k) * other(k, j);
            result(i, j) = sum;
        }
    return result;
}

Vector Matrix::operator*(const Vector& vec) const {
    assert(m_cols == vec.size());
    Vector result(m_rows);

    for (st i = 0; i < m_rows; ++i) {
        double sum = 0.0;
        for (st j = 0; j < m_cols; ++j)
            sum += (*this)(i, j) * vec[j];
        result[i] = sum;
    }

    return result;
}

Matrix Matrix::operator*(const double scalar) const {
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

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        m_rows = other.m_rows;
        m_cols = other.m_cols;
        m_data = other.m_data;
    }
    return *this;
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

void Matrix::center_data() {
    for (st j = 0; j < m_cols; ++j) {
        const auto mean = this->col(j).mean();
        for (st i = 0; i < m_rows; ++i) (*this)(i, j) -= mean;
    }
}

Matrix Matrix::covariance_matrix() const {
    const Matrix c = this->copy();
    return c.transpose() * c * (1.0 / (static_cast<double>(m_rows) - 1));
}

Vector Matrix::column_means() const {
    Vector means(m_cols);
    for (st j = 0; j < m_cols; ++j) means[j] = this->col(j).mean();
    return means;
}

void Matrix::add_mean(const Vector& column_means) {
    assert(column_means.size() == m_cols);
    for (st i = 0; i < m_rows; ++i) {
        for (st j = 0; j < m_cols; ++j) {
            (*this)(i, j) += column_means[j];
        }
    }
}
