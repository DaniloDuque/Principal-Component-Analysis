#include "ImageIO.h"
#include <opencv2/imgcodecs.hpp>
#include <stdexcept>

std::vector<Matrix> ImageIO::readRGB(const std::string& path) {
    cv::Mat img = cv::imread(path, cv::IMREAD_COLOR);
    if (img.empty()) {
        throw std::runtime_error("Failed to load image: " + path);
    }

    img.convertTo(img, CV_64FC3);
    const int rows = img.rows, cols = img.cols;
    Matrix R(rows, cols), G(rows, cols), B(rows, cols);

    for (int i = 0; i < rows; ++i) {
        const cv::Vec3d* ptr = img.ptr<cv::Vec3d>(i);
        for (int j = 0; j < cols; ++j) {
            B(i, j) = ptr[j][0];
            G(i, j) = ptr[j][1];
            R(i, j) = ptr[j][2];
        }
    }

    return {R, G, B};
}

void ImageIO::writeRGB(const std::string& path, const Matrix& R, const Matrix& G, const Matrix& B) {
    if (R.rows() != G.rows() || G.rows() != B.rows() || R.cols() != G.cols() || G.cols() != B.cols()) {
        throw std::runtime_error("Matrix dimensions of R, G, B channels must be equal");
    }

    const int rows = R.rows(), cols = R.cols();
    cv::Mat img(rows, cols, CV_64FC3);

    for (int i = 0; i < rows; ++i) {
        auto* ptr = img.ptr<cv::Vec3d>(i);
        for (int j = 0; j < cols; ++j) {
            ptr[j][0] = B(i, j);
            ptr[j][1] = G(i, j);
            ptr[j][2] = R(i, j);
        }
    }

    cv::Mat img8u;
    img.convertTo(img8u, CV_8UC3, 1.0 /*scale*/, 0.0 /*offset*/);
    if (!cv::imwrite(path, img8u)) throw std::runtime_error("Failed to write image: " + path);

}
