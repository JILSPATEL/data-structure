/**
 * Problem: Longest Repeating Character Replacement
 * 
 * Given a string s and an integer k, you can replace at most k characters
 * to make a substring with all identical characters.
 * Return the length of the longest such substring.
 * 
 * Approach:
 * 1. Brute Force:
 *    - Generate all substrings.
 *    - Count frequency of characters in each substring.
 *    - Check if (length - maxFreq <= k).
 *    - Time Complexity: O(n^3)
 * 
 * 2. Better Approach:
 *    - Use sliding window and recompute maxFreq every time.
 *    - Time Complexity: O(26 * n)
 * 
 * 3. Optimal Approach (Used Below):
 *    - Use sliding window with hashmap.
 *    - Track maxFreq dynamically (do NOT decrease it).
 *    - If replacements needed > k → shrink window.
 *    - Time Complexity: O(n)
 *    - Space Complexity: O(1) (since only 26 chars)
 */

class Solution {
public:
    int characterReplacement(string s, int k) {

        unordered_map<char, int> mp; // frequency map
        int left = 0;
        int maxFreq = 0; // max frequency in current window
        int res = 0;

        for (int right = 0; right < s.size(); right++) {

            // expand window
            mp[s[right]]++;

            // update max frequency
            maxFreq = max(maxFreq, mp[s[right]]);

            // if replacements needed > k → shrink window
            while ((right - left + 1) - maxFreq > k) {
                mp[s[left]]--;
                left++;
            }

            // update result
            res = max(res, right - left + 1);
        }

        return res;
    }
};