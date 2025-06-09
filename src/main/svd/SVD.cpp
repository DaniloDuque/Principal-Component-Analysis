#include "SVD.hpp"
#include "../util/util.hpp"
#include <cmath>

SVD::SVD(const Matrix& input) : A(input),
                                U(Matrix::identity(input.rows())),
                                Sigma(Matrix::zeros(input.rows(), input.cols())),
                                Vt(Matrix::identity(input.cols())),
                                B(Matrix::zeros(input.rows(), input.cols())) {
    bidiagonalize();
    diagonalizeBidiagonal();
}

Matrix SVD::getU() const { return U; }

Matrix SVD::getVt() const { return Vt; }

Matrix SVD::getSigma() const { return Sigma; }

void SVD::setEpsValuesToZero(Matrix &M, const double eps = 1e-10) {
    const st rows = M.rows(), cols = M.cols();
    for (st i = 0; i < rows; ++i)
        for (st j = 0; j < cols; ++j)
            if (abs(M(i, j)) < eps) M(i, j) = 0.0;
}

Matrix SVD::Householder(const vector &x, const st start) {
    const st n = x.size() - start;
    vector v(n);
    for (st i = 0; i < n; ++i) v[i] = x[start + i];

    const double alpha = -std::copysign(v.norm(), v[0]);
    vector e = vector::zeros(n); e[0] = 1.0;
    vector u = v - e * alpha; u = u * (1.0 / u.norm());

    const Matrix uMat(u.size(), 1, u);
    Matrix Htrailing = Matrix::identity(n) - uMat * uMat.transpose() * 2.0;
    Matrix H = Matrix::identity(x.size());
    for (st i = 0; i < n; ++i)
        for (st j = 0; j < n; ++j)
            H(start + i, start + j) = Htrailing(i, j);

    return H;
}

void SVD::bidiagonalize() {
    const st row = A.rows(), col = A.cols();
    for (st i = 0; i < std::min(row, col) - 1; ++i) {
        vector colVec(row);
        for (st k = 0; k < row; ++k) colVec[k] = A(k, i);
        Matrix P = Householder(colVec, i);
        A = P * A;
        U = U * P.transpose();
        setEpsValuesToZero(A);
        if (i < col - 2) {
            vector rowVec(col);
            for (st k = 0; k < col; ++k) rowVec[k] = A(i, k);
            Matrix Q = Householder(rowVec, i + 1);
            A = A * Q;
            Vt = Q.transpose() * Vt;
            setEpsValuesToZero(A);
        }
    }
    B = A;
}

void SVD::applyGivensRotation(Matrix& M, const st i, const st j, const double c, const double s, const bool left) {
    const st dim = left ? M.cols() : M.rows();
    for (st k = 0; k < dim; ++k) {
        const double a = left ? M(i, k) : M(k, i);
        const double b = left ? M(j, k) : M(k, j);
        if (left) {
            M(i, k) = c * a - s * b;
            M(j, k) = s * a + c * b;
        } else {
            M(k, i) = c * a - s * b;
            M(k, j) = s * a + c * b;
        }
    }
}

void SVD::diagonalizeBidiagonal() {

}

Matrix SVD::lowRankApprox(const st k) const {
    return U.slice(0, U.rows(), 0, k) * Sigma.slice(0, k, 0, k) * Vt.slice(0, k, 0, Vt.cols());
}
