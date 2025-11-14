/**
 * ---------------- PROBLEM 5: Dual-Weighted Cargo (2D Knapsack) ----------------
 *
 * You have n items, each with:
 *    • mass        = w1[i]
 *    • volume      = w2[i]
 *    • profit      = v[i]
 *
 * Space ship limits:
 *    • total mass   ≤ W1
 *    • total volume ≤ W2
 *
 * Goal: Maximize total profit without exceeding limits.
 *
 * Constraints:
 *   1 ≤ t ≤ 1000
 *   1 ≤ n ≤ 1e6
 *   Sum(w1[i] * w2[i] * n) ≤ 1e6   → DP is feasible
 *
 * ---------------------------- Sample Input ----------------------------
 * 2
 * 3 10 8
 * 4 3 8
 * 5 4 10
 * 8 6 15
 * 2 6 5
 * 2 3 4
 * 4 4 7
 *
 * ---------------------------- Sample Output ---------------------------
 * 18
 * 11
 *
 * ----------------------------------------------------------------------
 * ---------------------- Time & Space Complexity -----------------------
 * Time Complexity  : O(n * W1 * W2)
 * Space Complexity : O(W1 * W2)
 * ----------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while(T--){
        int n, W1, W2;
        cin >> n >> W1 >> W2;

        vector<int> w1(n), w2(n), val(n);
        for(int i = 0; i < n; i++)
            cin >> w1[i] >> w2[i] >> val[i];

        vector<vector<int>> dp(W1+1, vector<int>(W2+1, 0));

        for(int i = 0; i < n; i++){
            for(int m = W1; m >= w1[i]; m--){
                for(int v = W2; v >= w2[i]; v--){
                    dp[m][v] = max(dp[m][v],
                                   dp[m - w1[i]][v - w2[i]] + val[i]);
                }
            }
        }

        cout << dp[W1][W2] << "\n";
    }
    return 0;
}
