/*
This code finds the maximum subarray sum when we are allowed to remove at most one element.

Approach:
- We use DFS + memoization (dynamic programming) to explore all valid choices.
- The three important states are:
  1. idx -> current index in the array
  2. canSkip -> whether we still have the option to delete one element
  3. started -> whether we have already started a subarray

Meaning of the DP:
- If we have not started a subarray yet, we can either skip the element or start a new subarray.
- If we are already inside a subarray, we can either continue it, end it, or remove one element if allowed.
- We use max(0, nextValue) so that negative sums do not reduce the best answer.
*/

class Solution {
public:
    const int NEG = -1e9;

    int solve(int idx, vector<int>& arr,
              vector<vector<vector<int>>>& dp,
              int canSkip, int started) {

        int n = arr.size();

        if (idx == n) {
            return started ? 0 : NEG;
        }

        if (dp[idx][canSkip][started] != NEG)
            return dp[idx][canSkip][started];

        int ans = NEG;

        if (!started) {
            // Skip current index before starting the subarray
            ans = max(ans, solve(idx + 1, arr, dp, canSkip, 0));

            // Start subarray from current index
            ans = max(ans,
                      arr[idx] + max(0, solve(idx + 1, arr, dp, canSkip, 1)));
        } else {
            // End subarray here
            ans = max(ans, 0);

            // Take current element
            ans = max(ans,
                      arr[idx] + max(0, solve(idx + 1, arr, dp, canSkip, 1)));

            // Skip current element if deletion is available
            if (canSkip)
                ans = max(ans,
                          max(0, solve(idx + 1, arr, dp, 0, 1)));
        }

        return dp[idx][canSkip][started] = ans;
    }

    int maxSumSubarray(vector<int>& arr) {
        int n = arr.size();

        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(2, vector<int>(2, NEG)));

        return solve(0, arr, dp, 1, 0);
    }
};