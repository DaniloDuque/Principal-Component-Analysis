#pragma once
#include "main/util.hpp"
#include <vector>

class Vector : public std::vector<double> {
public:
    using std::vector<double>::vector;

    [[nodiscard]] double norm() const;
    [[nodiscard]] double mean() const;
    [[nodiscard]] double dot(const Vector& other) const;

    static Vector random_unit(st size);

    Vector static zeros(st size);
    Vector operator*(double scalar) const;
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    [[nodiscard]] Vector normalize() const;
    void normalize_this();

    void reserve(st size);
};
