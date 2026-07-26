/*
Description:
Count how many palindromic substrings exist in a given string.

Intuition:
A substring is a palindrome if its first and last characters match and the inside substring is also a palindrome.
We can build answers from smaller substrings to larger ones using dynamic programming.

Approach:
- Use a DP table dp[i][j] to store whether s[i..j] is a palindrome.
- Base cases:
  - Single character => palindrome
  - Two characters => palindrome if both are equal
- Transition:
  - dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1]
- Count every true palindrome found.

Example:
Input: s = "aaa"
Palindromic substrings are: "a", "a", "a", "aa", "aa", "aaa"
Total = 6
*/

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n, false));

        int cnt = 0;

        for (int l = 1; l <= n; l++) {
            for (int i = 0; i + l - 1 < n; i++) {
                int j = i + l - 1;

                if (i == j) {
                    dp[i][j] = true;
                }
                else if (i + 1 == j) {
                    dp[i][j] = (s[i] == s[j]);
                }
                else {
                    dp[i][j] = (s[i] == s[j] && dp[i+1][j-1]);
                }

                if (dp[i][j]) cnt++;
            }
        }

        return cnt;
    }
};