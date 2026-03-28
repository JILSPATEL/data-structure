/**
 * Problem: Number of Substrings Containing All Three Characters
 * ------------------------------------------------------------
 * Given a string s consisting only of characters 'a', 'b', and 'c',
 * return the number of substrings containing at least one occurrence
 * of all three characters.
 *
 * Approach 1 (Optimal - Last Seen Index):
 * - Maintain last seen indices of 'a', 'b', and 'c'.
 * - At each index i:
 *      - Update last seen for current character.
 *      - If all three characters have appeared:
 *          -> The number of valid substrings ending at i is:
 *             1 + min(lastSeen['a'], lastSeen['b'], lastSeen['c'])
 *
 * - Why?
 *   Because any substring starting from index [0 ... minIndex]
 *   and ending at i will contain all three characters.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * ------------------------------------------------------------
 * Approach 2 (Sliding Window - Alternative):
 * - Use two pointers and count valid windows.
 * - Expand right pointer and maintain frequency.
 * - Shrink left pointer while all 3 characters exist.
 * - Add (n - right) to answer.
 *
 * (Slightly more complex than optimal approach)
 */

class Solution {
public:
    int numberOfSubstrings(string s) {
        int n = s.size();

        // Stores last seen index of 'a', 'b', 'c'
        vector<int> lastSeen(3, -1);

        int cnt = 0;

        for (int i = 0; i < n; i++) {

            // Update last seen index
            lastSeen[s[i] - 'a'] = i;

            // Check if all characters have been seen
            if (lastSeen[0] != -1 && lastSeen[1] != -1 && lastSeen[2] != -1) {

                // Count valid substrings ending at i
                cnt += (1 + min({lastSeen[0], lastSeen[1], lastSeen[2]}));
            }
        }

        return cnt;
    }
};