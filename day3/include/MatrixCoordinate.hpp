#pragma once

#include <utility>

class MatrixCoordinate {

  public:
    std::size_t x;
    std::size_t y;

    MatrixCoordinate(std::size_t x, std::size_t y);

    /*
     * srcDimensions.first: width
     * srcDimensions.second: height
     *
     * Throws an out_of_range error if the coordinates would be larger than
     * srcDimensions.
     */
    std::size_t
    toLinear(std::pair<std::size_t, std::size_t> srcDimensions) const;
};