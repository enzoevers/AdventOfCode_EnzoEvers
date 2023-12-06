#pragma once

#include "./Mapping.hpp"
#include <vector>

struct MultiMap {
    /*
     * It is assumed that the mapped ranges don't overlap
     */
    std::vector<Mapping> mappings;

    int map(int srcId) {
        int dstId = srcId;

        for (auto it = mappings.begin(); it < mappings.end(); it++) {
            if (it->isInMappedRange(srcId)) {
                dstId = it->map(srcId);
                break;
            }
        }

        return dstId;
    }
};