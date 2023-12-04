public struct RGBCount
{
    public RGBCount()
    {
        rCount = 0;
        gCount = 0;
        bCount = 0;
    }

    public RGBCount(int _rCount, int _gCount, int _bCount)
    {
        rCount = _rCount;
        gCount = _gCount;
        bCount = _bCount;
    }

    public int rCount { set; get; }
    public int gCount { set; get; }
    public int bCount { set; get; }

    public static bool operator <=(in RGBCount a, in RGBCount b)
    {
        return (a.rCount <= b.rCount)
            && (a.gCount <= b.gCount)
            && (a.bCount <= b.bCount);
    }

    public static bool operator >=(in RGBCount a, in RGBCount b)
    {
        return (a.rCount >= b.rCount)
            && (a.gCount >= b.gCount)
            && (a.bCount >= b.bCount);
    }

    public static bool operator <(in RGBCount a, in RGBCount b)
    {
        return (a.rCount < b.rCount)
            && (a.gCount < b.gCount)
            && (a.bCount < b.bCount);
    }

    public static bool operator >(in RGBCount a, in RGBCount b)
    {
        return (a.rCount > b.rCount)
            && (a.gCount > b.gCount)
            && (a.bCount > b.bCount);
    }

    public static RGBCount mergeMax(in RGBCount a, in RGBCount b)
    {
        RGBCount rgbCountMerged = new RGBCount(
            Math.Max(a.rCount, b.rCount),
            Math.Max(a.gCount, b.gCount),
            Math.Max(a.bCount, b.bCount)
        );

        return rgbCountMerged;
    }

    public int Power()
    {
        return (rCount * gCount * bCount);
    }

    public override string ToString() => $"(rCount: {rCount}, gCount: {gCount}, bCount: {bCount})";
}