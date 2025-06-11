#include "ImageCompressor.h"
#include "image/ImageIO.h"
#include <pthread/pthread.h>

using namespace std;

// vector<Matrix> ImageCompressor::compress(const string& path) {
//     auto rgb = ImageIO::readRGB(path);
//     auto [R, G, B] = tie(rgb[0], rgb[1], rgb[2]);
// }
