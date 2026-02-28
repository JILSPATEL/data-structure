/**
 * PROBLEM: Unique Paths
 * --------------------
 * A robot is located at the top-left corner of an n x m grid.
 * The robot can only move:
 *   1. Right
 *   2. Down
 * 
 * The task is to count the total number of unique paths
 * to reach the bottom-right corner.
 *
 * -------------------------------------------------------
 * KEY OBSERVATION:
 * -------------------------------------------------------
 * To reach cell (i, j), the robot must come from:
 *   - (i - 1, j)  -> from above
 *   - (i, j - 1)  -> from left
 *
 * So,
 *   paths(i, j) = paths(i - 1, j) + paths(i, j - 1)
 *
 * -------------------------------------------------------
 * BASE CASES:
 * -------------------------------------------------------
 * 1. Starting cell (0, 0):
 *    - There is exactly 1 way to stay there.
 *
 * 2. Out of bounds (i < 0 or j < 0):
 *    - No valid path, return 0.
 *
 * -------------------------------------------------------
 * APPROACH 1: TOP-DOWN DYNAMIC PROGRAMMING (MEMOIZATION)
 * -------------------------------------------------------
 * - Use recursion to explore all paths.
 * - Use a DP table to store already computed results.
 * - This avoids repeated calculations.
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(n * m) + recursion stack
 *
 * -------------------------------------------------------
 * APPROACH 2: BOTTOM-UP DYNAMIC PROGRAMMING (TABULATION)
 * -------------------------------------------------------
 * - Build the solution iteratively from smaller subproblems.
 * - No recursion is used.
 * - First row and first column always have 1 path.
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(n * m)
 */

//==============================================================
// Top-Down(memorization)
//==============================================================
class Solution {
public:
    int solve(int i, int j, vector<vector<int>> &dp) {
        // base case: starting cell
        if (i == 0 && j == 0) {
            return 1;
        }

        // out of bounds
        if (i < 0 || j < 0) {
            return 0;
        }

        // return cached value
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // compute and store result
        dp[i][j] = solve(i - 1, j, dp) + solve(i, j - 1, dp);
        return dp[i][j];
    }

    int uniquePaths(int n, int m) {
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n - 1, m - 1, dp);
    }
};

//================================================================
// Bottom-Up (Tabulation)
//================================================================
class Solution {
public:
    int uniquePaths(int n, int m) {
        vector<vector<int>> dp(n, vector<int>(m, 0));

        // first row -> only 1 way (move right)
        for (int j = 0; j < m; j++) {
            dp[0][j] = 1;
        }

        // first column -> only 1 way (move down)
        for (int i = 0; i < n; i++) {
            dp[i][0] = 1;
        }

        // fill the DP table
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }

        return dp[n - 1][m - 1];
    }
};