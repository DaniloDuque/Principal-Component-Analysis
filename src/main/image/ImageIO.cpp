#include "ImageIO.h"

#include <fstream>
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

std::vector<CompressedMatrix> ImageIO::readBinary(const std::string& path) {
    std::ifstream in(path, std::ios::binary);
    if (!in) throw std::runtime_error("Failed to open binary input file: " + path);

    auto readMatrix = [&](Matrix& mat) {
        st rows, cols;
        in.read(reinterpret_cast<char*>(&rows), sizeof(st));
        in.read(reinterpret_cast<char*>(&cols), sizeof(st));
        mat = Matrix(rows, cols);
        for (st i = 0; i < rows; ++i)
            for (st j = 0; j < cols; ++j)
                in.read(reinterpret_cast<char*>(&mat(i, j)), sizeof(double));
    };

    auto readVector = [&](Vector& vec) {
        st size;
        in.read(reinterpret_cast<char*>(&size), sizeof(st));
        vec = Vector(size);
        for (st i = 0; i < size; ++i)
            in.read(reinterpret_cast<char*>(&vec[i]), sizeof(double));
    };

    auto readCompressed = [&]() -> CompressedMatrix {
        CompressedMatrix img;
        readMatrix(img.Y);
        readMatrix(img.V_k);
        readVector(img.mean);
        return img;
    };

    CompressedMatrix R = readCompressed();
    CompressedMatrix G = readCompressed();
    CompressedMatrix B = readCompressed();
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

void ImageIO::writeBinary(const std::string& path,
                          const CompressedMatrix& R,
                          const CompressedMatrix& G,
                          const CompressedMatrix& B) {
    std::ofstream out(path, std::ios::binary);
    if (!out) throw std::runtime_error("Failed to open binary output file: " + path);

    auto writeMatrix = [&](const Matrix& mat) {
        const st rows = mat.rows(), cols = mat.cols();
        out.write(reinterpret_cast<const char*>(&rows), sizeof(st));
        out.write(reinterpret_cast<const char*>(&cols), sizeof(st));
        for (st i = 0; i < mat.rows(); ++i) {
            for (st j = 0; j < mat.cols(); ++j) {
                double val = mat(i, j);
                out.write(reinterpret_cast<const char*>(&val), sizeof(double));
            }
        }
    };

    auto writeVector = [&](const Vector& vec) {
        const st size = vec.size();
        out.write(reinterpret_cast<const char*>(&size), sizeof(st));
        for (st i = 0; i < size; ++i)
            out.write(reinterpret_cast<const char*>(&vec[i]), sizeof(double));
    };

    auto writeCompressed = [&](const CompressedMatrix& img) {
        writeMatrix(img.Y);
        writeMatrix(img.V_k);
        writeVector(img.mean);
    };

    writeCompressed(R), writeCompressed(G), writeCompressed(B);
}
