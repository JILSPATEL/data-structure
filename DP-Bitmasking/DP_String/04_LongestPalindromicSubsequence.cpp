/**
 * Problem: Longest Palindromic Subsequence (Print LPS)
 *
 * Given a string s, find the longest subsequence of the string
 * that is also a palindrome and return the subsequence itself.
 *
 * Idea:
 * A palindrome reads the same forward and backward.
 * If we reverse the string and find the Longest Common Subsequence (LCS)
 * between the original string and the reversed string,
 * the result will be the Longest Palindromic Subsequence.
 *
 * Steps:
 * 1. Reverse the given string.
 * 2. Find LCS between original string and reversed string.
 * 3. Backtrack through the DP table to reconstruct the subsequence.
 *
 * Time Complexity:  O(N^2)
 * Space Complexity: O(N^2)
 *
 * Example:
 * Input:  s = "bbbab"
 * Output: "bbbb"
 */


 //Tabulation

 #include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string longestPalinSubseq(string s) {

        int n = s.size();
        string t = s;
        reverse(t.begin(), t.end());

        vector<vector<int>> dp(n+1, vector<int>(n+1,0));

        // Build LCS table
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){

                if(s[i-1] == t[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];

                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }

        // Backtrack to construct LPS
        int i = n;
        int j = n;
        string ans = "";

        while(i>0 && j>0){

            if(s[i-1] == t[j-1]){
                ans.push_back(s[i-1]);
                i--;
                j--;
            }
            else if(dp[i-1][j] > dp[i][j-1]){
                i--;
            }
            else{
                j--;
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
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

    string longestPalinSubseq(string s) {

        int n = s.size();
        string t = s;
        reverse(t.begin(), t.end());

        vector<vector<int>> dp(n+1, vector<int>(n+1,-1));

        solve(n,n,s,t,dp);

        // Backtracking
        int i=n, j=n;
        string ans="";

        while(i>0 && j>0){

            if(s[i-1] == t[j-1]){
                ans.push_back(s[i-1]);
                i--;
                j--;
            }
            else if(dp[i-1][j] > dp[i][j-1]){
                i--;
            }
            else{
                j--;
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};