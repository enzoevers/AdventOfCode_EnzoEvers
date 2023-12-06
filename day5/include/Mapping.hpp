#pragma once

struct Mapping {
    int srcStartId;
    int dstStartId;
    int range;

    Mapping(int srcStartId, int dstStartId, int range)
        : srcStartId(srcStartId), dstStartId(dstStartId), range(range) {}

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