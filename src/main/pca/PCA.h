#pragma once
#include "main/util.hpp"
#include "main/matrix/Matrix.hpp"

class PCA {
    static Matrix qr_iteration(const Matrix &X, st k, st num_iter);
public:
    static Matrix lowRankApproximation(const Matrix& A, st k, st num_iter = 200);
};
