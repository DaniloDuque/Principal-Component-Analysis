#include "gtest/gtest.h"
#include "main/pca/PCA.h"
#include "main/matrix/Matrix.hpp"

class PCA_TestWrapper : public PCA {
public:
    static std::pair<Matrix, Matrix> test_power_iteration(const Matrix& X, const st k, const st num_iter) {
        return power_iteration(X, k, num_iter);
    }

    static LowRankApproximation test_low_rank_approximation(const Matrix& A, const st k, const st num_iter = 200) {
        return low_rank_approximation(A, k, num_iter);
    }
};

bool matrix_approx_equal(const Matrix& a, const Matrix& b, const double tol = 1e-5) {
    if (a.rows() != b.rows() || a.cols() != b.cols()) return false;
    for (st i = 0; i < a.rows(); ++i)
        for (st j = 0; j < a.cols(); ++j)
            if (std::abs(a(i, j) - b(i, j)) > tol) return false;
    return true;
}

bool vector_approx_equal(const Vector& a, const Vector& b, const double tol = 1e-5) {
    if (a.size() != b.size()) return false;
    for (st i = 0; i < a.size(); ++i)
        if (std::abs(a[i] - b[i]) > tol) return false;
    return true;
}

TEST(PCATest, PowerIterationReturnsExpectedShapes) {
    const Matrix X{ { {1, 2}, {3, 4}, {5, 6} } };

    auto [Y, V_k] = PCA_TestWrapper::test_power_iteration(X, 1, 100);

    EXPECT_EQ(Y.rows(), 3);
    EXPECT_EQ(Y.cols(), 1);
    EXPECT_EQ(V_k.rows(), 2);
    EXPECT_EQ(V_k.cols(), 1);
    EXPECT_NEAR(V_k.col(0).norm(), 1.0, 1e-5);
}

TEST(PCATest, LowRankApproximationBasicProperties) {
    const Matrix A{ { {1, 2}, {3, 4}, {5, 6} } };

    const LowRankApproximation approx = PCA_TestWrapper::test_low_rank_approximation(A, 1, 100);

    EXPECT_EQ(approx.Y.rows(), 3);
    EXPECT_EQ(approx.Y.cols(), 1);
    EXPECT_EQ(approx.V_k.rows(), 2);
    EXPECT_EQ(approx.V_k.cols(), 1);
    EXPECT_EQ(approx.mean.size(), 2);

    Matrix centered = A.copy();
    centered.center_data();
    for (const double val : centered.column_means())
        EXPECT_NEAR(val, 0.0, 1e-5);
}
