/**
 Problem: Partition Equal Subset Sum

 Given an integer array nums, determine whether it can be divided into two subsets
 such that the sum of elements in both subsets is equal.

 Explanation:
 If the array can be partitioned into two subsets with equal sum, then the total
 sum of the array must be even. Let totalSum be the sum of all elements.

 If totalSum is odd → partition is impossible.

 If totalSum is even → we need to check whether there exists a subset whose
 sum equals totalSum / 2.

 This becomes a classic Subset Sum problem.

 We solve it using Dynamic Programming.

 Approaches:
 1. Memoization (Top-Down DP / Recursion + Caching)
 2. Tabulation (Bottom-Up DP)

 State Definition:
 dp[idx][tar] → whether we can form sum "tar" using elements from index idx onward.

 Choices:
 1. Take the current element
 2. Skip the current element

 Final Answer:
 Check if we can form subset with sum = totalSum / 2.
*/


// Tabulation

class Solution {
public:
    bool canPartition(vector<int>& nums) {

        int total = accumulate(nums.begin(), nums.end(), 0);

        if (total % 2 != 0)
            return false;

        int target = total / 2;
        int n = nums.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        for (int i = 0; i <= n; i++)
            dp[i][0] = true;

        for (int i = 1; i <= n; i++) {

            for (int t = 1; t <= target; t++) {

                bool skip = dp[i - 1][t];
                bool take = false;

                if (nums[i - 1] <= t)
                    take = dp[i - 1][t - nums[i - 1]];

                dp[i][t] = take || skip;
            }
        }

        return dp[n][target];
    }
};

// Memorization

class Solution {
public:
    bool solve(int idx, int n, int tar, vector<int>& nums,
               vector<vector<int>>& dp) {

        if (tar == 0)
            return true;

        if (idx >= n || tar < 0)
            return false;

        if (dp[idx][tar] != -1)
            return dp[idx][tar];

        bool take = solve(idx + 1, n, tar - nums[idx], nums, dp);
        bool skip = solve(idx + 1, n, tar, nums, dp);

        return dp[idx][tar] = (take || skip);
    }

    bool canPartition(vector<int>& nums) {

        int total = accumulate(nums.begin(), nums.end(), 0);

        if (total % 2 != 0)
            return false;

        int target = total / 2;
        int n = nums.size();

        vector<vector<int>> dp(n, vector<int>(target + 1, -1));

        return solve(0, n, target, nums, dp);
    }
};