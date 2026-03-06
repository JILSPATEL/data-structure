/*
Problem: Longest Common Subsequence (LCS)

Given two strings s1 and s2, find the length of their Longest Common Subsequence.

A subsequence is a sequence that appears in the same relative order but not
necessarily contiguous.

Example:
s1 = "abcde"
s2 = "ace"

The longest common subsequence is "ace".
So the answer = 3.

Approach 1: Dynamic Programming (Tabulation)

Idea:
Let dp[i][j] represent the length of LCS between:
first i characters of s1 and first j characters of s2.

Base Case:
If either string is empty, LCS length = 0.
dp[i][0] = 0
dp[0][j] = 0

Transition:
If characters match:
s1[i-1] == s2[j-1]

Then we extend the previous subsequence:
dp[i][j] = 1 + dp[i-1][j-1]

Else:
We take the maximum of ignoring one character from either string:
dp[i][j] = max(dp[i-1][j], dp[i][j-1])

Final Answer:
dp[l1][l2]

Time Complexity:
O(n * m)

Space Complexity:
O(n * m)


Approach 2: Recursive + Memoization (Top Down)

Idea:
At each index we have two choices:
1. If characters match → include it and move both pointers
2. If not match → skip one character from either string

We store already computed results in dp to avoid recomputation.

Recursive Relation:
if s1[i] == s2[j]
    return 1 + solve(i-1, j-1)

else
    return max(solve(i-1, j), solve(i, j-1))

Base Case:
If i < 0 or j < 0 → return 0

Memoization stores results in dp[i][j].
*/


// ---------------- TABULATION SOLUTION ----------------

class Solution {
public:
    int longestCommonSubsequence(string s1, string s2) {
        int l1 = s1.size();
        int l2 = s2.size();

        vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));

        for(int i = 0; i < l1+1; i++){
            dp[i][0] = 0;
        }

        for(int i = 0; i < l2+1; i++){
            dp[0][i] = 0;
        }

        for(int i = 1; i <= l1; i++){
            for(int j = 1; j <= l2; j++){
                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[l1][l2];
    }
};



// ---------------- MEMOIZATION SOLUTION ----------------

class Solution {
public:

    int solve(int i, int j, string &s1, string &s2, vector<vector<int>> &dp){
        
        if(i < 0 || j < 0) return 0;

        if(dp[i][j] != -1) return dp[i][j];

        if(s1[i] == s2[j]){
            return dp[i][j] = 1 + solve(i-1, j-1, s1, s2, dp);
        }

        return dp[i][j] = max(
            solve(i-1, j, s1, s2, dp),
            solve(i, j-1, s1, s2, dp)
        );
    }

    int longestCommonSubsequence(string s1, string s2) {

        int l1 = s1.size();
        int l2 = s2.size();

        vector<vector<int>> dp(l1, vector<int>(l2, -1));

        return solve(l1-1, l2-1, s1, s2, dp);
    }
};