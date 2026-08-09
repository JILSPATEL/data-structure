/*
Problem: Count the number of palindromic substrings in a string.

Intuition:
A substring is a palindrome if its first and last characters are the same,
and the substring inside them is also a palindrome. We can build the answer
from shorter substrings to longer ones.

Approach:
Use dynamic programming where dp[j] tells whether s[i..j] is a palindrome.
- A single character is always a palindrome.
- A two-character substring is a palindrome if both characters are equal.
- For longer substrings, check whether s[i] == s[j] and the inner substring
  s[i+1..j-1] is a palindrome.
Every time we find a palindromic substring (except when i == j), we increase
our count.

Example:
Input: s = "aaa"
Palindromic substrings are: "a", "a", "a", "aa", "aa", "aaa"
So the answer is 6.
*/

class Solution {
public:
    int countPS(string &s) {
        int n = s.size();

        vector<bool> dp(n, false);
        int cnt = 0;

        for (int i = n - 1; i >= 0; i--) {

            for (int j = i; j < n; j++) {

                if (i == j) {
                    dp[j] = true;
                }
                else if (i + 1 == j) {
                    dp[j] = (s[i] == s[j]);
                }
                else {
                    dp[j] = (s[i] == s[j] && dp[j - 1]);
                }

                if (dp[j] && i != j) {
                    cnt++;
                }
            }
        }

        return cnt;
    }
};