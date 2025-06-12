#include "ImageCompressor.h"
#include "../image/ImageIO.h"
#include "main/pca/PCA.h"
#include <thread>
using namespace std;

void ImageCompressor::compress(const string& image_path, const string& output_path, const st k, const st num_iter) {
    const auto rgb = ImageIO::readRGB(image_path);
    CompressedMatrix compressed_R, compressed_G, compressed_B;

    thread tR([&] { compressed_R = PCA::lowRankApproximation(rgb[0], k, num_iter); });
    thread tG([&] { compressed_G = PCA::lowRankApproximation(rgb[1], k, num_iter); });
    thread tB([&] { compressed_B = PCA::lowRankApproximation(rgb[2], k, num_iter); });

    tR.join(), tG.join(), tB.join();
    ImageIO::writeBinary(output_path, compressed_R, compressed_G, compressed_B);
}

void ImageCompressor::decompress(const string& compressed_image_path, const string& output_image_path) {
    const auto rgb = ImageIO::readBinary(compressed_image_path);
    Matrix R_k, G_k, B_k;

    thread tR([&] { R_k = rgb[0].decompress(); });
    thread tG([&] { G_k = rgb[1].decompress(); });
    thread tB([&] { B_k = rgb[2].decompress(); });

    tR.join(), tG.join(), tB.join();
    ImageIO::writeRGB(output_image_path, R_k, G_k, B_k);
}
