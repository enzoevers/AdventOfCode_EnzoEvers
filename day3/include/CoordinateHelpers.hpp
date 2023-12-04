#pragma once

#include <utility>

class ICoordinateHelper {
  public:
    virtual std::size_t
    coordiate2dToLinear(std::pair<std::size_t, std::size_t> coordinate) = 0;
};