#include "vector.hpp"
#include "../util.hpp"
#include <cassert>
#include <cmath>

vector vector::zeros(const st size) { return vector(size, 0.0); }

double vector::norm() const {
    double result = 0.0;
    for (const auto& i : *this) result += i * i;
    return sqrt(result);
}

double vector::dot(const vector& other) const {
    double result = 0.0;
    for (st i = 0; i < size(); ++i) result += (*this)[i] * other[i];
    return result;
}

vector vector::operator*(const double scalar) const {
    vector result(size());
    for (st i = 0; i < size(); ++i) result[i] = (*this)[i] * scalar;
    return result;
}

vector vector::operator+(const vector& other) const {
    assert(size() == other.size());
    vector result(size());
    for (st i = 0; i < size(); ++i) result[i] = (*this)[i] + other[i];
    return result;
}

vector vector::operator-(const vector& other) const {
    assert(size() == other.size());
    vector result(size());
    for (st i = 0; i < size(); ++i) result[i] = (*this)[i] - other[i];
    return result;
}

void vector::reserve(const st size) {
    std::vector<double>::reserve(size);
}
