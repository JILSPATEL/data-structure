/**
 * Problem: Minimum Insertions to Make String Palindrome
 *
 * Given a string s, return the minimum number of insertions required
 * to make the string a palindrome.
 *
 * Key Idea:
 * Instead of directly calculating insertions, we first compute
 * the Longest Palindromic Subsequence (LPS).
 *
 * Relation:
 * Minimum Insertions = n - LPS
 *
 * And LPS can be found using:
 * LCS(s, reverse(s))
 *
 * Steps:
 * 1. Reverse the string.
 * 2. Compute LCS between original string and reversed string.
 * 3. The LCS length represents the Longest Palindromic Subsequence.
 * 4. Minimum insertions needed = n - LPS.
 *
 * Time Complexity:  O(N^2)
 * Space Complexity: O(N^2)
 *
 * Example:
 * Input:  s = "mbadm"
 * Output: 2
 *
 * Explanation:
 * Longest Palindromic Subsequence = "mam" or "mbm"
 * String length = 5
 * Minimum insertions = 5 - 3 = 2
 */

//Tabulation

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minInsertions(string s) {

        int n = s.size();
        string t = s;
        reverse(t.begin(), t.end());

        vector<vector<int>> dp(n+1, vector<int>(n+1,0));

        // LCS computation
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){

                if(s[i-1] == t[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];

                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }

        int lps = dp[n][n];

        return n - lps;
    }
};

//Memoization

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    int solve(int i, int j, string &s, string &t, vector<vector<int>> &dp){

        if(i==0 || j==0)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s[i-1] == t[j-1])
            return dp[i][j] = 1 + solve(i-1,j-1,s,t,dp);

        return dp[i][j] = max(
            solve(i-1,j,s,t,dp),
            solve(i,j-1,s,t,dp)
        );
    }

    int minInsertions(string s) {

        int n = s.size();
        string t = s;
        reverse(t.begin(), t.end());

        vector<vector<int>> dp(n+1, vector<int>(n+1,-1));

        int lps = solve(n,n,s,t,dp);

        return n - lps;
    }
};