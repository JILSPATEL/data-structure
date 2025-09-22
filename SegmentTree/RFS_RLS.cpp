/*
6
5 2 6 1 3 7
2
For index 2 (value 6):
Right First Smaller (nearest)  = 3
Right Last Smaller (farthest) = 4
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

// Right First Smaller (nearest on right)
int rightFirstSmaller(SegmentTree &seg, vector<int> &arr, int i) {
    int lo = i + 1, hi = arr.size() - 1, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int mn = seg.rangeMin(i + 1, mid);
        if (mn < arr[i]) {
            ans = mid;
            hi = mid - 1; // try closer to i
        } else {
            lo = mid + 1;
        }
    }
    if (ans == -1) return -1;
    for (int j = i + 1; j <= ans; j++) {
        if (arr[j] < arr[i]) return j;
    }
    return -1;
}

// Right Last Smaller (farthest on right)
int rightLastSmaller(SegmentTree &seg, vector<int> &arr, int i) {
    int lo = i + 1, hi = arr.size() - 1, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int mn = seg.rangeMin(mid, hi);
        if (mn < arr[i]) {
            ans = mid;
            lo = mid + 1; // expand to the right
        } else {
            hi = mid - 1;
        }
    }
    if (ans == -1) return -1;
    for (int j = arr.size() - 1; j >= ans; j--) {
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
    cin >> index; // index for which we want RFS and RLS

    int rfs = rightFirstSmaller(seg, arr, index);
    int rls = rightLastSmaller(seg, arr, index);

    cout << "For index " << index << " (value " << arr[index] << "):\n";
    cout << "Right First Smaller (nearest)  = " << rfs << "\n";
    cout << "Right Last Smaller (farthest) = " << rls << "\n";

    return 0;
}
