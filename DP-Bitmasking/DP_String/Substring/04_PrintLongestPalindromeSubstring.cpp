/*
 Problem: Longest Palindromic Substring

 Description:
 Given a string `s`, find and return the longest substring of `s` which is a palindrome.

 Intuition:
 A substring s[i..j] is a palindrome if the characters at the ends match (s[i] == s[j])
 and the inner substring s[i+1..j-1] is also a palindrome. Base cases are single
 characters and pairs of equal characters.

 Approach (Dynamic Programming):
 - Use a 2D boolean DP table `dp[i][j]` that is true when s[i..j] is palindrome.
 - Iterate lengths `l` from 1 to n and for each start index `i` compute `j = i + l - 1`.
 - Set `dp[i][j]` based on base cases (length 1 or 2) or `s[i] == s[j] && dp[i+1][j-1]`.
 - Track the maximum length and starting index to return the longest palindromic substring.

 Example:
 s = "babad"
 - Palindromic substrings found include "b", "a", "bab", "aba".
 - The algorithm may return "bab" or "aba" (both length 3 and valid answers).

 Complexity:
 - Time: O(n^2) due to checking all substring lengths and start indices.
 - Space: O(n^2) for the DP table.
*/

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();

        vector<vector<bool>> dp(n, vector<bool>(n, false));

        int start = 0;
        int maxLen = 1;

        for (int l = 1; l <= n; l++) {

            for (int i = 0; i + l - 1 < n; i++) {

                int j = i + l - 1;

                if (i == j)
                    dp[i][j] = true;

                else if (i + 1 == j)
                    dp[i][j] = (s[i] == s[j]);

                else
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);

                if (dp[i][j] && l > maxLen) {
                    maxLen = l;
                    start = i;
                }
            }
        }

        return s.substr(start, maxLen);
    }
};