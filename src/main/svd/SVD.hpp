#pragma once
#include "../util/matrix/matrix.hpp"
#include "../util/util.hpp"

class SVD {
public:
    explicit SVD(const Matrix& input);

    [[nodiscard]] Matrix getU() const;
    [[nodiscard]] Matrix getSigma() const;
    [[nodiscard]] Matrix getVt() const;
    [[nodiscard]] Matrix lowRankApprox(st k) const;
    static void applyGivensRotation(Matrix& M, st i, st j, double c, double s, bool left);
    static void setEpsValuesToZero(Matrix &M, double eps);
    static Matrix Householder(const vector &x, st start);

private:
    Matrix A, U, Sigma, Vt, B;
    void bidiagonalize();
    void diagonalizeBidiagonal();

};
