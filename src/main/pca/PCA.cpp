#include "PCA.h"
#include "main/eigen/QR.h"
#include "main/vector/Vector.hpp"
#include "../matrix/CompressedMatrix.h"
using namespace std;

constexpr double EPSILON = 1e-5;

std::pair<Matrix, Matrix> PCA::qr_iteration(const Matrix& X, const st k, const st num_iter) {
    Matrix cov = X.covariance_matrix();
    Matrix Q_total = Matrix::identity(cov.rows());

    for (st iter = 0; !cov.is_diagonal() && iter < num_iter; ++iter) {
        const QR qr(cov);
        cov = qr.getR() * qr.getQ();
        Q_total = Q_total * qr.getQ();
    }

    std::vector<std::pair<double, Vector>> eig_pairs;
    eig_pairs.reserve(cov.rows());
    for (st i = 0; i < cov.rows(); ++i)
        eig_pairs.emplace_back(cov(i, i), Q_total.col(i));

    std::ranges::sort(eig_pairs, [](const auto& a, const auto& b) {
        return std::abs(a.first) > std::abs(b.first);
    });

    Matrix V_k(cov.rows(), k);
    for (st j = 0; j < k; ++j)
        for (st i = 0; i < cov.rows(); ++i)
            V_k(i, j) = eig_pairs[j].second[i];

    Matrix Y = X * V_k;
    return {Y, V_k};
}

std::pair<Matrix, Matrix> PCA::power_iteration(const Matrix& X, const st k, const st num_iter) {
    Matrix cov = X.covariance_matrix();
    const st n = cov.rows();
    Matrix V_k(n, k);

    for (st eig = 0; eig < k; ++eig) {
        Vector v = Vector::random_unit(n);

        for (st iter = 0; iter < num_iter; ++iter) {
            Vector v_new = cov * v;

            for (st j = 0; j < eig; ++j) {
                const Vector& prev = V_k.col(j);
                v_new = v_new - prev * (prev.dot(v_new));
            }

            v_new.normalize_this();
            if ((v - v_new).norm() < EPSILON)
                break;
            v = std::move(v_new);
        }

        V_k.set_col(eig, v);

        Vector Av = cov * v;
        for (st i = 0; i < n; ++i)
            for (st j = 0; j < n; ++j)
                cov(i, j) -= v[i] * Av[j];
    }

    Matrix Y = X * V_k;
    return {Y, V_k};
}


CompressedMatrix PCA::lowRankApproximation(const Matrix &A, const st k, const st num_iter) {
    Matrix X = A.copy();
    X.center_data();
    const Vector mean = A.column_means();

    auto [Y, V_k] = power_iteration(X, k, num_iter);
    return {Y, V_k, mean};
}



