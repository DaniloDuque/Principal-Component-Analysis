#include "src/main/ImageCompressor/ImageCompressor.h"

int main() {
    ImageCompressor::compress("../assets/pfp.jpg", "../assets/compressed", 2, 5);
    ImageCompressor::decompress("../assets/compressed", "../assets/out.jpg");
    return 0;
}
