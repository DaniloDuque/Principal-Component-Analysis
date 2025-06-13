#pragma once
#include <utility>
#include "main/matrix/Matrix.hpp"
#include "main/vector/Vector.hpp"

struct LowRankApproximation {
    Matrix Y, V_k;
    Vector mean;

    LowRankApproximation(const Matrix& Y_, const Matrix& V_k_, Vector mean_)
        : Y(Y_), V_k(V_k_), mean(std::move(mean_)) {}

    LowRankApproximation() = default;

    [[nodiscard]] Matrix reconstruct() const {
        Matrix X_hat = Y * V_k.transpose();
        X_hat.add_mean(mean);
        return X_hat;
    }
};

