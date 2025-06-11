#include "PCA.h"
#include "main/eigen/QR.h"
#include "main/vector/Vector.hpp"
using namespace std;

Matrix PCA::qr_iteration(const Matrix& X, const st k, const st num_iter) {
    Matrix cov = X.covariance_matrix();
    Matrix Q_total = Matrix::identity(cov.rows());

    for (st iter = 0; !cov.is_diagonal() && iter < num_iter; ++iter) {
        const QR qr(cov);
        cov = qr.getR() * qr.getQ();
        Q_total = Q_total * qr.getQ();
    }

    vector<pair<double, Vector>> eig_pairs; eig_pairs.reserve(cov.rows());
    for (st i = 0; i < cov.rows(); ++i) eig_pairs.emplace_back(cov(i, i), Q_total.col(i));

    ranges::sort(eig_pairs,[](const auto& a, const auto& b) { return abs(a.first) > abs(b.first); });
    Matrix V_k(cov.rows(), k);
    for (st j = 0; j < k; ++j)
        for (st i = 0; i < cov.rows(); ++i)
            V_k(i, j) = eig_pairs[j].second[i];

    return X * V_k;
}


Matrix PCA::lowRankApproximation(const Matrix &A, const st k, const st num_iter) {
    Matrix X = A.copy(); X.center_data();
    return qr_iteration(X, k, num_iter);
}
