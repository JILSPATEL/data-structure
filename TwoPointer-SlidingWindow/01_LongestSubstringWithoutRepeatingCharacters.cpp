/**
 * Problem: Longest Substring Without Repeating Characters
 * ------------------------------------------------------
 * Given a string s, find the length of the longest substring 
 * without repeating characters.
 *
 * Approach Used: Sliding Window + Hash Set
 * ------------------------------------------------------
 * - We maintain a window using two pointers:
 *      left  -> start of window
 *      right -> end of window
 *
 * - Use an unordered_set to store unique characters in current window.
 *
 * - Traverse string using 'right' pointer:
 *      1. If current character is NOT in set:
 *          - Insert into set
 *          - Update max length
 *          - Expand window (right++)
 *
 *      2. If character is already present:
 *          - Remove character at 'left'
 *          - Move left pointer forward
 *
 * - Continue until full string is processed.
 *
 * Time Complexity: O(n)
 *      Each character is inserted and removed at most once.
 *
 * Space Complexity: O(k)
 *      k = size of character set (at most 256 for ASCII)
 *
 * NOTE:
 * ------------------------------------------------------
 * This implementation has a logical issue:
 * - In case of duplicate, it removes only ONE character,
 *   but we may need to shrink window multiple times until
 *   duplicate is removed.
 *
 * Correct approach should use a while loop instead of if.
 *
 * Corrected snippet:
 * ------------------------------------------------------
 * while(st.find(s[right]) != st.end()){
 *     st.erase(s[left]);
 *     left++;
 * }
 *
 */

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        int left = 0, right = 0;
        unordered_set<char> st;
        int maxLen = INT_MIN;

        for(char ch : s){
            if(st.find(ch) == st.end()){
                st.insert(ch);
                maxLen = max(maxLen, (right - left + 1));
                right++;
            } else {
                st.erase(s[left]);
                left++;
            }
        }
        return maxLen;
    }
};