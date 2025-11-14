/**
 * Count Ways (Medium Version)
 * 
 * Problem: Count ordered sequences of 2 and 3 rupee coins that sum to exactly N rupees.
 * Order matters - different sequences are counted separately.
 * 
 * Constraints: 1 ≤ N ≤ 10^7, 1 ≤ T, sum of all N ≤ 10^7
 * Memory Limit: 16 MB
 * 
 * Sample Input:
 * 5
 * 1
 * 2
 * 3
 * 5
 * 10
 * 
 * Sample Output:
 * 0
 * 1
 * 1
 * 2
 * 7
 * 
 * Approach:
 * Let dp[i] = number of ordered sequences to make i rupees
 * Recurrence: dp[i] = dp[i-2] + dp[i-3]
 * Base cases: dp[0] = 1, dp[1] = 0, dp[2] = 1, dp[3] = 1
 * 
 * Due to memory constraints (16MB), we process all test cases together
 * and compute DP values only up to maximum N.
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    // Read all test cases and find maximum N
    vector<int> queries(T);
    int maxN = 0;
    for (int i = 0; i < T; i++) {
        cin >> queries[i];
        maxN = max(maxN, queries[i]);
    }
    
    // Handle edge case
    if (maxN == 0) {
        for (int i = 0; i < T; i++) {
            cout << (queries[i] == 0 ? 1 : 0) << "\n";
        }
        return 0;
    }
    
    // DP array - we only need to store up to maxN
    vector<int> dp(maxN + 1, 0);
    
    // Base cases
    if (maxN >= 0) dp[0] = 1;
    if (maxN >= 2) dp[2] = 1;
    if (maxN >= 3) dp[3] = 1;
    
    // Fill DP table
    for (int i = 4; i <= maxN; i++) {
        dp[i] = (dp[i-2] + dp[i-3]) % MOD;
    }
    
    // Output results for each query
    for (int i = 0; i < T; i++) {
        cout << dp[queries[i]] << "\n";
    }
    
    return 0;
}