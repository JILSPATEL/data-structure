/**
 * Problem: Distinct Subsequences
 *
 * Given two strings s and t, return the number of distinct subsequences
 * of s which equals t.
 *
 * A subsequence is formed by deleting zero or more characters without
 * changing the relative order of the remaining characters.
 *
 * Example:
 * s = "rabbbit"
 * t = "rabbit"
 *
 * Output: 3
 *
 * Explanation:
 * There are three ways to remove one 'b' from "rabbbit" to get "rabbit".
 */

 /*
 * -------------------------------------------------------------
 * Memoization Idea (Top Down DP)
 *
 * Define:
 * dp[i][j] = number of ways to form t[0..j] using s[0..i]
 *
 * Recurrence:
 *
 * If s[i] == t[j]
 *      We have two options:
 *      1) Match characters
 *         -> solve(i-1, j-1)
 *      2) Skip s[i]
 *         -> solve(i-1, j)
 *
 *      dp[i][j] = solve(i-1, j-1) + solve(i-1, j)
 *
 * If s[i] != t[j]
 *      We must skip s[i]
 *
 *      dp[i][j] = solve(i-1, j)
 *
 * -------------------------------------------------------------
 * Base Cases
 *
 * If j < 0
 *      Target completely matched
 *      return 1
 *
 * If i < 0
 *      Source exhausted but target still left
 *      return 0
 *
 * -------------------------------------------------------------
 *
 * Time Complexity  : O(n * m)
 * Space Complexity : O(n * m)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    long long solve(int i, int j, string &s, string &t, vector<vector<long long>> &dp)
    {
        if (j < 0)
            return 1;

        if (i < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == t[j])
        {
            long long take = solve(i - 1, j - 1, s, t, dp);
            long long skip = solve(i - 1, j, s, t, dp);

            return dp[i][j] = take + skip;
        }

        return dp[i][j] = solve(i - 1, j, s, t, dp);
    }

    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        vector<vector<long long>> dp(n, vector<long long>(m, -1));

        return solve(n - 1, m - 1, s, t, dp);
    }
};


//Tabulation

/**
 * Problem: Distinct Subsequences
 *
 * Given two strings s and t, return the number of distinct subsequences
 * of s which equals t.
 *
 * -------------------------------------------------------------
 * Tabulation Idea (Bottom Up DP)
 *
 * Let:
 *
 * dp[i][j] = number of ways to form first j characters of t
 *            using first i characters of s
 *
 * -------------------------------------------------------------
 * Base Cases
 *
 * dp[i][0] = 1
 * Empty string t can always be formed from any prefix of s.
 *
 * dp[0][j] = 0
 * Non-empty t cannot be formed from empty s.
 *
 * -------------------------------------------------------------
 * Transition
 *
 * If s[i-1] == t[j-1]
 *
 *      We have two choices:
 *
 *      1) Use this character
 *             dp[i-1][j-1]
 *
 *      2) Skip this character
 *             dp[i-1][j]
 *
 *      dp[i][j] = dp[i-1][j-1] + dp[i-1][j]
 *
 * If s[i-1] != t[j-1]
 *
 *      dp[i][j] = dp[i-1][j]
 *
 * -------------------------------------------------------------
 *
 * Time Complexity  : O(n * m)
 * Space Complexity : O(n * m)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t)
    {
        int n = s.size();
        int m = t.size();

        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));

        for (int i = 0; i <= n; i++)
            dp[i][0] = 1;

        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s[i - 1] == t[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        return dp[n][m];
    }
};