/*
Problem: Longest Common Substring

Given two strings s1 and s2, find the length of the longest common substring.

IMPORTANT:
Substring means characters must be CONTIGUOUS.

Example:
s1 = "abcdgh"
s2 = "acdghr"

Longest common substring = "dgh"
Length = 3


===========================
DP APPROACH EXPLANATION
===========================

Difference Between LCS and LCSubstring
--------------------------------------

LCS (Subsequence)
Characters do NOT need to be contiguous.

LCSubstring
Characters MUST be contiguous.

This is the key reason for the different DP transition.

================================================
APPROACH 1 : RECURSION + MEMOIZATION (TOP DOWN)
================================================

Idea:
For substring we must maintain the length of the current matching suffix.

If characters match:
    extend the substring

If characters do not match:
    substring breaks → reset length to 0

We explore three possibilities:
1) Continue substring if characters match
2) Move i-1
3) Move j-1

We track the global maximum length.

State Definition:
dp[i][j] = longest substring ending at i and j

Transition:
If s1[i] == s2[j]
    dp[i][j] = 1 + solve(i-1, j-1)

Else
    dp[i][j] = 0

But we still explore solve(i-1,j) and solve(i,j-1)
to check other starting positions.


Time Complexity:
O(n*m)

Space Complexity:
O(n*m)
*/


class Solution {
public:

    int ans = 0;

    int solve(int i, int j, string &s1, string &s2, vector<vector<int>> &dp){

        if(i < 0 || j < 0)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        int cur = 0;

        if(s1[i] == s2[j]){
            cur = 1 + solve(i-1, j-1, s1, s2, dp);
            ans = max(ans, cur);
        }

        solve(i-1, j, s1, s2, dp);
        solve(i, j-1, s1, s2, dp);

        return dp[i][j] = cur;
    }

    int longCommSubstr(string s1, string s2) {

        int n = s1.size();
        int m = s2.size();

        vector<vector<int>> dp(n, vector<int>(m, -1));

        solve(n-1, m-1, s1, s2, dp);

        return ans;
    }
};



/*
====================================
APPROACH 2 : TABULATION (BOTTOM UP)
====================================

This is the MOST COMMON approach used in interviews.

Step 1: DP Definition
dp[i][j] = length of longest common substring
ending at s1[i-1] and s2[j-1]

Step 2: Base Case
If either string is empty:
dp[i][0] = 0
dp[0][j] = 0

Step 3: Transition

If characters match:
    dp[i][j] = 1 + dp[i-1][j-1]

Else:
    substring breaks → dp[i][j] = 0

Step 4: Track maximum value
Because answer can appear anywhere in table.

ans = max(ans, dp[i][j])

Final Answer = ans

Time Complexity:
O(n*m)

Space Complexity:
O(n*m)
*/


class Solution {
public:
    int longCommSubstr(string& s1, string& s2) {

        int l1 = s1.size();
        int l2 = s2.size();

        vector<vector<int>> dp(l1+1, vector<int>(l2+1, 0));

        int ans = 0;

        for(int i = 1; i <= l1; i++){
            for(int j = 1; j <= l2; j++){

                if(s1[i-1] == s2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                    ans = max(ans, dp[i][j]);
                }
                else{
                    dp[i][j] = 0;
                }

            }
        }

        return ans;
    }
};