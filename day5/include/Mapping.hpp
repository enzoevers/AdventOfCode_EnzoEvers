#pragma once

#include <stdexcept>

struct Mapping {
    int srcStartId;
    int dstStartId;
    int range;

    Mapping(int srcStartId, int dstStartId, int range)
        : srcStartId(srcStartId), dstStartId(dstStartId), range(range) {
        if (range <= 0) {
            throw std::invalid_argument("Error: range must be > 0");
        }
        if (srcStartId < 0) {
            throw std::invalid_argument("Error: srcStartId must be > 0");
        }
        if (dstStartId < 0) {
            throw std::invalid_argument("Error: dstStartId must be > 0");
        }
        if (srcStartId == dstStartId) {
            throw std::invalid_argument(
                "Error: srcStartId cannot be equal to dstStartId");
        }
    }

    int getSrcEndId() { return srcStartId + range - 1; }
    int getDstEndId() { return dstStartId + range - 1; }
    int getSrcToDstOffset() { return dstStartId - srcStartId; }

    bool isInMappedRange(int srcId) {
        bool inRange = false;
        if (srcId >= srcStartId && srcId <= getSrcEndId()) {
            inRange = true;
        }
        return inRange;
    }

    int map(int srcId) {
        int dstId = srcId;
        if (isInMappedRange(srcId)) {
            dstId = srcId + getSrcToDstOffset();
        }

        return dstId;
    }
};