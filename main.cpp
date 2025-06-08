#include "src/main/svd/SVD.hpp"
#include "src/main/util/matrix/matrix.hpp"

int main() {

    const Matrix m = {
        {1, 2, 3},
        {4, 5, 6},
        {6, 7, 8}
    };

    const SVD svd = SVD(m);
    m.print();
    return 0;
}