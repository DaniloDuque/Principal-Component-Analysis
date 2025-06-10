#include <gtest/gtest.h>
#include "main/matrix/Matrix.hpp"

TEST(MatrixTest, Construction) {
    const Matrix m(2, 2, 1.0);
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);
    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
}

TEST(MatrixTest, InitializerListConstruction) {
    const Matrix m{{1.0, 2.0}, {3.0, 4.0}};
    EXPECT_DOUBLE_EQ(m(0,0), 1.0);
    EXPECT_DOUBLE_EQ(m(0,1), 2.0);
    EXPECT_DOUBLE_EQ(m(1,0), 3.0);
    EXPECT_DOUBLE_EQ(m(1,1), 4.0);
}

TEST(MatrixTest, Transpose) {
    const Matrix m{{1.0, 2.0}, {3.0, 4.0}};
    const Matrix mt = m.transpose();
    EXPECT_DOUBLE_EQ(mt(0,0), 1.0);
    EXPECT_DOUBLE_EQ(mt(0,1), 3.0);
    EXPECT_DOUBLE_EQ(mt(1,0), 2.0);
    EXPECT_DOUBLE_EQ(mt(1,1), 4.0);
}

TEST(MatrixTest, MatrixMultiplication) {
    const Matrix m1{{1.0, 2.0}, {3.0, 4.0}};
    const Matrix m2{{5.0, 6.0}, {7.0, 8.0}};
    const Matrix result = m1 * m2;
    EXPECT_DOUBLE_EQ(result(0,0), 19.0);
    EXPECT_DOUBLE_EQ(result(0,1), 22.0);
    EXPECT_DOUBLE_EQ(result(1,0), 43.0);
    EXPECT_DOUBLE_EQ(result(1,1), 50.0);
}

TEST(MatrixTest, FrobeniusNorm) {
    const Matrix m{{1.0, 2.0}, {3.0, 4.0}};
    EXPECT_DOUBLE_EQ(m.frobenius_norm(), sqrt(30.0));
}

TEST(MatrixTest, Slice) {
    const Matrix m{{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}};
    const Matrix slice = m.slice(0, 2, 1, 3);
    EXPECT_EQ(slice.rows(), 2);
    EXPECT_EQ(slice.cols(), 2);
    EXPECT_DOUBLE_EQ(slice(0,0), 2.0);
    EXPECT_DOUBLE_EQ(slice(0,1), 3.0);
    EXPECT_DOUBLE_EQ(slice(1,0), 5.0);
    EXPECT_DOUBLE_EQ(slice(1,1), 6.0);
}