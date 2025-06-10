#pragma once
#include "main/matrix/Matrix.hpp"

class PCA {
    static Matrix lowRankApproximation(const Matrix& A);
};
