#include "QR.h"
#include "main/matrix/Matrix.hpp"
#include "main/vector/Vector.hpp"
#include <algorithm>
#include <cmath>
#include <utility>

std::pair<Matrix, Matrix> QR::qr_householder(const Matrix& input) {
    Matrix A = input;
    const st m = A.rows();
    const st n = A.cols();
    Matrix Q = Matrix::identity(m);

    for (st k = 0; k < std::min(m, n); ++k) {
        Vector x(m - k);
        for (st i = k; i < m; ++i) x[i - k] = A(i, k);

        const double alpha = -std::copysign(x.norm(), x[0]);
        Vector e1 = Vector::zeros(m - k); e1[0] = 1.0;
        Vector v = (x - e1 * alpha).normalize();

        for (st j = k; j < n; ++j) {
            double dot = 0.0;
            for (int i = 0; i < v.size(); ++i) dot += v[i] * A(k + i, j);
            for (int i = 0; i < v.size(); ++i) A(k + i, j) -= 2 * v[i] * dot;
        }

        for (st j = 0; j < m; ++j) {
            double dot = 0.0;
            for (int i = 0; i < v.size(); ++i) dot += v[i] * Q(j, k + i);
            for (int i = 0; i < v.size(); ++i) Q(j, k + i) -= 2 * dot * v[i];
        }
    }
    return {Q, A};
}

QR::QR(const Matrix& A): Q({{}}), R({{}}) {
    std::tie(Q, R) = qr_householder(A);
}

const Matrix& QR::getQ() const { return Q; }

const Matrix& QR::getR() const { return R; }

bool QR::verify(const Matrix &A, const double tol) const {
    if (!Q.is_orthogonal()) return false;
    if (!R.is_upper_triangular()) return false;

    Matrix QR = Q * R;
    if (QR.rows() != A.rows() || QR.cols() != A.cols()) return false;

    for (int i = 0; i < QR.rows(); ++i) {
        for (int j = 0; j < QR.cols(); ++j) {
            if (std::abs(QR(i, j) - A(i, j)) > tol) return false;
        }
    }

    return true;
}




