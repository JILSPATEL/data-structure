#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    int n;
    vector<int> st;  // stores index of max element

    SegmentTree(vector<int>& A) {
        n = A.size();
        st.resize(4 * n);
        build(A, 0, n - 1, 0);
    }

    void build(vector<int>& A, int ss, int se, int si) {
        if (ss == se) {
            st[si] = ss;
            return;
        }
        int mid = (ss + se) / 2;
        build(A, ss, mid, 2 * si + 1);
        build(A, mid + 1, se, 2 * si + 2);

        int l = st[2 * si + 1];
        int r = st[2 * si + 2];
        st[si] = (A[l] > A[r] ? l : r);   // store index of max
    }

    // ✅ Right First Greater (RFG)
    int rightFirstGreater(vector<int>& A, int j) {
        int ss = 0, se = n - 1, si = 0;
        if (j >= n - 1) return -1;  // nothing to the right

        // restrict search to right side
        ss = j + 1;

        while (ss != se) {
            int mid = (ss + se) / 2;
            int leftIdx = st[2 * si + 1];

            if (mid >= j + 1 && A[leftIdx] > A[j]) {
                // go left
                se = mid;
                si = 2 * si + 1;
            } else {
                // go right
                ss = mid + 1;
                si = 2 * si + 2;
            }
        }
        if (A[ss] > A[j] && ss > j) return ss;
        return -1;
    }

    // ✅ Right Last Greater (RLG)
    int rightLastGreater(vector<int>& A, int j) {
        int ss = 0, se = n - 1, si = 0;
        if (j >= n - 1) return -1;

        ss = j + 1;

        while (ss != se) {
            int mid = (ss + se) / 2;
            int rightIdx = st[2 * si + 2];

            if (mid + 1 <= se && A[rightIdx] > A[j]) {
                // go right
                ss = mid + 1;
                si = 2 * si + 2;
            } else {
                // go left
                se = mid;
                si = 2 * si + 1;
            }
        }
        if (A[ss] > A[j] && ss > j) return ss;
        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];

    int j;
    cin >> j;

    SegmentTree st(A);

    int rfg = st.rightFirstGreater(A, j);
    int rlg = st.rightLastGreater(A, j);

    cout << "RFG = " << rfg << "\n";
    cout << "RLG = " << rlg << "\n";

    return 0;
}

