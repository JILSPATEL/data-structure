/*
    Problem:
    Partition the string into palindromic substrings using the minimum
    possible number of cuts, and return that minimum number.

    Intuition:
    First determine which substrings are palindromes. Then, for each ending
    index i, consider every palindromic substring s[j...i]. If it starts at 0,
    no cut is needed; otherwise, make one cut after j-1 and reuse the best
    answer for s[0...j-1].

    Approach:
    1. Precompute pal[i][j], which tells whether s[i...j] is a palindrome.
    2. Let cuts[i] be the minimum cuts needed for s[0...i].
    3. For every palindromic s[j...i], update cuts[i] with either 0 or
       cuts[j-1] + 1.
    4. Return cuts[n-1].

    Example:
    For s = "aab", the best partition is "aa" | "b", so the answer is 1.
*/
class Solution {
public:
    int minCut(string s) {
        int n = s.size();

        vector<vector<bool>> pal(n, vector<bool>(n, false));

        // pal[i][j] = whether s[i...j] is a palindrome
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;

                if (len == 1)
                    pal[i][j] = true;
                else if (len == 2)
                    pal[i][j] = (s[i] == s[j]);
                else
                    pal[i][j] = (s[i] == s[j] && pal[i + 1][j - 1]);
            }
        }

        // cuts[i] = minimum cuts needed for s[0...i]
        vector<int> cuts(n);

        for (int i = 0; i < n; i++) {
            cuts[i] = i;  // Worst case: every character is separate.

            for (int j = 0; j <= i; j++) {
                if (pal[j][i]) {
                    if (j == 0)
                        cuts[i] = 0;
                    else
                        cuts[i] = min(cuts[i], cuts[j - 1] + 1);
                }
            }
        }

        return cuts[n - 1];
    }
};
