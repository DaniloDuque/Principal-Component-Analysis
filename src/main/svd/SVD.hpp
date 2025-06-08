#include "../util/matrix/matrix.hpp"
#include "../util/util.hpp"
#pragma once

class SVD {
public:
    SVD(const Matrix A);
    Matrix getU() const;
    Matrix getSigma() const;
    Matrix getVt() const;
    Matrix lowRankApprox(st k) const;
    void static applyGivensRotation(Matrix& mat, st i, st j, double c, double s, bool left);
    void static setEpsValuesToZero(Matrix &M, double eps);

private:
    Matrix A, U, Sigma, Vt, B;
    Matrix Householder(const vector &x, int i);
    void bidiagonalize();
    void diagonalizeBidiagonal();

};
