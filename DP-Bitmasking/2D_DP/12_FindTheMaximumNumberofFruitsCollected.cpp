/*
Find the Maximum Number of Fruits Collected - Detailed Intuition and Approach

Description:
We are given an n x n grid of fruits. Three children collect fruits at the same time:
1. Child 1 moves along the main diagonal from top-left to bottom-right.
2. Child 2 starts from the top-right corner and moves only in the upper triangle.
3. Child 3 starts from the bottom-left corner and moves only in the lower triangle.

The goal is to maximize the total number of fruits collected by all three children.
Since child 1 always follows the diagonal, that contribution is fixed.
The real challenge is to find the best paths for child 2 and child 3 without crossing the diagonal or overlapping incorrectly.

Intuition:
The grid can be split into three regions:
- The diagonal cells are reserved for child 1.
- The cells above the diagonal are handled by child 2.
- The cells below the diagonal are handled by child 3.

For child 2, every move goes from one row to the next, and the column can change by -1, 0, or +1.
For child 3, every move goes toward the right, while the row can change by -1, 0, or +1.

This makes the problem suitable for dynamic programming:
- For each position, ask for the maximum fruits that can be collected starting from that cell.
- Since the future only depends on the current cell and the next valid moves, memoization or tabulation works well.

Why DP works:
At each cell, the child has only a few valid transitions.
So instead of exploring all paths repeatedly, we store the best answer for every state.
This avoids recomputation and turns an exponential search into a polynomial solution.

Approach:
1. Child 1 is simple: sum all diagonal values, because the path is fixed.
2. For child 2, use DP over cells where i < j.
    - From (i, j), the next move can be (i+1, j-1), (i+1, j), or (i+1, j+1).
    - Take the maximum valid result among those moves.
3. For child 3, use DP over cells where i > j.
    - From (i, j), the next move can be (i-1, j+1), (i, j+1), or (i+1, j+1).
    - Again, take the maximum valid result.
4. Add the three contributions to get the final answer.

Example:
Consider this 3 x 3 grid:

1  2  3
4  5  6
7  8  9

Child 1 collects the diagonal:
1 + 5 + 9 = 15

Child 2 starts at the top-right cell 3 and tries to stay above the diagonal.
It chooses the best downward path among the allowed moves.

Child 3 starts at the bottom-left cell 7 and tries to stay below the diagonal.
It chooses the best rightward path among the allowed moves.

The final answer is:
diagonal sum + best upper-triangle path + best lower-triangle path

Time complexity:
O(n^2)

Space complexity:
O(n^2)
*/

//Memoization

class Solution {
public:
    int n;
    vector<vector<int>> dp;
    int child1(vector<vector<int>>& fruits){
        int count = 0;
        for(int i = 0; i < n; i++)
            count += fruits[i][i];
        return count;
    }

    int child2(int i, int j, vector<vector<int>>& fruits){
        if(i >= n || j < 0 || j >= n) return -1e9;
        if(i == n-1 && j == n-1) return 0;
        if(i >= j) return -1e9;
        if(dp[i][j]!=-1) return dp[i][j];
        int bottomL = fruits[i][j] + child2(i+1, j-1, fruits);
        int bottomD = fruits[i][j] + child2(i+1, j, fruits);
        int bottomR = fruits[i][j] + child2(i+1, j+1, fruits);

        return dp[i][j]=max({bottomL, bottomD, bottomR});
    }

    int child3(int i, int j, vector<vector<int>>& fruits){
        if(i < 0 || i >= n || j < 0 || j >= n) return -1e9;
        if(i == n-1 && j == n-1) return 0;
        if(i <= j) return -1e9;
        if(dp[i][j]!=-1) return dp[i][j];
        int upR = fruits[i][j] + child3(i-1, j+1, fruits);
        int right = fruits[i][j] + child3(i, j+1, fruits);
        int bottomR = fruits[i][j] + child3(i+1, j+1, fruits);

        return dp[i][j]=max({upR, right, bottomR});
    }

    int maxCollectedFruits(vector<vector<int>>& fruits) {
        n = fruits.size();
        dp.assign(n,vector<int>(n,-1));
        int c1 = child1(fruits);
        int c2 = child2(0, n-1, fruits);
        int c3 = child3(n-1, 0, fruits);

        return c1 + c2 + c3;
    }
};

//Tabulation

class Solution {
public:
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        vector<vector<int>> dp1(n, vector<int>(n, 0));
        vector<vector<int>> dp2(n, vector<int>(n, 0));
        vector<vector<int>> dp3(n, vector<int>(n, 0));

        // Child 1
        for (int i = 0; i < n; i++) {
            dp1[i][i] = fruits[i][i];
        }

        // Child 2
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i >= j) continue;
                int bottomL = (i + 1 < n && j - 1 >= 0) ? dp2[i + 1][j - 1] : -1e9;
                int bottomD = (i + 1 < n) ? dp2[i + 1][j] : -1e9;
                int bottomR = (i + 1 < n && j + 1 < n) ? dp2[i + 1][j + 1] : -1e9;
                dp2[i][j] = fruits[i][j] + max({bottomL, bottomD, bottomR});
            }
        }

        // Child 3
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (i <= j) continue;
                int upR = (i - 1 >= 0 && j + 1 < n) ? dp3[i - 1][j + 1] : -1e9;
                int right = (j + 1 < n) ? dp3[i][j + 1] : -1e9;
                int bottomR = (i + 1 < n && j + 1 < n) ? dp3[i + 1][j + 1] : -1e9;
                dp3[i][j] = fruits[i][j] + max({upR, right, bottomR});
            }
        }

        return accumulate(dp1.begin(), dp1.end(), 0) + accumulate(dp2.begin(), dp2.end(), 0) + accumulate(dp3.begin(), dp3.end(), 0);
    }