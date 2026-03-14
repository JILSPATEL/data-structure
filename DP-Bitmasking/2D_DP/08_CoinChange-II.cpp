/**
 * Problem: Coin Change – Count Ways
 *
 * We are given an array `coins[]` representing different coin denominations
 * and a target `sum`. We need to find the number of distinct ways to make
 * the given sum using the coins. Each coin can be used unlimited times.
 *
 * Order does NOT matter.
 *
 * Example:
 * coins = [1,2,3], sum = 4
 *
 * Ways:
 * 1+1+1+1
 * 1+1+2
 * 2+2
 * 1+3
 *
 * Total ways = 4
 *
 * ------------------------------------------------------------
 * INTUITION
 * ------------------------------------------------------------
 *
 * This is also an Unbounded Knapsack style problem.
 *
 * For every coin index we have two choices:
 *
 * 1. Skip the coin
 *    Move to the previous coin.
 *
 * 2. Take the coin
 *    If coin value <= sum, we take it and reduce the remaining sum.
 *    Since coins are unlimited, we stay at the same index.
 *
 * Example:
 *
 * coins = [1,2,3]
 * sum = 4
 *
 * solve(idx,4)
 *
 *        solve(2,4)
 *         /     \
 *      skip     take
 *   solve(1,4)  solve(2,1)
 *
 * The total number of ways is:
 *
 *      ways = skip + take
 *
 * ------------------------------------------------------------
 * BASE CASE
 * ------------------------------------------------------------
 *
 * When idx == 0:
 * Only coin[0] is available.
 *
 * If the remaining sum is divisible by coin[0],
 * then we can form the sum using only that coin.
 *
 *      sum % coins[0] == 0 → 1 way
 *
 * Otherwise:
 *
 *      0 ways
 *
 * ------------------------------------------------------------
 * DP STATE
 * ------------------------------------------------------------
 *
 * dp[idx][sum]
 *
 * Meaning:
 * Number of ways to make `sum`
 * using coins from index [0...idx].
 *
 * ------------------------------------------------------------
 * TIME COMPLEXITY
 * ------------------------------------------------------------
 *
 * O(N * SUM)
 *
 * ------------------------------------------------------------
 * SPACE COMPLEXITY
 * ------------------------------------------------------------
 *
 * O(N * SUM) + recursion stack
 *
 * ------------------------------------------------------------
 * APPROACH 1: MEMOIZATION (Top-Down DP)
 * ------------------------------------------------------------
 */

class Solution {
public:

    int solve(int idx,vector<int> &coins,int sum,vector<vector<int>> &dp){

        if(idx==0){
            return (sum % coins[0] == 0);
        }

        if(dp[idx][sum] != -1) return dp[idx][sum];

        int skip = solve(idx-1,coins,sum,dp);

        int take = 0;

        if(coins[idx] <= sum){
            take = solve(idx,coins,sum-coins[idx],dp);
        }

        return dp[idx][sum] = take + skip;
    }

    int count(vector<int>& coins, int sum) {

        int n = coins.size();

        vector<vector<int>> dp(n,vector<int>(sum+1,-1));

        int ans = solve(n-1,coins,sum,dp);

        return ans;
    }
};



/**
 * ------------------------------------------------------------
 * APPROACH 2: TABULATION (Bottom-Up DP)
 * ------------------------------------------------------------
 *
 * Instead of recursion, we fill the DP table iteratively.
 *
 * dp[i][s] = number of ways to make sum s using coins[0..i]
 *
 * Transition:
 *
 * skip = dp[i-1][s]
 *
 * take = dp[i][s - coins[i]]
 *
 * dp[i][s] = skip + take
 *
 * ------------------------------------------------------------
 */

class Solution {
public:
    int count(vector<int>& coins, int sum) {

        int n = coins.size();

        vector<vector<int>> dp(n,vector<int>(sum+1,0));

        for(int s=0; s<=sum; s++){
            if(s % coins[0] == 0) dp[0][s] = 1;
        }

        for(int i=1;i<n;i++){
            for(int s=0;s<=sum;s++){

                int skip = dp[i-1][s];

                int take = 0;

                if(coins[i] <= s){
                    take = dp[i][s-coins[i]];
                }

                dp[i][s] = skip + take;
            }
        }

        return dp[n-1][sum];
    }
};