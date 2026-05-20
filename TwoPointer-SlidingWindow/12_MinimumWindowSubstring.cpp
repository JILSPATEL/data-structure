/**
 * Problem: Minimum Window Substring
 * --------------------------------
 * Given two strings s and t, return the minimum window substring of s 
 * such that every character in t (including duplicates) is included in the window.
 * If no such substring exists, return "".
 *
 * Approach:
 * 1. Sliding Window + Hash Map
 *    - Store frequency of characters of t in a hashmap.
 *    - Expand right pointer (r) to include characters.
 *    - If character is useful (exists in map with freq > 0), increase match count.
 *    - Once all characters are matched (cnt == t.size()), shrink window from left (l).
 *    - Update minimum window length whenever valid window is found.
 *
 * 2. Optimization Idea:
 *    - Instead of comparing with t.size(), maintain a required unique count.
 *    - This avoids redundant counting when duplicates exist.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) (since charset is limited)
 */

class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> mp;

        // Store frequency of characters in t
        for(char ch : t){
            mp[ch]++;
        }

        int cnt = 0;
        int minLen = 1e9;
        int sIdx = -1;

        int l = 0, r = 0;
        int n = s.size();

        while (r < n) {

            // Expand window
            if (mp[s[r]] > 0) {
                cnt++;
            }
            mp[s[r]]--;

            // Shrink window when valid
            while (cnt == t.size()) {
                if (r - l + 1 < minLen) {
                    minLen = r - l + 1;
                    sIdx = l;
                }

                mp[s[l]]++;
                if (mp[s[l]] > 0) {
                    cnt--;
                }
                l++;
            }

            r++;
        }

        return sIdx == -1 ? "" : s.substr(sIdx, minLen);
    }
};