/**
 * Problem: Minimum Coins (Coin Change)
 *
 * We are given an array `coins[]` representing different coin denominations
 * and a target `sum`. We need to find the minimum number of coins required
 * to make the given sum. Each coin can be used unlimited times.
 *
 * If it is not possible to make the sum using the given coins, return -1.
 *
 * -------------------------------------------------------------
 * INTUITION
 * -------------------------------------------------------------
 * This problem is a classic Unbounded Knapsack / Coin Change problem.
 *
 * At every coin index we have two choices:
 *
 * 1. Skip the coin
 *    Move to the previous coin and try to make the same target.
 *
 * 2. Take the coin
 *    If the coin value is <= target, we take it and reduce the target
 *    by that coin value. Since coins can be used multiple times,
 *    we stay at the same index.
 *
 * Example:
 * coins = [1,2,5], sum = 11
 *
 * If we are at coin 5:
 *
 *      solve(idx,11)
 *        /        \
 *     skip        take
 * solve(idx-1,11) 1 + solve(idx,6)
 *
 * We explore both possibilities and take the minimum coins required.
 *
 * -------------------------------------------------------------
 * BASE CASE
 * -------------------------------------------------------------
 * When idx == 0:
 * We only have coin[0] available.
 *
 * If target is divisible by coin[0], we can make the sum using only that coin:
 *
 *      tar % coin[0] == 0
 *
 * number of coins = tar / coin[0]
 *
 * Otherwise it is impossible, so return a large value (1e9).
 *
 * -------------------------------------------------------------
 * OVERLAPPING SUBPROBLEMS
 * -------------------------------------------------------------
 * The same (idx, target) state may be computed many times.
 * We store results in DP table to avoid recomputation.
 *
 * State:
 *
 *      dp[idx][target]
 *
 * Meaning:
 * Minimum coins needed using coins[0...idx] to make target.
 *
 * -------------------------------------------------------------
 * TIME COMPLEXITY
 * -------------------------------------------------------------
 * O(N * SUM)
 *
 * -------------------------------------------------------------
 * SPACE COMPLEXITY
 * -------------------------------------------------------------
 * O(N * SUM) + recursion stack
 *
 * -------------------------------------------------------------
 * APPROACH 1: MEMOIZATION (Top-Down DP)
 * -------------------------------------------------------------
 */

class Solution {
public:

    int solve(int idx,int tar,vector<int> &coins,vector<vector<int>> &dp){
        
        if(idx==0){
            if(tar%coins[idx]==0) return tar/coins[idx];
            else return 1e9;
        }

        if(dp[idx][tar]!=-1) return dp[idx][tar];

        int skip = solve(idx-1,tar,coins,dp);

        int take = 1e9;

        if(tar >= coins[idx]){
            take = 1 + solve(idx,tar-coins[idx],coins,dp);
        }

        return dp[idx][tar] = min(skip,take);
    }

    int minCoins(vector<int> &coins, int sum) {

        int n = coins.size();

        vector<vector<int>> dp(n,vector<int>(sum+1,-1));

        int ans = solve(n-1,sum,coins,dp);

        return (ans>=1e9 ? -1 : ans);
    }
};



/**
 * -------------------------------------------------------------
 * APPROACH 2: TABULATION (Bottom-Up DP)
 * -------------------------------------------------------------
 *
 * Instead of recursion, we fill the DP table iteratively.
 *
 * dp[i][t] = minimum coins needed using coins[0..i] to make target t
 *
 * Transition:
 *
 * skip = dp[i-1][t]
 *
 * take = 1 + dp[i][t - coins[i]]    (since coin can be reused)
 *
 * dp[i][t] = min(skip, take)
 *
 */

class Solution {
public:
    int minCoins(vector<int> &coins, int sum) {

        int n = coins.size();
        vector<vector<int>> dp(n,vector<int>(sum+1,0));

        for(int t=0;t<=sum;t++){
            if(t % coins[0] == 0) dp[0][t] = t/coins[0];
            else dp[0][t] = 1e9;
        }

        for(int i=1;i<n;i++){
            for(int t=0;t<=sum;t++){

                int skip = dp[i-1][t];

                int take = 1e9;

                if(t >= coins[i]){
                    take = 1 + dp[i][t-coins[i]];
                }

                dp[i][t] = min(skip,take);
            }
        }

        int ans = dp[n-1][sum];

        return (ans>=1e9 ? -1 : ans);
    }
};