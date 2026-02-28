/**
 * PROBLEM: Unique Paths II
 * -----------------------
 * You are given an n x m grid where:
 *   - 0 represents an empty cell
 *   - 1 represents an obstacle
 *
 * A robot starts at the top-left cell (0, 0)
 * and wants to reach the bottom-right cell (n-1, m-1).
 *
 * The robot can move only:
 *   1. Right
 *   2. Down
 *
 * The robot CANNOT move through obstacles.
 *
 * -------------------------------------------------------
 * KEY OBSERVATION:
 * -------------------------------------------------------
 * If a cell (i, j) contains an obstacle:
 *   - paths(i, j) = 0
 *
 * Otherwise, to reach cell (i, j):
 *   - from above  -> (i - 1, j)
 *   - from left  -> (i, j - 1)
 *
 * So,
 *   paths(i, j) = paths(i - 1, j) + paths(i, j - 1)
 *
 * -------------------------------------------------------
 * BASE CASES:
 * -------------------------------------------------------
 * 1. If start cell (0,0) has an obstacle:
 *    - Answer is 0 (no path exists)
 *
 * 2. Out of bounds:
 *    - Return 0
 *
 * 3. Starting cell without obstacle:
 *    - Exactly 1 path
 *
 * -------------------------------------------------------
 * APPROACH 1: TOP-DOWN DP (MEMOIZATION)
 * -------------------------------------------------------
 * - Use recursion
 * - Store results in dp[][] to avoid recomputation
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(n * m) + recursion stack
 *
 * -------------------------------------------------------
 * APPROACH 2: BOTTOM-UP DP (TABULATION)
 * -------------------------------------------------------
 * - Build solution iteratively
 * - First row & column stop when obstacle appears
 *
 * Time Complexity:  O(n * m)
 * Space Complexity: O(n * m)
 */

 //Memorization

 class Solution {
public:
    int solve(int i, int j, vector<vector<int>> &grid,
              vector<vector<int>> &dp) {

        // out of bounds
        if (i < 0 || j < 0) {
            return 0;
        }

        // obstacle cell
        if (grid[i][j] == 1) {
            return 0;
        }

        // starting cell
        if (i == 0 && j == 0) {
            return 1;
        }

        // memoized value
        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        // compute and store
        dp[i][j] = solve(i - 1, j, grid, dp)
                 + solve(i, j - 1, grid, dp);

        return dp[i][j];
    }

    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();

        // if starting cell is blocked
        if (obstacleGrid[0][0] == 1) {
            return 0;
        }

        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n - 1, m - 1, obstacleGrid, dp);
    }
};

// Tabulation 

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();

        vector<vector<int>> dp(n, vector<int>(m, 0));

        // starting cell
        if (obstacleGrid[0][0] == 1) {
            return 0;
        }
        dp[0][0] = 1;

        // first column
        for (int i = 1; i < n; i++) {
            if (obstacleGrid[i][0] == 0)
                dp[i][0] = dp[i - 1][0];
            else
                dp[i][0] = 0;
        }

        // first row
        for (int j = 1; j < m; j++) {
            if (obstacleGrid[0][j] == 0)
                dp[0][j] = dp[0][j - 1];
            else
                dp[0][j] = 0;
        }

        // fill dp table
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                if (obstacleGrid[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                } else {
                    dp[i][j] = 0;
                }
            }
        }

        return dp[n - 1][m - 1];
    }
};