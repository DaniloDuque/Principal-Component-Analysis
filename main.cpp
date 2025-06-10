#include <iostream>
#include "src/main/svd/SVD.hpp"
#include "src/main/util/matrix/matrix.hpp"

int main() {

    const Matrix m = {
        {1, 2, 3, 0.56, 1092102},
        {4, 5, 6, -901, -0.128192},
        {6, 7, 8, 100, 12},
        {123, 0.1, 3, 3, 3.14159265359}
    };

    const auto svd = SVD(m);
    std :: cout << std::endl;
    m.print();
    return 0;
}