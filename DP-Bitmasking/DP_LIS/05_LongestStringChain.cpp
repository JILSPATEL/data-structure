/*
Problem:
Find the length of the longest chain of words where each next word can be formed by inserting exactly one character into the previous word.

Approach:
Sort the words by length and use dynamic programming.
A word can follow a shorter word if it differs by exactly one insertion.
For each word, try all earlier words and update the best chain length.

Intuition:
Because every valid transition adds exactly one character, sorting by size makes the comparison simple and ensures we only check words that are one character shorter.

Example:
words = ["a", "b", "ba", "bca", "bda", "ca", "bdca"]
One longest chain is "a -> ba -> bca -> bdca", so the answer is 4.
*/

// Memorization approach
class Solution {
public:
    bool isPred(string &word1, string &word2) {
        int m = word1.size();
        int n = word2.size();

        if (m >= n || n - m != 1) return false;

        int i = 0, j = 0;

        while (i < m && j < n) {
            if (word1[i] == word2[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        return i == m;
    }

    int solve(int idx, vector<string> &words, vector<int> &dp) {
        if (dp[idx] != -1) return dp[idx];

        int ans = 1;
        for (int i = idx - 1; i >= 0; i--) {
            if (isPred(words[i], words[idx])) {
                ans = max(ans, 1 + solve(i, words, dp));
            }
        }
        return dp[idx] = ans;
    }

    int longestStrChain(vector<string>& words) {
        int n = words.size();
        sort(words.begin(), words.end(),
             [](string a, string b) { return a.size() < b.size(); });
        vector<int> dp(n, -1);
        int ans = 1;
        for (int i = 0; i < n; i++) {
            ans = max(ans, solve(i, words, dp));
        }
        return ans;
    }
};

// Tabulation approach
class SolutionTabulation {
public:
    bool isPred(string &word1, string &word2) {
        int m = word1.size();
        int n = word2.size();

        if (m >= n || n - m != 1) return false;

        int i = 0, j = 0;

        while (i < m && j < n) {
            if (word1[i] == word2[j]) {
                i++;
                j++;
            } else {
                j++;
            }
        }
        return i == m;
    }

    int longestStrChain(vector<string>& words) {
        int n = words.size();
        sort(words.begin(), words.end(),
             [](string a, string b) { return a.size() < b.size(); });
        int ans = 1;
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (isPred(words[j], words[i])) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    ans = max(ans, dp[i]);
                }
            }
        }
        return ans;
    }
};