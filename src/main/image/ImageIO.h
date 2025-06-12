#pragma once
#include "main/matrix/Matrix.hpp"
#include "main/matrix/CompressedMatrix.h"
#include <opencv2/opencv.hpp>
#include <vector>
using namespace std;

class ImageIO {
public:
    static vector<Matrix> readRGB(const string& path);
    static vector<CompressedMatrix> readBinary(const string& path);
    static void writeRGB(const string& path, const Matrix& R, const Matrix& G, const Matrix& B);
    static void writeBinary(const string& path, const CompressedMatrix& R, const CompressedMatrix& G, const CompressedMatrix& B);
};
