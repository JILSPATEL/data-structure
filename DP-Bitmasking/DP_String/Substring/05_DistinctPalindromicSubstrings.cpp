/*
 Problem: Distinct Palindromic Substrings

 Description:
 Given a string `s`, return all distinct substrings of `s` that are palindromes.

 Intuition:
 Any palindrome is symmetric around its center. You can discover palindromes either
 by checking all substring ranges with DP (using previously computed inner results),
 or by expanding around each possible center (for odd and even lengths).

 Approaches:
 1) Dynamic Programming (DP):
        - Use a 2D table `dp[i][j]` that is true if s[i..j] is a palindrome.
        - Build by increasing substring length: base cases length 1 and 2, then
            dp[i][j] = (s[i] == s[j]) && dp[i+1][j-1].
        - Insert each palindrome substring into an `unordered_set` to keep only distinct ones.

 2) Expand Around Center (Two-pointers):
        - For each index `i`, expand left/right for both odd (i,i) and even (i,i+1)
            centers while characters match; insert discovered palindromes into a set.
        - This avoids O(n^2) extra memory for the DP table and is typically faster in practice.

 Example:
 s = "abaaa"
 - Distinct palindromic substrings: {"a", "b", "aa", "aba", "aaa"}

 Complexity:
 - Time: O(n^2) in the worst case for both approaches (all centers/lengths expanded).
 - Space: DP uses O(n^2); expand-around-center uses O(1) extra + O(k * L) for storing
     the distinct palindromic substrings (set), where k is number of distinct palindromes.
*/

class Solution {
public:
    vector<string> palindromicSubstr(string &s) {
        int n = s.size();
        
        // vector<bool> takes 8x less memory than vector<char> or vector<int>
        vector<vector<bool>> dp(n, vector<bool>(n, false));
        
        // unordered_set provides O(1) average insertions (O(N) for strings)
        unordered_set<string> st; 
        
        for(int l = 1; l <= n; l++){
            for(int i = 0; i + l - 1 < n; i++){
                int j = i + l - 1;
                
                if(i == j) dp[i][j] = true;
                else if(i + 1 == j) dp[i][j] = (s[i] == s[j]);
                else dp[i][j] = (s[i] == s[j] && dp[i+1][j-1]);
                
                if(dp[i][j]){
                    // We still have to make a copy, but insertion is faster
                    st.insert(s.substr(i, l)); 
                }
            }
        }
        
        // Construct vector directly from unordered_set iterators
        return vector<string>(st.begin(), st.end());
    }
};


class Solution {
public:
    vector<string> palindromicSubstr(string &s) {
        int n = s.size();
        unordered_set<string> st;

        // Lambda function to expand outwards from a center
        auto expand = [&](int left, int right) {
            while (left >= 0 && right < n && s[left] == s[right]) {
                // We found a palindrome, insert it
                st.insert(s.substr(left, right - left + 1));
                left--;
                right++;
            }
        };

        for (int i = 0; i < n; i++) {
            expand(i, i);       // Odd length palindromes (e.g., "aba")
            expand(i, i + 1);   // Even length palindromes (e.g., "abba")
        }

        return vector<string>(st.begin(), st.end());
    }
};