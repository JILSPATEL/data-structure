/*
Problem: Maximum Non-Negative Product in a Matrix

Given an n x m integer grid, you start at the top-left cell and can only move either down or right at any point in time. The product of all numbers along a path is the path product. Return the maximum non-negative product that can be obtained from any path from the top-left to the bottom-right cell. If the maximum product is negative, return -1. Return the result modulo 10^9 + 7 when non-negative.

Key intuition:
- Products can become large and their sign matters. A negative value may become positive later when multiplied by another negative.
- For each cell we must therefore track both the maximum product and the minimum product achievable up to that cell. The minimum is important because multiplying two negatives can yield a larger positive.

Approach (DP tracking max and min at each cell):
- Let dp_max[i][j] = maximum product achievable from cell (i,j) to the destination following allowed moves.
- Let dp_min[i][j] = minimum product achievable from cell (i,j) to the destination.
- Transition: from (i,j) you can move down or right. Suppose the current cell value is v and from a neighbour we have its max and min. Multiplying v by neighbour's max or min can produce candidates; take the maximum of candidates for dp_max and the minimum for dp_min.
- Base: at bottom-right, both max and min equal grid[n-1][m-1]. Compute either via recursion+memoization or bottom-up tabulation.

Complexities:
- Time: O(n*m) since each cell computes fixed amount of work.
- Space: O(n*m) for DP arrays (or O(1) extra if optimized in-place along a row/column).

Worked example (walkthrough):
Grid:
    [ 1, -2,  1 ]
    [ 1, -2, -1 ]
    [ 3, -4,  1 ]

Start from bottom-right: dp(2,2) = (1,1).
Consider cell (2,1) value = -4: only right neighbor (2,2) with (max=1,min=1).
    candidates: -4*1 = -4 (both), so dp(2,1) = (max=-4, min=-4).
Cell (1,2) value = -1: down neighbor (2,2) => -1*1 = -1, so dp(1,2) = (-1,-1).
Cell (1,1) value = -2: right (1,2)=(-1,-1), down (2,1)=(-4,-4)
    candidates: -2 * -1 = 2, -2 * -4 = 8 -> dp_max=8, dp_min=min(2,8) = 2 (but actual min may be different in other examples).

Final answer is dp_max[0][0] if non-negative (mod 1e9+7), otherwise -1.

This file contains two implementations: memoized recursion and iterative tabulation using the same max/min idea.
*/

// Memoaization

class Solution
{
public:
    int n, m;
    typedef long long ll;
    const int MOD = 1000000007;
    vector<vector<pair<ll, ll>>> dp;
    pair<ll, ll> solve(int i, int j, vector<vector<int>> &grid)
    {
        if (i == n - 1 && j == m - 1)
        {
            return {grid[i][j], grid[i][j]};
        }
        ll maxVal = LLONG_MIN;
        ll minVal = LLONG_MAX;
        if (dp[i][j] != make_pair(LLONG_MIN, LLONG_MAX))
            return dp[i][j];
        if (i + 1 < n)
        {
            auto [downMax, downMin] = solve(i + 1, j, grid);
            maxVal = max({maxVal, grid[i][j] * downMax, grid[i][j] * downMin});
            minVal = min({minVal, grid[i][j] * downMax, grid[i][j] * downMin});
        }
        if (j + 1 < m)
        {
            auto [rightMax, rightMin] = solve(i, j + 1, grid);
            maxVal = max({maxVal, grid[i][j] * rightMax, grid[i][j] * rightMin});
            minVal = min({minVal, grid[i][j] * rightMax, grid[i][j] * rightMin});
        }
        return dp[i][j] = {maxVal, minVal};
    }
    int maxProductPath(vector<vector<int>> &grid)
    {
        n = grid.size();
        m = grid[0].size();
        dp.assign(n, vector<pair<ll, ll>>(m, {LLONG_MIN, LLONG_MAX}));
        auto [maxProd, minProd] = solve(0, 0, grid);
        return maxProd < 0 ? -1 : maxProd % MOD;
    }
};

//Tabulation

class Solution
{
public:
    int n, m;
    typedef long long ll;
    const int MOD = 1000000007;
    int maxProductPath(vector<vector<int>> &grid)
    {
        n = grid.size();
        m = grid[0].size();
        vector<vector<pair<ll, ll>>> dp(n, vector<pair<ll, ll>>(m, {LLONG_MIN, LLONG_MAX}));
        dp[n - 1][m - 1] = {grid[n - 1][m - 1], grid[n - 1][m - 1]};
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                if (i + 1 < n)
                {
                    auto [downMax, downMin] = dp[i + 1][j];
                    dp[i][j].first = max({dp[i][j].first, grid[i][j] * downMax, grid[i][j] * downMin});
                    dp[i][j].second = min({dp[i][j].second, grid[i][j] * downMax, grid[i][j] * downMin});
                }
                if (j + 1 < m)
                {
                    auto [rightMax, rightMin] = dp[i][j + 1];
                    dp[i][j].first = max({dp[i][j].first, grid[i][j] * rightMax, grid[i][j] * rightMin});
                    dp[i][j].second = min({dp[i][j].second, grid[i][j] * rightMax, grid[i][j] * rightMin});
                }
            }
        }
        return dp[0][0].first < 0 ? -1 : dp[0][0].first % MOD;
    }
};