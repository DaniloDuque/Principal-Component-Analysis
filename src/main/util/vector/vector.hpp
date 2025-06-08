#pragma once
#include "../util.hpp"
#include <vector>

class vector : public std::vector<double> {
public:
    using std::vector<double>::vector;

    double norm() const;
    double dot(const vector& other) const;

    vector static zeros(st size);
    vector operator*(double scalar) const;
    vector operator+(const vector& other) const;
    vector operator-(const vector& other) const;

    void reserve(st size);
};
