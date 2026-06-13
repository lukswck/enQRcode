#pragma once

#include <string>
#include "grid.h"
#include "TinyPngOut.hpp"

// matrix containing the boolean values for the QRcode
// enlarges each source pixel to a scale x scale block in the output
static void writeMatrixToPng(
    const grid &matrix, 
    int scale,          
    const std::string &filename) ;