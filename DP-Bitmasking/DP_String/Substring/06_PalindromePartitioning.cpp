/*
    Problem:
    Partition the string into substrings so that every substring is a
    palindrome. Return all possible palindrome partitions.

    Intuition:
    At any index, try every substring that starts there. If the substring is
    a palindrome, add it to the current partition and recursively solve the
    remaining suffix. Backtracking removes the choice after the recursive
    call so that the next possible partition can be explored.

    Approach:
    1. Precompute dp[i][j], which tells whether s[i...j] is a palindrome.
    2. Start backtracking from index 0.
    3. For every palindromic s[idx...j], add it to path and recurse from j+1.
    4. When idx reaches n, store the completed path in ans.

    Example:
    For s = "aab", the valid partitions are:
    ["a", "a", "b"] and ["aa", "b"].
*/
class Solution {
public:
    vector<vector<bool>> dp;
    vector<vector<string>> ans;
    int n;

    void solve(string& s, int idx, vector<string>& path) {
        if (idx == n) {
            ans.push_back(path);
            return;
        }

        for (int j = idx; j < n; j++) {
            if (dp[idx][j]) {
                path.push_back(s.substr(idx, j - idx + 1));

                solve(s, j + 1, path);

                path.pop_back();
            }
        }
    }
    vector<vector<string>> partition(string s) {
        n = s.size();
        dp.assign(n, vector<bool>(n, false));

        for (int l = 1; l <= n; l++) {
            for (int i = 0; i + l - 1 < n; i++) {
                int j = i + l - 1;

                if (i == j)
                    dp[i][j] = true;
                else if (i + 1 == j)
                    dp[i][j] = (s[i] == s[j]);
                else
                    dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
            }
        }
        vector<string> path;
        solve(s, 0, path);
        return ans;
    }
};