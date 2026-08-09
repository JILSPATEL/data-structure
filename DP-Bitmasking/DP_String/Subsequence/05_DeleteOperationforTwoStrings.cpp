/*
Problem: Delete Operation for Two Strings

Given two strings word1 and word2, return the minimum number of deletions
required to make the two strings equal.

We are allowed to delete characters from both strings.

Example:
word1 = "sea"
word2 = "eat"

Output = 2

Explanation:
Common subsequence = "ea"

Delete 's' from word1
Delete 't' from word2

Total deletions = 2


=============================
KEY IDEA
=============================

Instead of directly computing deletions,
we first compute the Longest Common Subsequence (LCS).

Why?

Because the characters that are common do NOT need deletion.

Only the remaining characters must be deleted.

Let:
n = length of word1
m = length of word2
L = length of LCS

Characters to delete from word1 = n - L
Characters to delete from word2 = m - L

Total deletions = (n - L) + (m - L)

Final Formula:
n + m - 2 * LCS
*/


/*
=================================================
APPROACH 1 : MEMOIZATION (TOP DOWN DP)
=================================================

Idea:
We compute LCS using recursion and store results
in a DP table to avoid recomputation.

State Definition:
dp[i][j] = LCS length for
first i characters of word1
first j characters of word2

Transition:

If characters match:
    LCS increases

dp[i][j] = 1 + solve(i-1, j-1)

Else:
We try skipping one character from either string.

dp[i][j] = max(
    solve(i-1, j),
    solve(i, j-1)
)

Base Case:
If either string becomes empty → LCS = 0

Time Complexity:
O(n * m)

Space Complexity:
O(n * m) + recursion stack
*/

class Solution {
public:

    int solve(int i, int j, string &s1, string &s2, vector<vector<int>> &dp){

        if(i == 0 || j == 0)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s1[i-1] == s2[j-1]){
            return dp[i][j] = 1 + solve(i-1, j-1, s1, s2, dp);
        }

        return dp[i][j] = max(
            solve(i-1, j, s1, s2, dp),
            solve(i, j-1, s1, s2, dp)
        );
    }

    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        int lcs = solve(n, m, word1, word2, dp);

        return n + m - 2 * lcs;
    }
};



/*
=========================================
APPROACH 2 : TABULATION (BOTTOM UP DP)
=========================================

This is the most common approach used in interviews.

Step 1: DP Definition

dp[i][j] =
LCS length between
first i characters of word1
first j characters of word2


Step 2: Base Case

If one string is empty:

dp[i][0] = 0
dp[0][j] = 0


Step 3: Transition

If characters match:

dp[i][j] = 1 + dp[i-1][j-1]

Else:

dp[i][j] = max(
            dp[i-1][j],
            dp[i][j-1]
           )


Step 4: Final Answer

LCS = dp[n][m]

Minimum deletions = n + m - 2 * LCS


Time Complexity:
O(n * m)

Space Complexity:
O(n * m)
*/

class Solution {
public:
    int minDistance(string word1, string word2) {

        int n = word1.size();
        int m = word2.size();

        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){

                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = 1 + dp[i-1][j-1];
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }

            }
        }

        int lcs = dp[n][m];

        return n + m - 2 * lcs;
    }
};