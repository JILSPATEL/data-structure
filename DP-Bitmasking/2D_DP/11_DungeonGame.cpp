/*
Dungeon Game - Detailed Intuition and Approach

You start at the top-left cell and want to reach the bottom-right cell.
Each cell can add health (positive value) or reduce health (negative value).
The knight must never let health drop to 0 or below at any point.

Key idea:
We do not try to maximize health collected along the way.
Instead, for every cell, we ask:
"What is the minimum health needed when entering this cell so that I can still reach the end safely?"

Why this works:
If we know the minimum health needed for the cell below and the cell to the right,
then for the current cell we only need the smaller of those two requirements,
because we will choose the better path.

Transition:
If the best next cell needs `need` health, and the current cell has value `dungeon[i][j]`,
then the health needed before entering the current cell is:
`max(1, need - dungeon[i][j])`

The `max(1, ...)` part is important because health can never be less than 1.

Example:
Dungeon grid:
[-2, -3,  3]
[-5, -10, 1]
[10,  30, -5]

Start from the destination:
- At `-5`, you need `6` health to survive it and leave with at least `1`.
- Moving backward, each cell computes the minimum health needed based on the best next step.
- At the start cell `-2`, the answer becomes `7`.

So the knight needs at least 7 health initially.

Approach:
1. Use recursion + memoization or bottom-up DP.
2. Let `dp[i][j]` represent the minimum health needed to enter cell `(i, j)`.
3. Fill the table from bottom-right to top-left.
4. Return `dp[0][0]`.

Time complexity: `O(n * m)`
Space complexity: `O(n * m)`
*/

//Memoaization

class Solution {
public:
    vector<vector<int>> dp;
    int n,m;
    int solve(int i,int j,vector<vector<int>>& dungeon){
        if(i>=n || j>=m) return INT_MAX;
        if(i==n-1 && j==m-1){
            return max(1,1-dungeon[i][j]);
        }

        if(dp[i][j]!=-1) return dp[i][j];

        int down=solve(i+1,j,dungeon);
        int right=solve(i,j+1,dungeon);

        int need=min(down,right);
        return dp[i][j]=max(1,need-dungeon[i][j]);
    }
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        n=dungeon.size();
        m=dungeon[0].size();
        dp.assign(n,vector<int>(m,-1));
        return solve(0,0,dungeon);
    }
};


//Tabulation

class Solution {
public:
    vector<vector<int>> dp;
    int n, m;

    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        n = dungeon.size();
        m = dungeon[0].size();
        dp.assign(n, vector<int>(m));
        dp[n - 1][m - 1] = max(1, 1 - dungeon[n - 1][m - 1]);
        for (int i = n - 2; i >= 0; i--) {
            dp[i][m - 1] = max(1, dp[i + 1][m - 1] - dungeon[i][m - 1]);
        }
        for (int i = m - 2; i >= 0; i--) {
            dp[n - 1][i] = max(1, dp[n - 1][i + 1] - dungeon[n - 1][i]);
        }

        for (int i = n - 2; i >= 0; i--) {
            for (int j = m - 2; j >= 0; j--) {
                int need = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(1, need - dungeon[i][j]);
            }
        }
        return dp[0][0];
    }
};