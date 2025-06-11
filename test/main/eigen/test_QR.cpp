#include <gtest/gtest.h>
#include "main/eigen/QR.h"

class QRTest : public testing::Test {
protected:
    static Matrix createTestMatrix() {
        return {
            {12, -51, 4},
            {6, 167, -68},
            {-4, 24, -41}
        };
    }
};

// Test QR decomposition construction
TEST_F(QRTest, Construction) {
    const Matrix A = createTestMatrix();
    const QR qr(A);
    
    EXPECT_EQ(qr.getQ().rows(), 3);
    EXPECT_EQ(qr.getQ().cols(), 3);
    EXPECT_EQ(qr.getR().rows(), 3);
    EXPECT_EQ(qr.getR().cols(), 3);
}

// Test orthogonality of Q matrix
TEST_F(QRTest, QOrthogonality) {
    const Matrix A = createTestMatrix();
    const QR qr(A);
    
    const Matrix& Q = qr.getQ();
    const Matrix QT = Q.transpose();
    const Matrix I = Q * QT;

    EXPECT_TRUE(I.is_orthogonal());
}

// Test R is upper triangular
TEST_F(QRTest, RUpperTriangular) {
    const Matrix A = createTestMatrix();
    const QR qr(A);
    const Matrix& R = qr.getR();

    EXPECT_TRUE(R.is_upper_triangular());
}

// Test verification method
TEST_F(QRTest, Verification) {
    const Matrix A = createTestMatrix();
    const QR qr(A);
    
    EXPECT_TRUE(qr.verify(A));

    Matrix modified = A;
    modified(0, 0) += 1.0;
    EXPECT_FALSE(qr.verify(modified));
}

// Test with different matrix dimensions
TEST_F(QRTest, NonSquareMatrix) {
    Matrix rect(4, 3);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; ++j) {
            rect(i, j) = i + j + 1;
        }
    }
    
    const QR qr(rect);
    EXPECT_EQ(qr.getQ().rows(), 4);
    EXPECT_EQ(qr.getQ().cols(), 4);
    EXPECT_EQ(qr.getR().rows(), 4);
    EXPECT_EQ(qr.getR().cols(), 3);
    EXPECT_TRUE(qr.verify(rect));
}