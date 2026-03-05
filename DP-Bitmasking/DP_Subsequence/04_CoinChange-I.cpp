/**
Coin Change Problem

Given an array of coin denominations `coins` and an integer `amount`,
return the minimum number of coins required to make up that amount.
If it is not possible to form the amount using the given coins, return -1.

You can use each coin unlimited times.

Example:
coins = [1,2,5], amount = 11
Output = 3
Explanation: 11 = 5 + 5 + 1

The idea is to find the minimum coins needed to reach the target.
For each coin we have two choices:
1. Skip the coin and move to the previous coin.
2. Take the coin (if its value is ≤ target) and reduce the target.

We take the minimum of both choices.
If the target cannot be formed, we return a large value (1e9) and later convert it to -1.

Time Complexity: O(N * Amount)
Space Complexity: O(N * Amount)
*/


/* ================= APPROACH 1 : MEMOIZATION (Top Down DP) ================= */

class Solution {
public:
    int solve(int idx, vector<int> &coin, int tar, vector<vector<int>> &dp){
        
        // Base Case
        if(idx == 0){
            if(tar % coin[idx] == 0) return tar / coin[idx];
            else return 1e9;
        }

        if(dp[idx][tar] != -1) return dp[idx][tar];

        int skip = solve(idx-1, coin, tar, dp);

        int take = 1e9;
        if(coin[idx] <= tar){
            take = 1 + solve(idx, coin, tar - coin[idx], dp);
        }

        return dp[idx][tar] = min(take, skip);
    }

    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount+1, -1));

        int ans = solve(n-1, coins, amount, dp);

        return (ans >= 1e9) ? -1 : ans;
    }
};



/* ================= APPROACH 2 : TABULATION (Bottom Up DP) ================= */

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        
        int n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount+1, 0));

        // Base Case
        for(int t = 0; t <= amount; t++){
            if(t % coins[0] == 0) dp[0][t] = t / coins[0];
            else dp[0][t] = 1e9;
        }

        for(int i = 1; i < n; i++){
            for(int t = 0; t <= amount; t++){

                int skip = dp[i-1][t];

                int take = 1e9;
                if(coins[i] <= t){
                    take = 1 + dp[i][t - coins[i]];
                }

                dp[i][t] = min(take, skip);
            }
        }

        int ans = dp[n-1][amount];
        return (ans >= 1e9) ? -1 : ans;
    }
}