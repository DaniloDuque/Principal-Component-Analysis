#include "QR.h"
#include "main/matrix/Matrix.hpp"
#include "main/vector/Vector.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utility>

QR::QR(const Matrix& A): Q({{}}), R({{}}) {
    std::tie(Q, R) = qr_householder(A);
}

std::pair<Matrix, Matrix> QR::qr_householder(const Matrix& input) {
    Matrix A = input;
    const st m = A.rows();
    const st n = A.cols();
    Matrix Q = Matrix::identity(m);

    for (st k = 0; k < std::min(m, n); ++k) {
        Vector x = A.col(k, k);
        const double alpha = -std::copysign(x.norm(), x[0]);
        Vector e1 = Vector::zeros(m - k); e1[0] = 1.0;
        Vector v = (x - e1 * alpha).normalize();

        for (st j = k; j < n; ++j) {
            Vector a_col = A.col(j, k);
            const double vTa = v.dot(a_col);
            A.set_col(j, a_col - v * (2 * vTa), k);
        }

        for (st i = 0; i < m; ++i) {
            Vector q_row = Q.row(i, k);
            const double qv = q_row.dot(v);
            Q.set_row(i, q_row - v * (2 * qv), k);
        }
    }

    return {Q, A};
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




