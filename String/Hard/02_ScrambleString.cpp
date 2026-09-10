/*
Problem:
Given two strings `s1` and `s2` of the same length, determine whether `s2` can be formed by
recursively splitting `s1` into two non-empty parts and optionally swapping the parts at every
split.

Approach / Intuition:
- Two strings can be scrambles only if they have the same length and the same character
    frequencies. This also lets us reject impossible subproblems early.
- Try every split position `i` in `s1`. For each split, there are two possibilities:
    1. Do not swap the parts: the prefix matches the prefix of `s2`, and the suffix matches the
       suffix of `s2`.
    2. Swap the parts: the prefix matches the suffix of `s2`, and the suffix matches the prefix
       of `s2`.
- Recursively check both resulting pairs. Memoization stores the result for each `(s1, s2)` pair,
    avoiding repeated work from overlapping subproblems.

Example:
For `s1 = "great"` and `s2 = "rgeat"`, split `s1` into `"gr"` and `"eat"` and `s2` into
`"rg"` and `"eat"`. The first parts are scrambles because `"gr"` can be swapped to `"rg"`,
and the second parts are already equal. Therefore, `"rgeat"` is a scramble of `"great"`.

Why this works:
- Every valid scramble is created by one of the two split arrangements at each level. Trying all
    split positions and both arrangements explores every possible construction. Character counts
    safely eliminate pairs that cannot contain the same characters, while memoization ensures each
    pair is solved only once.

Complexity: O(n^4) time and O(n^3) space in the usual memoized analysis, where `n` is the string
length. The substring creation in this implementation can add extra copying overhead.
*/

class Solution {
public:
    unordered_map<string,bool> dp;
    bool isScramble(string s1, string s2) {
        if (s1 == s2) return true;
        if (s1.length() != s2.length()) return false;
        string key=s1+s2;
        if(dp.count(key)) return dp[key];
        int charCount[26] = {0};
        for (int i = 0; i < s1.length(); i++) {
            charCount[s1[i] - 'a']++;
            charCount[s2[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (charCount[i] != 0) {
                return dp[key]=false; 
            }
        }
        
        int n = s1.length();
        
        for (int i = 1; i < n; i++) {
            if (isScramble(s1.substr(0, i), s2.substr(0, i)) && 
                isScramble(s1.substr(i), s2.substr(i))) {
                return dp[key]=true;
            }
            
            if (isScramble(s1.substr(0, i), s2.substr(n - i)) && 
                isScramble(s1.substr(i), s2.substr(0, n - i))) {
                return dp[key]=true;
            }
        }
        
        return dp[key]=false;
    }
};