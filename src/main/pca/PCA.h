#pragma once
#include "main/util.hpp"
#include "main/matrix/Matrix.hpp"
#include "../matrix/LowRankApproximation.h"

class PCA {
protected:
    static std::pair<Matrix, Matrix> power_iteration(const Matrix& X, st k, st num_iter);
    static LowRankApproximation low_rank_approximation(const Matrix& A, st k, st num_iter = 200);
public:
    virtual ~PCA() = default;
    virtual void reduce_dimensionality(const std::string& input_path, const std::string& output_path, st rank, st num_iter) = 0;
};
