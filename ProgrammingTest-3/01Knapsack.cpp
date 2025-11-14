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

