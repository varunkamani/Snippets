ll seg[2000000], lazy[2000000];  /* adjust size as per need  */
void create_seg(int low, int high, int pos) {
    if(low == high) {
        seg[pos] = input[low];
        return;
    }
    int mid = (low + high) / 2;
    create_seg(low, mid, 2 * pos + 1);
    create_seg(mid + 1, high, 2 * pos + 2);
    seg[pos] = MIN(seg[2 * pos + 1], seg[2 * pos + 2]);
}
ll rangeQuery(int low, int high, int qlow, int qhigh, int pos) {
    if(qlow <= low && qhigh >= high) {
        return seg[pos];
    }
    if(qlow > high || qhigh < low) {
        return INT_MAX;
    }
    int mid = (low + high) / 2;
    return MIN(rangeQuery(low, mid, qlow, qhigh, 2 * pos + 1),
               rangeQuery(mid + 1, high, qlow, qhigh, 2 * pos + 2));
}
void updateSegmentTree(int index, int delta, int low, int high, int pos) {
    if(index < low || index > high) {
        return;
    }
    if(low == high) {
        seg[pos] += delta; /* delta = change added */
        return;
    }
    int mid = (low + high) / 2;
    updateSegmentTree(index, delta, low, mid, 2 * pos + 1);
    updateSegmentTree(index, delta, mid + 1, high, 2 * pos + 2);
    seg[pos] = MIN(seg[2 * pos + 1], seg[2 * pos + 2]);
}
void updateSegmentTreeRangeLazy(int startRange, int endRange,
                                int delta, int low, int high, int pos) {
    if(low > high) {
        return;
    }
    if (lazy[pos] != 0) {
        seg[pos] += lazy[pos];
        if (low != high) { //not a leaf node
            lazy[2 * pos + 1] += lazy[pos];
            lazy[2 * pos + 2] += lazy[pos];
        }
        lazy[pos] = 0;
    }
    if(startRange > high || endRange < low) return;
    if(startRange <= low && endRange >= high) {
        seg[pos] += delta;
        if(low != high) {
            lazy[2 * pos + 1] += delta;
            lazy[2 * pos + 2] += delta;
        }
        return;
    }
    int mid = (low + high) / 2;
    updateSegmentTreeRangeLazy(startRange, endRange,
                               delta, low, mid, 2 * pos + 1);
    updateSegmentTreeRangeLazy(startRange, endRange,
                               delta, mid + 1, high, 2 * pos + 2);
    seg[pos] = MIN(seg[2 * pos + 1], seg[2 * pos + 2]);
}
