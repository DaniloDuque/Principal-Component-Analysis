#include <gtest/gtest.h>
#include "main/vector/Vector.hpp"

TEST(VectorTest, Norm) {
    const Vector v{3.0, 4.0};
    EXPECT_DOUBLE_EQ(v.norm(), 5.0);
}

TEST(VectorTest, DotProduct) {
    const Vector v1{1.0, 2.0, 3.0};
    const Vector v2{4.0, 5.0, 6.0};
    EXPECT_DOUBLE_EQ(v1.dot(v2), 32.0);
}

TEST(VectorTest, Zeros) {
    const Vector v = Vector::zeros(3);
    EXPECT_EQ(v.size(), 3);
    for (const auto& val : v) {
        EXPECT_DOUBLE_EQ(val, 0.0);
    }
}

TEST(VectorTest, ScalarMultiplication) {
    const Vector v{1.0, 2.0, 3.0};
    const Vector result = v * 2.0;
    EXPECT_DOUBLE_EQ(result[0], 2.0);
    EXPECT_DOUBLE_EQ(result[1], 4.0);
    EXPECT_DOUBLE_EQ(result[2], 6.0);
}

TEST(VectorTest, Addition) {
    const Vector v1{1.0, 2.0, 3.0};
    const Vector v2{4.0, 5.0, 6.0};
    const Vector result = v1 + v2;
    EXPECT_DOUBLE_EQ(result[0], 5.0);
    EXPECT_DOUBLE_EQ(result[1], 7.0);
    EXPECT_DOUBLE_EQ(result[2], 9.0);
}

TEST(VectorTest, Subtraction) {
    const Vector v1{4.0, 5.0, 6.0};
    const Vector v2{1.0, 2.0, 3.0};
    const Vector result = v1 - v2;
    EXPECT_DOUBLE_EQ(result[0], 3.0);
    EXPECT_DOUBLE_EQ(result[1], 3.0);
    EXPECT_DOUBLE_EQ(result[2], 3.0);
}