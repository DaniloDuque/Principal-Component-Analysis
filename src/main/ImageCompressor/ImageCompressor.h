#pragma once
#include <string>
#include "main/util.hpp"
using namespace std;

class ImageCompressor {
public:
    static void compress(const string& image_path, const string& output_path, st k, st num_iter);
    static void decompress(const string& compressed_image_path, const string& output_image_path);
};
