#include "Vector.hpp"
#include "main/util.hpp"
#include <cassert>
#include <cmath>
#include <random>

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

void Vector::normalize_this() {
    *this = this->normalize();
}

Vector Vector::random_unit(const st size) {
    thread_local std::mt19937 gen(std::random_device{}());
    std::normal_distribution dist(0.0, 1.0);
    Vector v(size);
    for (st i = 0; i < size; ++i) v[i] = dist(gen);
    return v.normalize();
}

void Vector::reserve(const st size) {
    std::vector<double>::reserve(size);
}
