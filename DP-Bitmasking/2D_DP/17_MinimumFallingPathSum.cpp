/*
Description:
Given a square matrix, find the minimum sum of a falling path. A falling path
starts in any cell of the first row and, at each step, moves to the cell
directly below, diagonally left, or diagonally right in the next row.

Intuition:
For every cell, the best path reaching it depends on the best path starting
from one of its three possible cells in the row below. If we calculate these
values from bottom to top, each cell can reuse already-computed answers.

Approach:
1. Copy the matrix into `dp`, where `dp[i][j]` will store the minimum falling
   path sum starting at cell `(i, j)`.
2. Start from the second-last row and move upward.
3. For each cell, add the minimum of the valid down, down-left, and down-right
   values from the next row.
4. The answer is the minimum value in the first row because a path may start
   at any cell there.

Example:
For matrix:
[
  [2, 1, 3],
  [6, 5, 4],
  [7, 8, 9]
]

After processing from bottom to top:
[
  [14, 13, 15],
  [13, 12, 12],
  [7,  8,  9]
]

The minimum value in the first row is 13, produced by the path 1 -> 5 -> 7.

Time Complexity: O(n * m)
Space Complexity: O(n * m)
*/

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix) {
         int n = matrix.size();
        int m = matrix[0].size();
        vector<vector<int>> dp=matrix;
        for(int i=n-2;i>=0;i--){
            for(int j=0;j<m;j++){
                int down=dp[i+1][j];
                int diagonalLeft=(j>0)?dp[i+1][j-1]:INT_MAX;
                int diagonalRight=(j<m-1)?dp[i+1][j+1]:INT_MAX;
                dp[i][j]+=min({down,diagonalLeft,diagonalRight});

            }
        }
        return *min_element(dp[0].begin(),dp[0].end());
    }
};