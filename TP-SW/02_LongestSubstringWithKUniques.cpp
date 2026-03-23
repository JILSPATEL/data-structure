/**
 * Problem: Longest Substring with Exactly K Unique Characters
 * ----------------------------------------------------------
 * Given a string s and an integer k, find the length of the
 * longest substring that contains exactly k distinct characters.
 *
 * Approach Used: Sliding Window + Hash Map
 * ----------------------------------------------------------
 * - Use two pointers (left, right) to maintain a window.
 * - Use unordered_map<char,int> to store frequency of characters.
 *
 * Algorithm:
 * 1. Expand window by moving 'right':
 *      - Add s[right] to map and increase its frequency.
 *
 * 2. If number of distinct characters > k:
 *      - Shrink window from left until map size <= k
 *      - Decrease frequency and erase if it becomes 0
 *
 * 3. If map size == k:
 *      - Update maximum length
 *
 * 4. Continue until right reaches end of string.
 *
 * Time Complexity: O(n)
 *      Each character is processed at most twice.
 *
 * Space Complexity: O(k)
 *      At most k unique characters stored in map.
 *
 * Edge Case:
 * - If no substring with exactly k unique characters exists,
 *   return -1.
 *
 * Common Mistakes Fixed:
 * ----------------------------------------------------------
 * - Typo: unordered_map was misspelled
 * - Wrong data type for map key (should be char, not int)
 * - Incorrect while condition: mp.size() > k
 * - Missing increment of 'right'
 * - Incorrect maxLen calculation (missing +1)
 */

class Solution {
public:
    int longestKSubstr(string &s, int k) {
        unordered_map<char, int> mp;

        int n = s.size();
        if (n == 0 || k == 0) return -1;

        int left = 0, right = 0;
        int maxLen = -1;

        while (right < n) {
            mp[s[right]]++;

            while (mp.size() > k) {
                mp[s[left]]--;
                if (mp[s[left]] == 0) {
                    mp.erase(s[left]);
                }
                left++;
            }

            if (mp.size() == k) {
                maxLen = max(maxLen, right - left + 1);
            }

            right++;  // IMPORTANT
        }

        return maxLen;
    }
};