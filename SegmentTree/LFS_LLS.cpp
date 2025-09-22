/*
6
5 2 6 1 3 7
4
For index 4 (value 3):
Left First Smaller (nearest)  = 3
Left Last Smaller (farthest) = 1
*/
#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> st;

    SegmentTree(vector<int> &arr) {
        n = arr.size();
        st.resize(4 * n);
        build(1, 0, n - 1, arr);
    }

    void build(int node, int l, int r, vector<int> &arr) {
        if (l == r) {
            st[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, arr);
        build(2 * node + 1, mid + 1, r, arr);
        st[node] = min(st[2 * node], st[2 * node + 1]);
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return INT_MAX;
        if (ql <= l && r <= qr) return st[node];
        int mid = (l + r) / 2;
        return min(query(2 * node, l, mid, ql, qr),
                   query(2 * node + 1, mid + 1, r, ql, qr));
    }

    int rangeMin(int l, int r) {
        if (l > r) return INT_MAX;
        return query(1, 0, n - 1, l, r);
    }
};

int leftFirstSmaller(SegmentTree &seg, vector<int> &arr, int i) {
    int lo = 0, hi = i - 1, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int mn = seg.rangeMin(mid, i - 1);
        if (mn < arr[i]) {
            ans = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    if (ans == -1) return -1;
    for (int j = i - 1; j >= ans; j--) {
        if (arr[j] < arr[i]) return j;
    }
    return -1;
}

int leftLastSmaller(SegmentTree &seg, vector<int> &arr, int i) {
    int lo = 0, hi = i - 1, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int mn = seg.rangeMin(lo, mid);
        if (mn < arr[i]) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    if (ans == -1) return -1;
    for (int j = ans; j <= i - 1; j++) {
        if (arr[j] < arr[i]) return j;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    SegmentTree seg(arr);

    int index;
    cin >> index; // index for which we want LFS and LLS

    int lfs = leftFirstSmaller(seg, arr, index);
    int lls = leftLastSmaller(seg, arr, index);

    cout << "For index " << index << " (value " << arr[index] << "):\n";
    cout << "Left First Smaller (nearest)  = " << lfs << "\n";
    cout << "Left Last Smaller (farthest) = " << lls << "\n";

    return 0;
}
