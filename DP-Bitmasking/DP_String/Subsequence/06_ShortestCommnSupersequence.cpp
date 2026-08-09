/*
Problem: Shortest Common Supersequence (SCS)

Given two strings str1 and str2, return the shortest string that has both
str1 and str2 as subsequences.

A supersequence of a string is a string that contains the original string
as a subsequence.

Example:
str1 = "abac"
str2 = "cab"

Output:
"cabac"

Explanation:
Both "abac" and "cab" appear as subsequences in "cabac".


========================================
KEY IDEA
========================================

The shortest common supersequence is related to the
Longest Common Subsequence (LCS).

If we know the LCS, we can merge the two strings while
avoiding duplication of common characters.

Length of SCS = n + m - LCS


Example:

str1 = "abac"
str2 = "cab"

LCS = "ab"

SCS is formed by combining both strings while keeping
the LCS characters only once.


=================================================
APPROACH 1 : MEMOIZATION (TOP DOWN DP)
=================================================

Idea:
First compute the LCS using recursion + memoization.

dp[i][j] = LCS length for first i characters of str1
           and first j characters of str2.

Transition:

If characters match:
    dp[i][j] = 1 + solve(i-1, j-1)

Else:
    dp[i][j] = max(
                solve(i-1, j),
                solve(i, j-1)
              )

After computing LCS, reconstruct the SCS string
by traversing the DP table.

Time Complexity:
O(n * m)

Space Complexity:
O(n * m) + recursion stack


=================================================
APPROACH 2 : TABULATION (BOTTOM UP DP)
=================================================

Step 1: Build LCS DP table.

dp[i][j] = length of LCS between
first i characters of str1
first j characters of str2.

If characters match:
    dp[i][j] = 1 + dp[i-1][j-1]

Else:
    dp[i][j] = max(dp[i-1][j], dp[i][j-1])


Step 2: Reconstruct the SCS.

Start from dp[n][m].

If characters match:
    add character once
    move diagonally

Else:
    move in direction of larger dp value
    and append that character.


Step 3:
Append remaining characters.


Time Complexity:
O(n * m)

Space Complexity:
O(n * m)
*/


class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {

        int n = str1.size();
        int m = str2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){

                if(str1[i-1] == str2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);

            }
        }

        string ans = "";

        int i = n;
        int j = m;

        while(i > 0 && j > 0){

            if(str1[i-1] == str2[j-1]){
                ans += str1[i-1];
                i--;
                j--;
            }
            else if(dp[i-1][j] > dp[i][j-1]){
                ans += str1[i-1];
                i--;
            }
            else{
                ans += str2[j-1];
                j--;
            }

        }

        while(i > 0){
            ans += str1[i-1];
            i--;
        }

        while(j > 0){
            ans += str2[j-1];
            j--;
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};