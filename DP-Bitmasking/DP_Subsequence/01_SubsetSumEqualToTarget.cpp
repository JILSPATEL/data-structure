/**
 * Problem: Subset Sum Problem
 *
 * Given an array of integers `arr[]` and an integer `sum`,
 * determine whether there exists a subset of the array
 * such that the sum of its elements is exactly equal to `sum`.
 *
 * ---------------------------------------------------------
 * APPROACH: MEMOIZATION (TOP-DOWN DYNAMIC PROGRAMMING)
 * ---------------------------------------------------------
 *
 * Idea:
 * We use recursion to explore all possibilities of either
 * taking or skipping each element. To avoid recomputation,
 * results are stored in a DP table.
 *
 * State Definition:
 * solve(idx, tar):
 *   - idx → current index in the array
 *   - tar → remaining target sum
 *
 * Base Cases:
 * 1. If tar == 0 → subset found → return true
 * 2. If idx == n or tar < 0 → not possible → return false
 *
 * Transition:
 * - take = solve(idx+1, tar - arr[idx])
 * - skip = solve(idx+1, tar)
 *
 * Memo Table:
 * dp[idx][tar] stores whether sum `tar`
 * is possible using elements from index `idx` onward.
 *
 * Time Complexity: O(n × sum)
 * Space Complexity: O(n × sum) + recursion stack
 */

class Solution {
public:
    bool solve(int idx, int n, vector<int>& arr, int tar,
               vector<vector<int>>& dp) {
        if (tar == 0) return true;
        if (idx == n || tar < 0) return false;

        if (dp[idx][tar] != -1)
            return dp[idx][tar];

        bool take = solve(idx + 1, n, arr, tar - arr[idx], dp);
        bool skip = solve(idx + 1, n, arr, tar, dp);

        return dp[idx][tar] = take || skip;
    }

    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
        return solve(0, n, arr, sum, dp);
    }
};


/**
 * Problem: Subset Sum Problem
 *
 * Given an array of integers `arr[]` and an integer `sum`,
 * determine whether there exists a subset of the array
 * whose elements add up exactly to `sum`.
 *
 * ---------------------------------------------------------
 * APPROACH: TABULATION (BOTTOM-UP DYNAMIC PROGRAMMING)
 * ---------------------------------------------------------
 *
 * Idea:
 * Build a DP table iteratively where each state represents
 * whether a sum can be achieved using the first `i` elements.
 *
 * State Definition:
 * dp[i][s] = true if sum `s` can be formed using
 *            the first `i` elements.
 *
 * Initialization:
 * - dp[i][0] = true (sum 0 is always possible)
 * - dp[0][s] = false for s > 0 (no elements)
 *
 * Transition:
 * dp[i][s] = dp[i-1][s] (skip element)
 *         OR dp[i-1][s - arr[i-1]] (take element)
 *
 * Final Answer:
 * dp[n][sum]
 *
 * Time Complexity: O(n × sum)
 * Space Complexity: O(n × sum)
 */

class Solution {
public:
    bool isSubsetSum(vector<int>& arr, int sum) {
        int n = arr.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));

        // Base case: sum = 0
        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        // Fill DP table
        for (int i = 1; i <= n; i++) {
            for (int s = 1; s <= sum; s++) {
                bool skip = dp[i - 1][s];
                bool take = false;
                if (s >= arr[i - 1])
                    take = dp[i - 1][s - arr[i - 1]];
                dp[i][s] = take || skip;
            }
        }

        return dp[n][sum];
    }
};