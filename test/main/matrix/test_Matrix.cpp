#include <gtest/gtest.h>
#include "main/matrix/Matrix.hpp"
#include <cmath>

class MatrixTest : public testing::Test {
protected:
    static bool areMatricesEqual(const Matrix& a, const Matrix& b, double tol = 1e-5) {
        if (a.rows() != b.rows() || a.cols() != b.cols()) return false;

        for (st i = 0; i < a.rows(); ++i) {
            for (st j = 0; j < a.cols(); ++j) {
                if (std::abs(a(i, j) - b(i, j)) > tol) return false;
            }
        }
        return true;
    }
};

// Constructor Tests
TEST_F(MatrixTest, DefaultConstructor) {
    Matrix m(2, 3);
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 3);
    for (st i = 0; i < 2; ++i) {
        for (st j = 0; j < 3; ++j) {
            EXPECT_DOUBLE_EQ(m(i, j), 0.0);
        }
    }
}

TEST_F(MatrixTest, InitValueConstructor) {
    Matrix m(2, 2, 1.5);
    for (st i = 0; i < 2; ++i) {
        for (st j = 0; j < 2; ++j) {
            EXPECT_DOUBLE_EQ(m(i, j), 1.5);
        }
    }
}

TEST_F(MatrixTest, VectorConstructor) {
    const Vector v = {1.0, 2.0, 3.0, 4.0};
    const Matrix m(2, 2, v);
    EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

TEST_F(MatrixTest, InitializerListConstructor) {
    const Matrix m({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0}
    });
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);
    EXPECT_DOUBLE_EQ(m(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(m(0, 1), 2.0);
    EXPECT_DOUBLE_EQ(m(1, 0), 3.0);
    EXPECT_DOUBLE_EQ(m(1, 1), 4.0);
}

// Accessor Tests
TEST_F(MatrixTest, RowColAccess) {
    const Matrix m({
        Vector{1.0, 2.0, 3.0},
        Vector{4.0, 5.0, 6.0}
    });

    const Vector row0 = m.row(0);
    EXPECT_EQ(row0, Vector({1.0, 2.0, 3.0}));

    const Vector col1 = m.col(1);
    EXPECT_EQ(col1, Vector({2.0, 5.0}));
}

// Operation Tests
TEST_F(MatrixTest, MatrixMultiplication) {
    const Matrix a({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0}
    });
    const Matrix b({
        Vector{5.0, 6.0},
        Vector{7.0, 8.0}
    });

    const Matrix c = a * b;
    EXPECT_EQ(c.rows(), 2);
    EXPECT_EQ(c.cols(), 2);
    EXPECT_DOUBLE_EQ(c(0, 0), 19.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 22.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 43.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 50.0);
}

TEST_F(MatrixTest, ScalarMultiplication) {
    const Matrix a({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0}
    });

    const Matrix b = a * 2.0;
    EXPECT_DOUBLE_EQ(b(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(b(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(b(1, 0), 6.0);
    EXPECT_DOUBLE_EQ(b(1, 1), 8.0);
}

TEST_F(MatrixTest, MatrixAddition) {
    const Matrix a({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0}
    });
    const Matrix b({
        Vector{5.0, 6.0},
        Vector{7.0, 8.0}
    });

    const Matrix c = a + b;
    EXPECT_DOUBLE_EQ(c(0, 0), 6.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 8.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 10.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 12.0);
}

TEST_F(MatrixTest, MatrixSubtraction) {
    const Matrix a({
        Vector{5.0, 6.0},
        Vector{7.0, 8.0}
    });
    const Matrix b({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0}
    });

    const Matrix c = a - b;
    EXPECT_DOUBLE_EQ(c(0, 0), 4.0);
    EXPECT_DOUBLE_EQ(c(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(c(1, 0), 4.0);
    EXPECT_DOUBLE_EQ(c(1, 1), 4.0);
}

TEST_F(MatrixTest, Transpose) {
    const Matrix a({
        Vector{1.0, 2.0, 3.0},
        Vector{4.0, 5.0, 6.0}
    });

    const Matrix aT = a.transpose();
    EXPECT_EQ(aT.rows(), 3);
    EXPECT_EQ(aT.cols(), 2);
    EXPECT_DOUBLE_EQ(aT(0, 0), 1.0);
    EXPECT_DOUBLE_EQ(aT(0, 1), 4.0);
    EXPECT_DOUBLE_EQ(aT(1, 0), 2.0);
    EXPECT_DOUBLE_EQ(aT(1, 1), 5.0);
    EXPECT_DOUBLE_EQ(aT(2, 0), 3.0);
    EXPECT_DOUBLE_EQ(aT(2, 1), 6.0);
}

TEST_F(MatrixTest, FrobeniusNorm) {
    const Matrix a({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0}
    });

    EXPECT_DOUBLE_EQ(a.frobenius_norm(), std::sqrt(30.0));
}

// Static Method Tests
TEST_F(MatrixTest, Identity) {
    const Matrix i = Matrix::identity(3);
    EXPECT_TRUE(i.is_identity());
    EXPECT_TRUE(i.is_diagonal());
}

TEST_F(MatrixTest, Zeros) {
    const Matrix z = Matrix::zeros(2, 3);
    for (st i = 0; i < z.rows(); ++i) {
        for (st j = 0; j < z.cols(); ++j) {
            EXPECT_DOUBLE_EQ(z(i, j), 0.0);
        }
    }
}

// Matrix Property Tests
TEST_F(MatrixTest, IsOrthogonal) {
    constexpr double theta = M_PI / 4; // 45 degrees
    const Matrix rot({
        Vector{std::cos(theta), -std::sin(theta)},
        Vector{std::sin(theta), std::cos(theta)}
    });

    EXPECT_TRUE(rot.is_orthogonal());
}

TEST_F(MatrixTest, IsUpperTriangular) {
    const Matrix ut({
        Vector{1.0, 2.0, 3.0},
        Vector{0.0, 4.0, 5.0},
        Vector{0.0, 0.0, 6.0}
    });

    EXPECT_TRUE(ut.is_upper_triangular());
}

// Data Processing Tests
TEST_F(MatrixTest, CenterData) {
    Matrix m({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0},
        Vector{5.0, 6.0}
    });

    m.center_data();
    for (st j = 0; j < m.cols(); ++j) {
        double sum = 0.0;
        for (st i = 0; i < m.rows(); ++i) {
            sum += m(i, j);
        }
        EXPECT_NEAR(sum, 0.0, 1e-2);
    }
}

TEST_F(MatrixTest, CovarianceMatrix) {
    const Matrix m({
        Vector{1.0, 2.0},
        Vector{3.0, 4.0},
        Vector{5.0, 6.0}
    });

    const Matrix cov = m.covariance_matrix();
    EXPECT_EQ(cov.rows(), m.cols());
    EXPECT_EQ(cov.cols(), m.cols());
    EXPECT_TRUE(areMatricesEqual(cov, cov.transpose()));
}

TEST_F(MatrixTest, Slice) {
    const Matrix m({
        Vector{1.0, 2.0, 3.0},
        Vector{4.0, 5.0, 6.0},
        Vector{7.0, 8.0, 9.0}
    });

    const Matrix slice = m.slice(0, 2, 1, 3);
    EXPECT_EQ(slice.rows(), 2);
    EXPECT_EQ(slice.cols(), 2);
    EXPECT_DOUBLE_EQ(slice(0, 0), 2.0);
    EXPECT_DOUBLE_EQ(slice(0, 1), 3.0);
    EXPECT_DOUBLE_EQ(slice(1, 0), 5.0);
    EXPECT_DOUBLE_EQ(slice(1, 1), 6.0);
}