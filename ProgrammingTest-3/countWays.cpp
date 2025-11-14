/**
 * Problem: Count the number of ordered sequences using 2-rupee and 3-rupee coins
 * that sum exactly to N. Order matters. Return result modulo 1e9+7.
 *
 * Recurrence:
 *     ways[n] = ways[n-2] + ways[n-3]   (mod 1e9+7)
 *
 * Sample Input:
 *     5
 *     1
 *     2
 *     3
 *     5
 *     10
 *
 * Sample Output:
 *     0
 *     1
 *     1
 *     2
 *     7
 *
 * Explanation:
 *     N = 5 → sequences: [2+3], [3+2] → answer = 2
 *
 * Complexity:
 *     Time  : O(Nmax + T)
 *     Space : O(Nmax)   // DP array (fits in 40 MB)
 */

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;

    vector<int> queries(T);
    int Nmax = 0;

    for (int i = 0; i < T; i++) {
        cin >> queries[i];
        Nmax = max(Nmax, queries[i]);
    }

    // Allocate DP up to maximum N
    vector<int> dp(Nmax + 1, 0);

    // Base cases
    if (Nmax >= 0) dp[0] = 1;
    if (Nmax >= 1) dp[1] = 0;
    if (Nmax >= 2) dp[2] = 1;
    if (Nmax >= 3) dp[3] = 1;

    // DP computation
    for (int i = 4; i <= Nmax; i++) {
        long long res = dp[i - 2];
        res += dp[i - 3];
        if (res >= MOD) res -= MOD;
        dp[i] = (int)res;
    }

    // Answer queries
    for (int n : queries) {
        cout << dp[n] << "\n";
    }

    return 0;
}
