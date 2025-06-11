#include "Vector.hpp"
#include "main/util.hpp"
#include <cassert>
#include <cmath>

Vector Vector::zeros(const st size) { return Vector(size, 0.0); }

double Vector::norm() const {
    double result = 0.0;
    for (const auto& i : *this) result += i * i;
    return sqrt(result);
}

double Vector::mean() const {
    double result = 0.0;
    for (const auto& i : *this) result += i;
    return result / static_cast<double>(size());
}

double Vector::dot(const Vector& other) const {
    double result = 0.0;
    for (st i = 0; i < size(); ++i) result += (*this)[i] * other[i];
    return result;
}

Vector Vector::operator*(const double scalar) const {
    Vector result(size());
    for (st i = 0; i < size(); ++i) result[i] = (*this)[i] * scalar;
    return result;
}

Vector Vector::operator+(const Vector& other) const {
    assert(size() == other.size());
    Vector result(size());
    for (st i = 0; i < size(); ++i) result[i] = (*this)[i] + other[i];
    return result;
}

Vector Vector::operator-(const Vector& other) const {
    assert(size() == other.size());
    Vector result(size());
    for (st i = 0; i < size(); ++i) result[i] = (*this)[i] - other[i];
    return result;
}

Vector Vector::normalize() const {
    Vector v(*this);
    const double norm = v.norm();
    if (norm == 0.0) return v;
    return v * (1.0 / norm);
}

void Vector::reserve(const st size) {
    std::vector<double>::reserve(size);
}
