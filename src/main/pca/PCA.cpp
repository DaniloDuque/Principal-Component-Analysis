#include "PCA.h"
#include "main/vector/Vector.hpp"
#include "../matrix/LowRankApproximation.h"
using namespace std;

constexpr double EPSILON = 1e-5;

std::pair<Matrix, Matrix> PCA::power_iteration(const Matrix& X, const st k, const st num_iter) {
    const Matrix cov = X.covariance_matrix();
    const st n = cov.rows();
    Matrix V_k(n, k);

    for (st eig = 0; eig < k; ++eig) {
        Vector v = Vector::random_unit(n);

        for (st iter = 0; iter < num_iter; ++iter) {
            Vector v_new = cov * v;

            for (st j = 0; j < eig; ++j) {
                const Vector& prev = V_k.col(j);
                v_new = v_new - prev * prev.dot(v_new);
            }

            v_new.normalize_this();
            if ((v - v_new).norm() < EPSILON) break;
            v = std::move(v_new);
        }
        V_k.set_col(eig, v);
    }

    Matrix Y = X * V_k;
    return {Y, V_k};
}

LowRankApproximation PCA::low_rank_approximation(const Matrix &A, const st k, const st num_iter) {
    Matrix X = A.copy();
    X.center_data();
    const Vector mean = A.column_means();

    auto [Y, V_k] = power_iteration(X, k, num_iter);
    return {Y, V_k, mean};
}
