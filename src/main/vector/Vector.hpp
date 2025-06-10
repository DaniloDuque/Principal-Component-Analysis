#pragma once
#include "main/util.hpp"
#include <vector>

class Vector : public std::vector<double> {
public:
    using std::vector<double>::vector;

    [[nodiscard]] double norm() const;
    [[nodiscard]] double mean() const;
    [[nodiscard]] double dot(const Vector& other) const;

    Vector static zeros(st size);
    Vector operator*(double scalar) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector normalize() const;

    void reserve(st size);
};
