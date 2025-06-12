#include "Matrix.hpp"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

Matrix::Matrix(const st rows, const st cols, const double init_val): m_rows(rows), m_cols(cols), m_data(rows * cols, init_val) {}

Matrix::Matrix(const st rows, const st cols, const Vector& init): m_rows(rows), m_cols(cols) {
    assert(init.size() == m_rows * m_cols);
    m_data = init;
}

void Matrix::clean_values_close_to_zero() {
    const st rows = m_rows, cols = m_cols;
    for (st i = 0; i < rows; ++i)
        for (st j = 0; j < cols; ++j)
            if (abs((*this)(i, j)) < EPSILON)
                (*this)(i, j) = 0.0;
}

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

void Matrix::normalize() {
    *this = *this * (1.0 / this->frobenius_norm());
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
    Vector new_data(new_rows * new_cols, 0.0);

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

bool Matrix::is_diagonal() const {
    for (st i = 0; i < m_rows; ++i)
        for (st j = 0; j < m_cols; ++j)
            if (i != j && abs((*this)(i, j)) > EPSILON) return false;
    return true;
}

bool Matrix::is_identity() const {
    for (st i = 0; i < m_rows; ++i)
        for (st j = 0; j < m_cols; ++j) {
            if (i == j && abs((*this)(i, j) - 1.0) > EPSILON) return false;
            if (i != j && abs((*this)(i, j)) > EPSILON) return false;
        }
    return true;
}

bool Matrix::is_orthogonal() const {
    return (*this * this->transpose()).is_identity();
}

bool Matrix::is_upper_triangular() const {
    for (st i = 1; i < m_rows; ++i)
        for (st j = 0; j < std::min(i, m_cols); ++j)
            if (std::abs((*this)(i, j)) > EPSILON)
                return false;
    return true;
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
