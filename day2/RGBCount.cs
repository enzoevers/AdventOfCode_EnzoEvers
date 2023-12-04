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

    public override string ToString() => $"(rCount: {rCount}, gCount: {gCount}, bCount: {bCount})";
}