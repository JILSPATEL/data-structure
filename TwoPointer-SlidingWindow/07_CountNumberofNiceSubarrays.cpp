/**
 * Problem: Count Number of Nice Subarrays
 * --------------------------------------
 * Given an array of integers nums and an integer k,
 * return the number of subarrays with exactly k odd numbers.
 *
 * Approach:
 * ----------
 * 1. Sliding Window + At Most Technique:
 *    - Count subarrays with at most k odd numbers.
 *    - Count subarrays with at most (k - 1) odd numbers.
 *    - Exact k = atMost(k) - atMost(k - 1)
 *
 * 2. Why it works:
 *    - atMost(k) includes all subarrays having <= k odd numbers
 *    - Subtracting atMost(k-1) removes subarrays with < k odds
 *    - Remaining = exactly k odds
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
public:
    // Helper function: count subarrays with at most k odd numbers
    int atMost(vector<int> &nums, int k) {
        if (k < 0) return 0;

        int left = 0, sum = 0, cnt = 0;
        int n = nums.size();

        for (int right = 0; right < n; right++) {
            // Add 1 if odd, 0 if even
            sum += nums[right] % 2;

            // Shrink window if odd count exceeds k
            while (sum > k) {
                sum -= nums[left] % 2;
                left++;
            }

            // Count valid subarrays ending at 'right'
            cnt += (right - left + 1);
        }

        return cnt;
    }

    int numberOfSubarrays(vector<int>& nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }
};