#include "../include/MatrixCoordinate.hpp"

#include <stdexcept>

MatrixCoordinate::MatrixCoordinate(std::size_t x, std::size_t y) : x(x), y(y) {}

std::size_t
MatrixCoordinate::toLinear(std::pair<std::size_t, std::size_t> srcDimensions) {
    if (x >= srcDimensions.first || y >= srcDimensions.second) {
        throw std::out_of_range("Coordinates out of range for size");
    }

    return x + (y * srcDimensions.first);
}