#include "ImagePCA.h"
#include "main/matrix/LowRankApproximation.h"
#include "../io/ImageIO.h"
#include "main/pca/PCA.h"
#include <thread>
using namespace std;

void ImagePCA::reduce_dimensionality(const std::string& input_path, const std::string& output_path, const st rank, const st num_iter) {
    const auto rgb = ImageIO::readRGB(input_path);

    LowRankApproximation R_k, G_k, B_k;
    thread tR([&] { R_k = low_rank_approximation(rgb[0], rank, num_iter); });
    thread tG([&] { G_k = low_rank_approximation(rgb[1], rank, num_iter); });
    thread tB([&] { B_k = low_rank_approximation(rgb[2], rank, num_iter); });
    tR.join(), tG.join(), tB.join(); // Technically at this point we have reduced dimensionality and could return

    Matrix MR_k, MG_k, MB_k;         // Let`s continue to see how the image looks as a kth PCA approximation
    thread tRk([&] { MR_k = R_k.reconstruct(); });
    thread tGk([&] { MG_k = G_k.reconstruct(); });
    thread tBk([&] { MB_k = B_k.reconstruct(); });

    tRk.join(), tGk.join(), tBk.join();
    ImageIO::writeRGB(output_path, MR_k, MG_k, MB_k);
}