/**
Coin Change II Problem (Number of Ways)

Given an integer array `coins` representing different coin denominations
and an integer `amount`, return the total number of combinations that
make up that amount.

You have an infinite number of each kind of coin.

Important:
The order of coins does NOT matter. We count combinations, not permutations.

Example:
coins = [1,2,5], amount = 5

Possible combinations:
1+1+1+1+1
1+1+1+2
1+2+2
5

Output = 4

Idea:
For every coin we have two choices:
1. Skip the coin → move to previous index
2. Take the coin → stay at same index because coins are unlimited

Total ways = take + skip

Base Case:
If we are at index 0, we can only use the first coin.
If amount is divisible by that coin → 1 way
otherwise → 0 ways

Time Complexity: O(N * Amount)
Space Complexity: O(N * Amount)
*/


/* ================= APPROACH 1 : MEMOIZATION (Top Down DP) ================= */

class Solution {
public:

    int solve(int idx, int tar, vector<int> &coins, vector<vector<int>> &dp){

        if(idx == 0){
            return (tar % coins[0] == 0);
        }

        if(dp[idx][tar] != -1) 
            return dp[idx][tar];

        int skip = solve(idx-1, tar, coins, dp);

        int take = 0;
        if(coins[idx] <= tar){
            take = solve(idx, tar - coins[idx], coins, dp);
        }

        return dp[idx][tar] = take + skip;
    }

    int change(int amount, vector<int>& coins) {

        int n = coins.size();

        vector<vector<int>> dp(n, vector<int>(amount+1, -1));

        return solve(n-1, amount, coins, dp);
    }
};



/* ================= APPROACH 2 : TABULATION (Bottom Up DP) ================= */

class Solution {
public:
    int change(int amount, vector<int>& coins) {

        int n = coins.size();

        vector<vector<int>> dp(n, vector<int>(amount+1, 0));

        // Base Case
        for(int t = 0; t <= amount; t++){
            if(t % coins[0] == 0)
                dp[0][t] = 1;
        }

        for(int i = 1; i < n; i++){
            for(int t = 0; t <= amount; t++){

                int skip = dp[i-1][t];

                int take = 0;
                if(coins[i] <= t){
                    take = dp[i][t - coins[i]];
                }

                dp[i][t] = take + skip;
            }
        }

        return dp[n-1][amount];
    }
}