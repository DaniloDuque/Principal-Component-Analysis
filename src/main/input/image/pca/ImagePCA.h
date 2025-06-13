#pragma once
#include <string>
#include "main/util.hpp"
#include "main/pca/PCA.h"
using namespace std;

class ImagePCA final : public PCA {
public:
    void reduce_dimensionality(const std::string& input_path, const std::string& output_path, st rank, st num_iter) override;
};
