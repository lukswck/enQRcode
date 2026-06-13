#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include "grid_to_png.h"
#include "TinyPngOut.hpp"

void writeMatrixToPng(
    const grid &matrix, 
    int scale,          
    const std::string &filename) {

    size_t grid_width{matrix.size() * scale};
    size_t grid_heigth{matrix.size() * scale};

    std::vector<uint8_t> pixels(grid_width * grid_heigth * 3);
    // single row vector 

    for (uint32_t y = 0; y < grid_heigth; ++y) {
        for (uint32_t x = 0; x < grid_width; ++x) {

            uint32_t sx = x / scale;
            uint32_t sy = y / scale;

            uint8_t bit = matrix[sx][sy];
                // static_cast<size_t>(sy) * grid_width + sx];
            uint8_t value = bit ? 255 : 0 ; // 0 -> black, 1 -> white

            size_t idx = (static_cast<size_t>(y) * grid_width + x) * 3;

            pixels[idx + 0] = value;
            pixels[idx + 1] = value;
            pixels[idx + 2] = value;
        }
    }

    std::ofstream out(filename, std::ios::binary);
    TinyPngOut pngout(grid_width, grid_heigth, out);
    pngout.write(pixels.data(), grid_width * grid_heigth);
    }