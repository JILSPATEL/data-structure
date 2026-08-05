/*
Description:
Count the number of ways to split the array into two groups such that both groups have sum at least k.

Approach / Intuition:
A partition is invalid if one group has sum < k. So instead of building valid partitions directly,
we count all subsets whose sum is less than k and subtract them from the total number of possible splits.
The DP state (idx, sum) tells us how many ways we can form a subset using elements from index idx onward
with current sum.

Example:
nums = [2, 3, 4], k = 5
Any subset with sum less than 5 is a bad subset, such as [2], [3], [2, 3].
We count these bad subsets, then remove their effect from the total number of partitions.
*/

// Memoization
class Solution {
public:
    const int MOD = 1e9 + 7;

    int n;
    vector<vector<int>> dp;

    int solve(int idx, int sum, vector<int>& nums, int k) {
        if (sum >= k)
            return 0;

        if (idx == n)
            return 1;

        if (dp[idx][sum] != -1)
            return dp[idx][sum];

        long long skip = solve(idx + 1, sum, nums, k);
        long long take = solve(idx + 1, sum + nums[idx], nums, k);

        return dp[idx][sum] = (skip + take) % MOD;
    }

    int countPartitions(vector<int>& nums, int k) {
        long long totalSum = 0;
        n = nums.size();

        for (int x : nums)
            totalSum += x;

        if (totalSum < 2LL * k)
            return 0;

        dp.assign(n, vector<int>(k, -1));

        long long badSubsets = solve(0, 0, nums, k);

        long long total = 1;
        for (int i = 0; i < n; i++)
            total = (total * 2) % MOD;

        long long ans = (total - (2 * badSubsets) % MOD + MOD) % MOD;

        return ans;
    }
};