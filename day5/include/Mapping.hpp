#pragma once

#include <stdexcept>

struct Mapping {
    uint64_t srcStartId;
    uint64_t dstStartId;
    int range;

    Mapping() {}

    Mapping(uint64_t srcStartId, uint64_t dstStartId, uint64_t range)
        : srcStartId(srcStartId), dstStartId(dstStartId), range(range) {
        if (range == 0) {
            throw std::invalid_argument("Error: range must be > 0");
        }
        if (srcStartId == dstStartId) {
            throw std::invalid_argument(
                "Error: srcStartId cannot be equal to dstStartId");
        }
    }

    uint64_t getSrcEndId() { return srcStartId + range - 1; }
    uint64_t getDstEndId() { return dstStartId + range - 1; }
    int64_t getSrcToDstOffset() {
        // TODO: Perform bound checks
        return (int64_t) dstStartId - (int64_t) srcStartId;
    }
    int64_t getDstToSrcOffset() {
        // TODO: Perform bound checks
        return (int64_t) srcStartId - (int64_t) dstStartId;
    }

    bool srcIdIsInMappedRange(uint64_t srcId) {
        bool inRange = false;
        if (srcId >= srcStartId && srcId <= getSrcEndId()) {
            inRange = true;
        }
        return inRange;
    }

    bool dstIdIsInMappedRange(uint64_t dstId) {
        bool inRange = false;
        if (dstId >= dstStartId && dstId <= getDstEndId()) {
            inRange = true;
        }
        return inRange;
    }

    uint64_t map(uint64_t srcId) {
        uint64_t dstId = srcId;
        if (srcIdIsInMappedRange(srcId)) {
            // TODO: Perform bound checks
            dstId = (uint64_t) ((int64_t) srcId + getSrcToDstOffset());
        }

        return dstId;
    }

    uint64_t rmap(uint64_t dstId) {
        uint64_t srcId = dstId;
        if (dstIdIsInMappedRange(srcId)) {
            // TODO: Perform bound checks
            srcId = (uint64_t) ((int64_t) dstId + getDstToSrcOffset());
        }

        return srcId;
    }
};