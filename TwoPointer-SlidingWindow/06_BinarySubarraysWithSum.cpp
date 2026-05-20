/**
 * Problem: Number of Subarrays with Sum = Goal
 * 
 * Description:
 * Given a binary array nums and an integer goal, return the number of non-empty
 * subarrays with a sum equal to goal.
 *
 * Approach:
 * 1. Use Sliding Window to count subarrays with sum ≤ goal.
 * 2. Use helper logic:
 *      count(goal) - count(goal - 1)
 *    This gives exact subarrays with sum = goal.
 * 3. Expand right pointer, shrink left when sum exceeds goal.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
public:

    // Helper function: count subarrays with sum <= goal
    int countSubarrays(vector<int>& nums, int goal) {
        if (goal < 0) return 0;

        int l = 0, sum = 0, cnt = 0;
        int n = nums.size();

        for (int r = 0; r < n; r++) {
            sum += nums[r];

            while (sum > goal) {
                sum -= nums[l];
                l++;
            }

            cnt += (r - l + 1);
        }

        return cnt;
    }

    int numSubarraysWithSum(vector<int>& nums, int goal) {
        return countSubarrays(nums, goal) - countSubarrays(nums, goal - 1);
    }
};