#pragma once
#include "main/util.hpp"
#include "main/matrix/Matrix.hpp"
#include "../matrix/CompressedMatrix.h"

class PCA {
    static std::pair<Matrix, Matrix> qr_iteration(const Matrix &X, st k, st num_iter);
    static std::pair<Matrix, Matrix> power_iteration(const Matrix& input, st k, st num_iter);
public:
    static CompressedMatrix lowRankApproximation(const Matrix& A, st k, st num_iter = 200);
};
