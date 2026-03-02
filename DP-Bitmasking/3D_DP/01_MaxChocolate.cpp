/**
 * Problem Description:
 * --------------------
 * You are given a grid of size n x m where each cell contains some chocolates.
 * Two robots start at the top row (row 0):
 *   - Robot 1 starts at column 0
 *   - Robot 2 starts at column m-1
 *
 * Both robots need to move from the top row to the bottom row (row n-1).
 * At each step, both robots move simultaneously to the next row (i + 1).
 *
 * From position (i, j), a robot can move to:
 *   - (i+1, j-1)
 *   - (i+1, j)
 *   - (i+1, j+1)
 *
 * Rules for collecting chocolates:
 *   - If both robots land on the same cell, chocolates from that cell are
 *     counted only once.
 *   - Otherwise, chocolates from both cells are added.
 *
 * Objective:
 * ----------
 * Maximize the total number of chocolates collected by both robots by the time
 * they reach the last row.
 *
 * Approach (Dynamic Programming + Recursion):
 * -------------------------------------------
 * We use a 3D DP array dp[i][j1][j2], where:
 *   - i   = current row
 *   - j1  = column of robot 1
 *   - j2  = column of robot 2
 *
 * dp[i][j1][j2] stores the maximum chocolates collectable from row i to the end
 * when robot 1 is at column j1 and robot 2 is at column j2.
 *
 * Base Cases:
 * -----------
 * 1. If j1 or j2 goes out of grid bounds → return a very small value (-1e9).
 * 2. If we are at the last row:
 *      - If j1 == j2 → return grid[i][j1]
 *      - Else        → return grid[i][j1] + grid[i][j2]
 *
 * Recursive Transition:
 * ---------------------
 * For the current state (i, j1, j2), try all 9 possible moves of both robots
 * (dj1 from -1 to 1 and dj2 from -1 to 1).
 *
 * Take the maximum result among all valid transitions.
 *
 * Time Complexity:
 * ----------------
 * O(n * m * m * 9) ≈ O(n * m^2)
 *
 * Space Complexity:
 * -----------------
 * O(n * m * m) for the DP table.
 */

class Solution {
public:
    int solve(int i, int j1, int j2, int n, int m,
              vector<vector<int>>& grid,
              vector<vector<vector<int>>>& dp) {

        // Boundary check
        if (j1 < 0 || j1 >= m || j2 < 0 || j2 >= m)
            return -1e9;

        // Base case: last row
        if (i == n - 1) {
            if (j1 == j2)
                return grid[i][j1];
            else
                return grid[i][j1] + grid[i][j2];
        }

        // Memoization check
        if (dp[i][j1][j2] != -1)
            return dp[i][j1][j2];

        int maxi = -1e9;

        // Current chocolates collected at row i
        int curr = (j1 == j2) ? grid[i][j1]
                              : grid[i][j1] + grid[i][j2];

        // Explore all 9 movement combinations
        for (int dj1 = -1; dj1 <= 1; dj1++) {
            for (int dj2 = -1; dj2 <= 1; dj2++) {
                int ans = curr + solve(i + 1, j1 + dj1, j2 + dj2,
                                       n, m, grid, dp);
                maxi = max(maxi, ans);
            }
        }

        return dp[i][j1][j2] = maxi;
    }

    int maxChocolate(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<vector<int>>> dp(
            n, vector<vector<int>>(m, vector<int>(m, -1))
        );

        // Robot 1 starts at column 0, Robot 2 at column m-1
        return solve(0, 0, m - 1, n, m, grid, dp);
    }
};