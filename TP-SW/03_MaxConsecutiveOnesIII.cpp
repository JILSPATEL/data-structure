/**
 * Problem: Max Consecutive Ones III
 * ----------------------------------------------------------
 * Given a binary array nums and an integer k, return the maximum
 * number of consecutive 1's in the array if you can flip at most
 * k 0's.
 *
 * Approach Used: Sliding Window
 * ----------------------------------------------------------
 * - Maintain a window [left, right]
 * - Count number of zeros in current window
 *
 * Algorithm:
 * 1. Expand window by moving 'right':
 *      - If nums[right] == 0, increment zero count
 *
 * 2. If zero count exceeds k:
 *      - Shrink window from left
 *      - If nums[left] == 0, decrement zero count
 *
 * 3. At every step, window is valid (zeroCnt <= k)
 *      - Update max length
 *
 * 4. Continue until end of array
 *
 * Key Insight:
 * ----------------------------------------------------------
 * We are allowed to flip at most k zeros, so the window can
 * contain at most k zeros at any time.
 *
 * Time Complexity: O(n)
 *      Each element is visited at most twice
 *
 * Space Complexity: O(1)
 *      No extra space used
 *
 * Example:
 * nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
 * Output: 6
 *
 * Window Explanation:
 * ----------------------------------------------------------
 * Longest valid window after flipping at most 2 zeros:
 * [1,1,1,0,0,1,1,1,1] → length = 6
 */

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        int zeroCnt = 0;
        int left = 0, right = 0;
        int maxLen = 0;

        while (right < n) {
            if (nums[right] == 0) {
                zeroCnt++;
            }

            while (zeroCnt > k) {
                if (nums[left] == 0) {
                    zeroCnt--;
                }
                left++;
            }

            maxLen = max(maxLen, right - left + 1);
            right++;
        }

        return maxLen;
    }
};