/************************************************************
 Problem: House Robber (Dynamic Programming)

 Description:
 You are given an array `nums` where nums[i] represents the
 amount of money in the i-th house.
 You cannot rob two adjacent houses.

 The task is to find the maximum amount of money you can rob
 without alerting the police.

 ------------------------------------------------------------
 Key Idea:
 At each house, you have two choices:
 1. Rob the current house and skip the next one.
 2. Skip the current house and move to the next one.

 We choose the option that gives the maximum profit.

 ------------------------------------------------------------
 Recursive Relation:
 Let dp[i] be the maximum money that can be robbed starting
 from house i.

 dp[i] = max(
             nums[i] + dp[i + 2],   // rob current house
             dp[i + 1]              // skip current house
          )

 Base Case:
 - If i >= number of houses, return 0.

 ------------------------------------------------------------
 Optimization:
 The recursive solution has overlapping subproblems.
 To avoid recomputation, we use memoization with a DP array.

 ------------------------------------------------------------
 Time Complexity:
 - Each state is computed once: O(n)

 Space Complexity:
 - DP array: O(n)
 - Recursion stack: O(n)

************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int solve(int i, vector<int>& nums, vector<int>& dp) {
        int n = nums.size();

        if (i >= n)
            return 0;

        if (dp[i] != -1)
            return dp[i];

        int take = nums[i] + solve(i + 2, nums, dp);
        int skip = solve(i + 1, nums, dp);

        dp[i] = max(take, skip);
        return dp[i];
    }

    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, -1);
        return solve(0, nums, dp);
    }
};
