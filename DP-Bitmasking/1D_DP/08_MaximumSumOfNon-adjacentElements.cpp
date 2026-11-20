
/*
Problem:
Given an array of numbers, find the maximum sum of elements such that
no two selected elements are adjacent.

Intuition:
At every index, there are only two choices:
1. Take the current element. The previous element cannot be taken, so
   continue from index - 2.
2. Skip the current element and continue from index - 1.

The best answer for an index is the maximum of these two choices.
The same smaller indexes are reached multiple times, so memoization
stores each result and avoids recomputing it.

Approach:
1. Start at the last index.
2. Compute the sum when the current element is taken:
   nums[idx] + solve(idx - 2, nums).
3. Compute the sum when the current element is skipped:
   solve(idx - 1, nums).
4. Store and return the larger value.
5. If the index is negative, return 0. For index 0, return nums[0].

Example:
nums = [2, 7, 9, 3, 1]

One optimal selection is 2 + 9 + 1 = 12.
The DP choices compare taking and skipping each element and return 12.

Time Complexity: O(n), because each index is solved once.
Space Complexity: O(n), for the memoization array and recursion stack.
*/

class Solution {
public:
    vector<int> dp;

    int solve(int idx, vector<int> &nums) {
        if (idx < 0) {
            return 0;
        }

        if (idx == 0) {
            return nums[0];
        }

        if (dp[idx] != -1) {
            return dp[idx];
        }

        int take = nums[idx] + solve(idx - 2, nums);
        int skip = solve(idx - 1, nums);

        return dp[idx] = max(take, skip);
    }

    int nonAdjacent(vector<int>& nums) {
        int n = nums.size();
        dp.assign(n, -1);

        return solve(n - 1, nums);
    }
};
