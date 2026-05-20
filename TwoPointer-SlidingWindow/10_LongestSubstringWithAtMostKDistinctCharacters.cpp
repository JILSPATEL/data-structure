/**
 * Problem: Longest Substring With At Most K Distinct Characters
 *
 * Description:
 * Given a string `s` and an integer `k`, find the length of the longest substring
 * that contains exactly `k` distinct characters.
 * If no such substring exists, return -1.
 *
 * Approach 1: Brute Force (Not Used)
 * - Generate all substrings.
 * - Count distinct characters for each substring.
 * - Track maximum length where distinct count == k.
 * - Time Complexity: O(n^2 * 26)
 * - Not efficient.
 *
 * Approach 2: Sliding Window + HashMap (Optimal - Used)
 * - Use two pointers (left, right) to maintain a window.
 * - Expand window by moving `right`.
 * - Use hashmap to store frequency of characters.
 * - If distinct characters exceed k → shrink window from left.
 * - When distinct characters == k → update max length.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(k)
 */

class Solution {
public:
    int longestKSubstr(string &s, int k) {
        int n = s.size();
        unordered_map<char, int> mp;

        if (n == 0 || k == 0) {
            return -1;
        }

        int left = 0, right = 0;
        int maxLen = -1;

        while (right < n) {
            // Add current character
            mp[s[right]]++;

            // Shrink window if distinct characters > k
            while (mp.size() > k) {
                mp[s[left]]--;

                if (mp[s[left]] == 0) {
                    mp.erase(s[left]);
                }

                left++;
            }

            // Update result when exactly k distinct characters
            if (mp.size() == k) {
                maxLen = max(maxLen, right - left + 1);
            }

            right++;
        }

        return maxLen;
    }
};