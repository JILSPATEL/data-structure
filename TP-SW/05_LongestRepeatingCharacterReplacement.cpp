/**
 * Problem: Longest Repeating Character Replacement
 *
 * Description:
 * Given a string s and an integer k, you can replace at most k characters.
 * Return the length of the longest substring containing the same letter
 * after performing at most k replacements.
 *
 * Approach:
 * 1. Sliding Window Technique:
 *    - Maintain a window [left, right]
 *    - Keep track of frequency of characters using hashmap
 *    - Track max frequency (maxFreq) in current window
 *
 * 2. Key Observation:
 *    - Number of replacements needed = window_size - maxFreq
 *    - If replacements > k → shrink window from left
 *
 * 3. Optimization:
 *    - maxFreq is NOT reduced when shrinking window (important trick)
 *    - This ensures O(n) time complexity
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1) (since only 26 uppercase letters)
 */

class Solution {
public:
    int characterReplacement(string s, int k) {
        int left = 0, res = 0, maxFreq = 0;
        int n = s.size();

        unordered_map<char, int> mp;
        int right = 0;

        while (right < n) {
            mp[s[right]]++;

            // Update max frequency in current window
            maxFreq = max(maxFreq, mp[s[right]]);

            // If replacements needed > k, shrink window
            while ((right - left + 1) - maxFreq > k) {
                mp[s[left]]--;
                left++;
            }

            // Update result
            res = max(res, right - left + 1);
            right++;
        }

        return res;
    }
};