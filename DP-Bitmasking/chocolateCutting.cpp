#include <bits/stdc++.h>
using namespace std;

/*
   Chocolate Cutting Problem (Bitmask DP)
   --------------------------------------
   Given n nuts/pieces on a chocolate grid (H x W),
   Each nut i is at (x[i], y[i]).
   The cost of cutting a chocolate piece = area of that piece.
   We can cut it into smaller parts along grid lines
   as long as we separate the nuts cleanly.
   Goal: Minimize total cutting cost.

   Constraints:
     h, w <= 100
     n <= 15

   Time Complexity: O(3^n)
   Space Complexity: O(2^n)
*/

struct Point {
    int x, y;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W, N;
    cin >> H >> W >> N;

    vector<Point> nuts(N);
    for (int i = 0; i < N; ++i) cin >> nuts[i].x >> nuts[i].y;

    int totalMasks = 1 << N;
    vector<int> minX(totalMasks), maxX(totalMasks), minY(totalMasks), maxY(totalMasks);

    // Precompute bounding box for every subset of nuts
    for (int mask = 1; mask < totalMasks; ++mask) {
        int x1 = H, x2 = 1, y1 = W, y2 = 1;
        for (int i = 0; i < N; ++i) {
            if (mask & (1 << i)) {
                x1 = min(x1, nuts[i].x);
                x2 = max(x2, nuts[i].x);
                y1 = min(y1, nuts[i].y);
                y2 = max(y2, nuts[i].y);
            }
        }
        minX[mask] = x1;
        maxX[mask] = x2;
        minY[mask] = y1;
        maxY[mask] = y2;
    }

    // dp[mask] = minimum cost to cut chocolate containing subset 'mask' of nuts
    vector<int> dp(totalMasks, INT_MAX);

    // Base case: single nut -> cost = area of that 1x1 square
    for (int i = 0; i < N; ++i) {
        int m = 1 << i;
        dp[m] = 1; // area of 1 cell (each nut alone)
    }

    // DP: Compute cost for all subsets
    for (int mask = 1; mask < totalMasks; ++mask) {
        int width = maxX[mask] - minX[mask] + 1;
        int height = maxY[mask] - minY[mask] + 1;
        int area = width * height;

        // Try splitting this subset into two non-empty submasks
        for (int sub = (mask - 1) & mask; sub > 0; sub = (sub - 1) & mask) {
            int other = mask ^ sub;
            dp[mask] = min(dp[mask], dp[sub] + dp[other] + area);
        }

        // If single nut, ensure base area is counted
        if (__builtin_popcount(mask) == 1)
            dp[mask] = area;
    }

    cout << "✅ Minimum cutting cost = " << dp[totalMasks - 1] << "\n";
    return 0;
}


/*
input:
10 10 3
2 2
4 3
9 9

output:
Minimum cutting cost = 73
*/

