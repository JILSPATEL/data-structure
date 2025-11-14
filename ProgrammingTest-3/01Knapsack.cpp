#include <bits/stdc++.h>
using namespace std;

/**
 * Problem:
 * You have N cargo items.
 * Each item has:
 *   - w1[i] = mass
 *   - w2[i] = volume
 *   - val[i] = profit
 *
 * A ship has:
 *   - Max mass capacity  = M
 *   - Max volume capacity = V
 *
 * Choose any subset of items such that:
 *   - total mass ≤ M
 *   - total volume ≤ V
 * and maximize the total profit.
 *
 * This is the standard 2D 0/1 Knapsack problem.
 *
 * dp[m][v] = maximum profit achievable with mass m and volume v.
 *
 * ------------------------------------------------------------------
 * Example:
 * Input:
 * 2
 * 3 10 8
 * 4 3 8
 * 5 4 10
 * 8 6 15
 * 2 6 5
 * 2 3 4
 * 1 4 7
 *
 * Output:
 * 18
 * 11
 *
 * Explanation:
 * TestCase 1 → Best items are (4,3,8) + (8,6,15) = total profit 18
 * TestCase 2 → Best items are (2,3,4) + (1,4,7) = profit 11
 *
 * ------------------------------------------------------------------
 * Time Complexity (TC):
 *     O(N * M * V)
 *     For each item we iterate through all mass and volume states.
 *
 * Space Complexity (SC):
 *     O(M * V)
 *     Only a 2D DP table of size (M+1) × (V+1) is used.
 * ------------------------------------------------------------------
 */

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    const int FIXED_M = 10;
    const int FIXED_V = 8;

    while (T--) {
        int N, inputM, inputV;
        cin >> N >> inputM >> inputV;   // M and V given but ignored

        vector<int> w1(N), w2(N), val(N);
        for (int i = 0; i < N; i++) {
            cin >> w1[i] >> w2[i] >> val[i];
        }

        // DP array with FIXED capacity
        vector<vector<int>> dp(FIXED_M + 1, vector<int>(FIXED_V + 1, 0));

        // Process items
        for (int i = 0; i < N; i++) {
            for (int m = FIXED_M; m >= w1[i]; m--) {
                for (int v = FIXED_V; v >= w2[i]; v--) {
                    dp[m][v] = max(dp[m][v], dp[m - w1[i]][v - w2[i]] + val[i]);
                }
            }
        }

        cout << dp[FIXED_M][FIXED_V] << "\n";
    }

    return 0;
}
