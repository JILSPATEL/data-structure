/*
Problem: 64. Minimum Path Sum

You are given an m x n grid.
- Each cell contains a non-negative number (cost).
- You start at the top-left cell (0,0).
- You want to reach the bottom-right cell (m-1, n-1).
- You are allowed to move ONLY:
    1) Right
    2) Down

Goal:
Find the minimum possible sum of numbers along any valid path
from start to destination.

--------------------------------------------------
Key Observations:
1. Since you can only move right or down, there are no cycles.
2. To reach any cell (i, j), you must come from:
      - top cell (i-1, j) OR
      - left cell (i, j-1)
3. The minimum path sum to a cell depends on the minimum
   path sum of its previous reachable cells.

--------------------------------------------------
Dynamic Programming Idea:
Let dp[i][j] = minimum path sum to reach cell (i, j).

Transition:
dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])

--------------------------------------------------
Base Cases:
1. dp[0][0] = grid[0][0]
   (Starting cell, no previous cost)

2. First row (i = 0):
   Can only come from the left
   dp[0][j] = dp[0][j-1] + grid[0][j]

3. First column (j = 0):
   Can only come from the top
   dp[i][0] = dp[i-1][0] + grid[i][0]

--------------------------------------------------
Example:
grid = [
  [1, 3, 1],
  [1, 5, 1],
  [4, 2, 1]
]

dp table becomes:
[
  [1, 4, 5],
  [2, 7, 6],
  [6, 8, 7]
]

Answer = dp[2][2] = 7

Path:
1 → 3 → 1 → 1 → 1

--------------------------------------------------
Time Complexity:
O(m * n)
(Each cell computed once)

Space Complexity:
O(m * n)
(Can be optimized to O(n) using one row)

--------------------------------------------------
Final Result:
Return dp[m-1][n-1] as the minimum path sum.
*/


//========================================
// Memorization
//========================================

class Solution {
  public:
    int solve(int i,int j,vector<vector<int>>&grid,vector<vector<int>> &dp){
        int n=grid.size();
        int m=grid[0].size();
        if(i>=n||j>=m) return INT_MAX;
        if(i==n-1 && j==m-1){
            return grid[i][j];
        }
        if(dp[i][j]!=-1) return dp[i][j];
        int right=solve(i,j+1,grid,dp);
        int down=solve(i+1,j,grid,dp);
        return dp[i][j]=grid[i][j]+min(right,down);
    }
    int minPathSum(vector<vector<int>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<int>>dp(n,vector<int>(m,-1));
        return solve(0,0,grid,dp);
    }
};

//========================================
// Tabulation
//========================================

class Solution {
public:

    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(i==0 && j==0) continue;
                else if(i==0) grid[i][j]+=grid[i][j-1];
                else if(j==0) grid[i][j]+=grid[i-1][j];
                else grid[i][j]+=min(grid[i][j-1],grid[i-1][j]);
            }
        }
        return grid[m-1][n-1];
    }
};