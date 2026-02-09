//Top Down With Memorization

class Solution {
public:
    int solve(vector<vector<int>>& ob, vector<vector<int>>& dp, int i, int j) {
        if (i >= 0 && j >= 0 && ob[i][j] == 1)
            return 0;
        if (i == 0 && j == 0)
            return 1;
        if (i < 0 || j < 0)
            return 0;
        if (dp[i][j] != -1)
            return dp[i][j];
        int up = solve(ob, dp, i, j - 1);
        int left = solve(ob, dp, i - 1, j);
        dp[i][j] = up + left;
        return dp[i][j];
    }
    int uniquePathsWithObstacles(vector<vector<int>>& ob) {
        int n = ob.size();
        int m = ob[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(ob, dp, n - 1, m - 1);
    }
};

//Bottom UP
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& ob) {
        int n = ob.size(), m = ob[0].size();

        vector<int> dp(m, 0);

        if (ob[0][0] == 1) return 0;
        dp[0] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (ob[i][j] == 1) {
                    dp[j] = 0;
                } else if (j > 0) {
                    dp[j] += dp[j - 1];
                }
            }
        }
        return dp[m - 1];
    }
};
