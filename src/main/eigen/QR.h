#pragma once
#include "main/matrix/Matrix.hpp"

class QR {
    Matrix Q;
    Matrix R;
    static std::pair<Matrix, Matrix> qr_householder(const Matrix& input) ;

public:
    explicit QR(const Matrix& A);

    [[nodiscard]] const Matrix& getQ() const;
    [[nodiscard]] const Matrix& getR() const;

    [[nodiscard]] bool verify(const Matrix& A, double tol = 1e-5) const;
};
