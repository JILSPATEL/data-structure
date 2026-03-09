/**
 * Problem: Edit Distance
 *
 * Given two strings word1 and word2, return the minimum number of
 * operations required to convert word1 into word2.
 *
 * Allowed operations:
 * 1. Insert a character
 * 2. Delete a character
 * 3. Replace a character
 *
 * Example:
 * word1 = "horse"
 * word2 = "ros"
 *
 * Output: 3
 *
 * Explanation:
 * horse -> rorse (replace h with r)
 * rorse -> rose (delete r)
 * rose  -> ros (delete e)
 *
 * ------------------------------------------------------------
 * Memoization Idea (Top Down DP)
 *
 * Let solve(i, j) represent the minimum operations required
 * to convert:
 *
 * word1[0..i] → word2[0..j]
 *
 * Base Cases:
 *
 * If i < 0
 *      word1 exhausted
 *      Need to insert remaining (j + 1) characters
 *
 * If j < 0
 *      word2 exhausted
 *      Need to delete remaining (i + 1) characters
 *
 * ------------------------------------------------------------
 * Transition
 *
 * If word1[i] == word2[j]
 *      No operation required
 *      move diagonally
 *
 *      solve(i-1, j-1)
 *
 * If characters are different:
 *
 * 1. Insert
 *      solve(i, j-1)
 *
 * 2. Delete
 *      solve(i-1, j)
 *
 * 3. Replace
 *      solve(i-1, j-1)
 *
 * Take minimum of all three operations.
 *
 * Time Complexity: O(n * m)
 * Space Complexity: O(n * m)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(int i,int j,string& s1,string& s2,vector<vector<int>>& dp){

        if(i < 0) return j + 1;
        if(j < 0) return i + 1;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s1[i] == s2[j])
            return dp[i][j] = solve(i-1, j-1, s1, s2, dp);

        int insertOp  = solve(i, j-1, s1, s2, dp);
        int deleteOp  = solve(i-1, j, s1, s2, dp);
        int replaceOp = solve(i-1, j-1, s1, s2, dp);

        return dp[i][j] = 1 + min(insertOp, min(deleteOp, replaceOp));
    }

    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));

        return solve(n-1, m-1, word1, word2, dp);
    }
};



/**
 * Problem: Edit Distance
 *
 * Convert string word1 to word2 using minimum operations.
 *
 * Allowed operations:
 * 1. Insert
 * 2. Delete
 * 3. Replace
 *
 * ------------------------------------------------------------
 * Tabulation Idea
 *
 * Let:
 *
 * dp[i][j] = minimum operations required to convert
 *            first i characters of word1
 *            into first j characters of word2
 *
 * ------------------------------------------------------------
 * Base Cases
 *
 * dp[i][0] = i
 * Convert word1 → empty string
 * Need i deletions
 *
 * dp[0][j] = j
 * Convert empty string → word2
 * Need j insertions
 *
 * ------------------------------------------------------------
 * Transition
 *
 * If word1[i-1] == word2[j-1]
 *
 *      dp[i][j] = dp[i-1][j-1]
 *
 * Else:
 *
 * Insert  -> dp[i][j-1]
 * Delete  -> dp[i-1][j]
 * Replace -> dp[i-1][j-1]
 *
 * dp[i][j] = 1 + min(insert, delete, replace)
 *
 * ------------------------------------------------------------
 *
 * Time Complexity : O(n * m)
 * Space Complexity : O(n * m)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for(int i = 0; i <= n; i++)
            dp[i][0] = i;

        for(int j = 0; j <= m; j++)
            dp[0][j] = j;

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){

                if(word1[i-1] == word2[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else{
                    int insertOp  = dp[i][j-1];
                    int deleteOp  = dp[i-1][j];
                    int replaceOp = dp[i-1][j-1];

                    dp[i][j] = 1 + min(insertOp, min(deleteOp, replaceOp));
                }
            }
        }

        return dp[n][m];
    }
};