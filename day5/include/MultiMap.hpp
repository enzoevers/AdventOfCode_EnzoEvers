#pragma once

#include "./Mapping.hpp"
#include <vector>

struct MultiMap {
    /*
     * It is assumed that the mapped ranges don't overlap
     */
    std::vector<Mapping> mappings;

    void clearMappings() {
        mappings.clear();
        mappings.shrink_to_fit();
    }

    uint64_t map(uint64_t srcId) {
        uint64_t dstId = srcId;

        for (auto it = mappings.begin(); it < mappings.end(); it++) {
            if (it->isInMappedRange(srcId)) {
                dstId = it->map(srcId);
                break;
            }
        }

        return dstId;
    }
};