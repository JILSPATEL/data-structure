/**
 * Problem: Subarrays With K Distinct Integers
 *
 * Description:
 * Given an integer array `nums` and an integer `k`, return the number of
 * good subarrays of `nums` with exactly `k` distinct integers.
 *
 * Key Idea:
 * Exactly K = At Most K - At Most (K - 1)
 *
 * Approach 1: Brute Force (Not Used)
 * - Generate all subarrays.
 * - Count distinct elements using set/map.
 * - Time Complexity: O(n^2)
 *
 * Approach 2: Sliding Window + Frequency Map (Optimal - Used)
 * - Count subarrays with at most K distinct elements.
 * - Use two pointers (left, right).
 * - Expand window → include nums[right].
 * - If distinct elements exceed K → shrink window.
 * - For each right, number of valid subarrays = (right - left + 1).
 *
 * Final Answer:
 * subarraysWithKDistinct = atMost(K) - atMost(K-1)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n) (for map)
 */

class Solution {
public:
    int solve(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> mp;  // FIX: should be int, not char

        int left = 0, right = 0;
        int cnt = 0;

        while (right < n) {
            // If new distinct element
            if (mp[nums[right]] == 0) {
                k--;
            }

            mp[nums[right]]++;

            // Shrink window if more than k distinct
            while (k < 0) {
                mp[nums[left]]--;

                if (mp[nums[left]] == 0) {
                    k++;
                }

                left++;
            }

            // Count valid subarrays ending at right
            cnt += (right - left + 1);
            right++;
        }

        return cnt;
    }

    int subarraysWithKDistinct(vector<int>& nums, int k) {
        return solve(nums, k) - solve(nums, k - 1);
    }
};