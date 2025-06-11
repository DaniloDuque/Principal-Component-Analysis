#include "src/main/matrix/Matrix.hpp"
#include "src/main/eigen/QR.h"
#include "src/main/pca/PCA.h"
#include "src/main/image/ImageIO.h"
#include <iostream>
#include <cassert>

int main() {

    const Matrix m = {
        {1, 2, 3, 0.56, 1092102},
        {4, 5, 6, -901, -0.128192},
        {6, 7, 8, 100, 12},
        {123, 0.1, 3, 3, 3.14159265359},
        {1, 2, 3, 4, 5},
        {1, 2, 3, 4, 5},
        {1e6, 1e7, 1e8, 1e9, 1e10},
        {10, 20, 30, 40, 50},
        {0, -1, -2, -3, -4},
        {100, 200, 300, 400, 500},
        {3.14, 2.71, 1.61, 0.57, 42},
        {1000, 2000, 3000, 4000, 5000},
        {7, 8, 9, 10, 11},
        {1.1, 2.2, 3.3, 4.4, 5.5},
        {999, 888, 777, 666, 555},
        {-10, -20, -30, -40, -50},
        {0.001, 0.002, 0.003, 0.004, 0.005},
        {12, 13, 14, 15, 16},
        {31415, 92653, 58979, 32384, 62643},
        {0.5, 0.4, 0.3, 0.2, 0.1}
    };


    const QR qr(m);

    puts("First test Q orthogonality");
    const Matrix q = qr.getQ();
    q.print();
    assert(q.is_orthogonal());

    puts("\nSecond test R upper triangular");
    const Matrix r = qr.getR();
    r.print();
    assert(r.is_upper_triangular());

    puts("\nThird test Q*R = A");
    assert(qr.verify(m));
    (q * r).print();

    puts("\nFourth test PCA");
    PCA::lowRankApproximation(m, 4, 1000).print();

    puts("\nFifth test ImageIO");
    const auto Ms = ImageIO::readRGB("../assets/pfp.jpg");
    const Matrix R = PCA::lowRankApproximation(Ms[0], 5, 50);
    puts("R ready!");
    const Matrix G = PCA::lowRankApproximation(Ms[1], 5, 50);
    puts("G ready!");
    const Matrix B = PCA::lowRankApproximation(Ms[2], 5, 50);
    ImageIO::writeRGB("../assets/pfp_out.jpg", R, G, B);
    return 0;
}
