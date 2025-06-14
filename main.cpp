#include "src/main/input/image/pca/ImagePCA.h"

int main() {
    auto image_pca = ImagePCA();
    image_pca.reduce_dimensionality("../assets/input/f1.jpg", "../assets/output/f1_k2.jpg", 2, 5);
    image_pca.reduce_dimensionality("../assets/input/f1.jpg", "../assets/output/f1_k5.jpg", 5, 5);
    image_pca.reduce_dimensionality("../assets/input/f1.jpg", "../assets/output/f1_k25.jpg", 25, 5);
    image_pca.reduce_dimensionality("../assets/input/f1.jpg", "../assets/output/f1_k50.jpg", 50, 5);
    image_pca.reduce_dimensionality("../assets/input/f1.jpg", "../assets/output/f1_k100.jpg", 100, 5);
    image_pca.reduce_dimensionality("../assets/input/f1.jpg", "../assets/output/f1_k200.jpg", 200, 5);

    image_pca.reduce_dimensionality("../assets/input/pfp.jpg", "../assets/output/pfp_k2.jpg", 2, 5);
    image_pca.reduce_dimensionality("../assets/input/pfp.jpg", "../assets/output/pfp_k5.jpg", 5, 5);
    image_pca.reduce_dimensionality("../assets/input/pfp.jpg", "../assets/output/pfp_k10.jpg", 10, 5);
    image_pca.reduce_dimensionality("../assets/input/pfp.jpg", "../assets/output/pfp_k25.jpg", 25, 5);
    image_pca.reduce_dimensionality("../assets/input/pfp.jpg", "../assets/output/pfp_k50.jpg", 50, 5);
    image_pca.reduce_dimensionality("../assets/input/pfp.jpg", "../assets/output/pfp_k100.jpg", 100, 5);
    image_pca.reduce_dimensionality("../assets/input/pfp.jpg", "../assets/output/pfp_k200.jpg", 200, 5);

    return 0;
}
