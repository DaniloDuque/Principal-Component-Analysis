#include "main/vector/Vector.hpp"
#include <gtest/gtest.h>
#include <cmath>
#include <numeric>

constexpr double EPS = 1e-9;

bool almost_equal(const Vector& a, const Vector& b, double eps = EPS) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i) {
        if (std::abs(a[i] - b[i]) > eps) return false;
    }
    return true;
}

TEST(VectorTest, Norm) {
    const Vector v = {3.0, 4.0};
    EXPECT_NEAR(v.norm(), 5.0, EPS);
}

TEST(VectorTest, Mean) {
    const Vector v = {1.0, 2.0, 3.0, 4.0};
    EXPECT_NEAR(v.mean(), 2.5, EPS);
}

TEST(VectorTest, DotProduct) {
    const Vector a = {1.0, 2.0, 3.0};
    const Vector b = {4.0, -5.0, 6.0};
    EXPECT_NEAR(a.dot(b), 12.0, EPS);
}

TEST(VectorTest, ScalarMultiplication) {
    const Vector v = {1.0, 2.0, 3.0};
    const Vector result = v * 2.0;
    const Vector expected = {2.0, 4.0, 6.0};
    EXPECT_TRUE(almost_equal(result, expected));
}

TEST(VectorTest, VectorAddition) {
    const Vector a = {1.0, 2.0, 3.0};
    const Vector b = {4.0, 5.0, 6.0};
    const Vector result = a + b;
    const Vector expected = {5.0, 7.0, 9.0};
    EXPECT_TRUE(almost_equal(result, expected));
}

TEST(VectorTest, VectorSubtraction) {
    const Vector a = {4.0, 5.0, 6.0};
    const Vector b = {1.0, 2.0, 3.0};
    const Vector result = a - b;
    const Vector expected = {3.0, 3.0, 3.0};
    EXPECT_TRUE(almost_equal(result, expected));
}

TEST(VectorTest, Normalize) {
    const Vector v = {3.0, 4.0};
    const Vector normed = v.normalize();
    EXPECT_NEAR(normed.norm(), 1.0, EPS);
}

TEST(VectorTest, NormalizeZeroVector) {
    const Vector v = {0.0, 0.0, 0.0};
    const Vector normed = v.normalize();
    EXPECT_TRUE(almost_equal(v, normed));
}

TEST(VectorTest, NormalizeThis) {
    Vector v = {3.0, 4.0};
    v.normalize_this();
    EXPECT_NEAR(v.norm(), 1.0, EPS);
}

TEST(VectorTest, RandomUnit) {
    const Vector v = Vector::random_unit(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_NEAR(v.norm(), 1.0, 1e-6);
}