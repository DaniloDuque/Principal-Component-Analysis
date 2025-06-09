#include <gtest/gtest.h>
#include "main/svd/SVD.hpp"
#include "main/util/matrix/matrix.hpp"

TEST(SVDTest, ConstructsWithoutError) {
    const Matrix A({
        {1.0, 2.0},
        {3.0, 4.0}
    });

    const SVD svd(A);
    EXPECT_EQ(svd.getU().rows(), 2);
    EXPECT_EQ(svd.getVt().cols(), 2);
}
