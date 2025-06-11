#pragma once
#include "main/matrix/Matrix.hpp"
#include <opencv2/opencv.hpp>
#include <vector>

class ImageIO {
public:
    static std::vector<Matrix> readRGB(const std::string& path);
    static void writeRGB(const std::string& path, const Matrix& R, const Matrix& G, const Matrix& B);
};
