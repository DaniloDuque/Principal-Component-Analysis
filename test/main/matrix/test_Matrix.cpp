#include "main/matrix/Matrix.hpp"
#include "gtest/gtest.h"

bool matrix_equal(const Matrix& a, const Matrix& b, const double tol = 1e-9) {
    if (a.rows() != b.rows() || a.cols() != b.cols()) return false;
    for (st i = 0; i < a.rows(); ++i)
        for (st j = 0; j < a.cols(); ++j)
            if (std::abs(a(i, j) - b(i, j)) > tol) return false;
    return true;
}

TEST(MatrixTest, ConstructorInitVal) {
    Matrix m(3, 4, 2.5);
    EXPECT_EQ(m.rows(), 3);
    EXPECT_EQ(m.cols(), 4);
    for (st i = 0; i < 3; ++i)
        for (st j = 0; j < 4; ++j)
            EXPECT_DOUBLE_EQ(m(i, j), 2.5);
}

TEST(MatrixTest, InitializerListConstructor) {
    Matrix m{{{1.0, 2.0}, {3.0, 4.0}}};
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);
    EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

TEST(MatrixTest, RowAccessAndModification) {
    Matrix m(2, 3, 0.0);
    m.set_row(0, {1.0, 2.0, 3.0});
    const Vector r = m.row(0);
    EXPECT_EQ(r, Vector({1.0, 2.0, 3.0}));
}

TEST(MatrixTest, ColumnAccessAndModification) {
    Matrix m(3, 2, 0.0);
    m.set_col(1, {5.0, 6.0, 7.0});
    const Vector c = m.col(1);
    EXPECT_EQ(c, Vector({5.0, 6.0, 7.0}));
}

TEST(MatrixTest, OperatorAccess) {
    Matrix m(2, 2, 0.0);
    m(1, 1) = 9.0;
    EXPECT_DOUBLE_EQ(m(1, 1), 9.0);
}

TEST(MatrixTest, CopyAndAssignment) {
    const Matrix m1{{{1.0, 2.0}, {3.0, 4.0}}};
    const Matrix m2 = m1.copy();
    EXPECT_TRUE(matrix_equal(m1, m2));
    Matrix m3(2, 2, 0.0);
    m3 = m1;
    EXPECT_TRUE(matrix_equal(m3, m1));
}

TEST(MatrixTest, Transpose) {
    const Matrix m{{{1, 2, 3}, {4, 5, 6}}};
    const Matrix expected{{{1, 4}, {2, 5}, {3, 6}}};
    EXPECT_TRUE(matrix_equal(m.transpose(), expected));
}

TEST(MatrixTest, MatrixMultiplication) {
    const Matrix a{{{1, 2}, {3, 4}}};
    const Matrix b{{{2, 0}, {1, 2}}};
    const Matrix expected{{{4, 4}, {10, 8}}};
    EXPECT_TRUE(matrix_equal(a * b, expected));
}

TEST(MatrixTest, MatrixVectorMultiplication) {
    const Matrix m{{{1, 2}, {3, 4}}};
    const Vector v{1, 2};
    const Vector expected{5, 11};
    EXPECT_EQ(m * v, expected);
}

TEST(MatrixTest, ScalarMultiplication) {
    const Matrix m{{{1, 2}, {3, 4}}};
    const Matrix expected{{{2, 4}, {6, 8}}};
    EXPECT_TRUE(matrix_equal(m * 2.0, expected));
}

TEST(MatrixTest, AdditionAndSubtraction) {
    const Matrix a{{{1, 2}, {3, 4}}};
    const Matrix b{{{4, 3}, {2, 1}}};
    const Matrix sum{{{5, 5}, {5, 5}}};
    const Matrix diff{{{-3, -1}, {1, 3}}};
    EXPECT_TRUE(matrix_equal(a + b, sum));
    EXPECT_TRUE(matrix_equal(a - b, diff));
}

TEST(MatrixTest, IdentityMatrix) {
    Matrix I = Matrix::identity(3);
    for (st i = 0; i < 3; ++i)
        for (st j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(I(i, j), i == j ? 1.0 : 0.0);
}

TEST(MatrixTest, ZerosMatrix) {
    Matrix Z = Matrix::zeros(2, 3);
    for (st i = 0; i < 2; ++i)
        for (st j = 0; j < 3; ++j)
            EXPECT_DOUBLE_EQ(Z(i, j), 0.0);
}

TEST(MatrixTest, FrobeniusNorm) {
    const Matrix m{{{3, 4}}};
    EXPECT_DOUBLE_EQ(m.frobenius_norm(), 5.0);
}

TEST(MatrixTest, CenterDataAndAddMean) {
    Matrix m{{{1, 2}, {3, 4}, {5, 6}}};
    const Vector means = m.column_means();
    m.center_data();
    for (const Vector new_means = m.column_means(); const double val : new_means) EXPECT_NEAR(val, 0.0, 1e-9);
    m.add_mean(means);
    const Vector restored_means = m.column_means();
    for (st i = 0; i < restored_means.size(); ++i)
        EXPECT_NEAR(restored_means[i], means[i], 1e-9);
}

TEST(MatrixTest, CovarianceMatrix) {
    Matrix m{{{1, 2}, {3, 4}, {5, 6}}};
    m.center_data();
    Matrix cov = m.covariance_matrix();
    EXPECT_EQ(cov.rows(), 2);
    EXPECT_EQ(cov.cols(), 2);
    // No strict expected value but should be symmetric and positive semi-definite
    EXPECT_NEAR(cov(0, 1), cov(1, 0), 1e-9);
}
