#include "src/main/matrix/Matrix.hpp"
#include "src/main/eigen/QR.h"
#include "src/main/pca/PCA.h"
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
        {1e6, 1e7, 1e8, 1e9, 1e10}
    };

    const QR qr(m);

    puts("First test Q orthogonality");
    const Matrix q = qr.getQ();
    q.print();
    assert(q.is_orthogonal());

    puts("Second test R upper triangular");
    const Matrix r = qr.getR();
    r.print();
    assert(r.is_upper_triangular());

    puts("Third test Q*R = A");
    assert(qr.verify(m));
    (q * r).print();

    puts("Fourth test PCA");
    PCA::lowRankApproximation(m, 2, 100).print();
    return 0;
}
