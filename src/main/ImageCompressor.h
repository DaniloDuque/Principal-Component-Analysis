#pragma once
#include "main/matrix/Matrix.hpp"
#include <vector>

class ImageCompressor {
    public:
    static std::vector<Matrix> compress(const std::string& path);
    static void compress_and_save(const std::string& path, const std::string& output_path);
    static void decompress(const Matrix& A, const Matrix& B, const std::string& output_path);
};
