/**
 * Problem: Jump Game V
 * 
 * Given an array arr and an integer d, return the maximum number
 * of indices you can visit.
 *
 * Rules:
 * - From index i, you can jump left or right at most d positions.
 * - You can jump only to an index j where arr[j] < arr[i].
 * - If a greater/equal element appears in between, movement stops.
 *
 * Approaches:
 * 1. Brute Force:
 *    - Try all possible jumps recursively.
 *    - Time: Exponential
 *
 * 2. DP + Memoization (Used Below):
 *    - For every index, compute the maximum jumps possible.
 *    - Store results in dp to avoid recomputation.
 *    - Explore left and right up to distance d.
 *
 * Time Complexity: O(n*d)
 * Space Complexity: O(n)
 */

class Solution {
public:

    int solve(vector<int>& arr, vector<int>& dp, int idx, int d) {
        int n = arr.size();

        // Already computed
        if(dp[idx] != -1)
            return dp[idx];

        int ans = 1; // Current index itself

        // Explore left side
        for(int i = idx - 1; i >= max(0, idx - d); i--) {
            
            // Stop if greater/equal element blocks path
            if(arr[i] >= arr[idx])
                break;

            ans = max(ans, 1 + solve(arr, dp, i, d));
        }

        // Explore right side
        for(int i = idx + 1; i <= min(n - 1, idx + d); i++) {

            // Stop if greater/equal element blocks path
            if(arr[i] >= arr[idx])
                break;

            ans = max(ans, 1 + solve(arr, dp, i, d));
        }

        return dp[idx] = ans;
    }

    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();

        vector<int> dp(n, -1);

        int ans = 0;

        for(int i = 0; i < n; i++) {
            ans = max(ans, solve(arr, dp, i, d));
        }

        return ans;
    }
};