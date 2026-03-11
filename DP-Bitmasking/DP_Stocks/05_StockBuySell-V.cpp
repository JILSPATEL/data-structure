/**
 * Problem: Best Time to Buy and Sell Stock with Cooldown
 *
 * You are given an array `arr` where arr[i] represents the stock price on day i.
 * You may perform multiple buy/sell transactions but with the following rules:
 *
 * 1. You can hold only one stock at a time.
 * 2. After selling a stock, you must wait for one day before buying again
 *    (this is called the cooldown period).
 *
 * Goal:
 * Find the maximum profit you can achieve.
 *
 * Idea:
 * We use Dynamic Programming where the state depends on:
 *  - current day (i)
 *  - whether we are allowed to buy (buy = 1) or must sell (buy = 0)
 *
 * State Meaning:
 * dp[i][buy]
 *
 * buy = 1 → we can buy stock at day i
 * buy = 0 → we currently hold stock and can sell
 *
 * Transitions:
 *
 * If buy == 1:
 *  Option 1: Buy stock today
 *            profit = -arr[i] + dp[i+1][0]
 *  Option 2: Skip buying
 *            profit = dp[i+1][1]
 *
 * If buy == 0:
 *  Option 1: Sell stock today
 *            profit = arr[i] + dp[i+2][1]
 *            (i+2 because of cooldown)
 *  Option 2: Skip selling
 *            profit = dp[i+1][0]
 *
 * Base Case:
 * If i >= n → profit = 0
 *
 * We fill the DP table from back (bottom-up).
 *
 * Time Complexity:  O(N)
 * Space Complexity: O(N)
 *
 * This implementation uses Tabulation.
 *
 * Other possible approaches:
 * 1. Recursion
 * 2. Memoization
 * 3. Tabulation
 * 4. Space Optimization
 */

 //Memoization

class Solution {
public:

    long long solve(int i,int buy,vector<int>& arr,vector<vector<long long>>& dp){
        int n = arr.size();

        if(i >= n) return 0;

        if(dp[i][buy] != -1) return dp[i][buy];

        if(buy){
            return dp[i][buy] = max(-arr[i] + solve(i+1,0,arr,dp),
                                     solve(i+1,1,arr,dp));
        }
        else{
            return dp[i][buy] = max(arr[i] + solve(i+2,1,arr,dp),
                                     solve(i+1,0,arr,dp));
        }
    }

    int maxProfit(vector<int>& arr) {
        int n = arr.size();

        vector<vector<long long>> dp(n, vector<long long>(2,-1));

        return solve(0,1,arr,dp);
    }
};

 //Tabulation

 class Solution {
public:
    int maxProfit(vector<int>& arr) {

        int n = arr.size();

        vector<vector<long long>> dp(n+2, vector<long long>(2,0));

        for(int i=n-1;i>=0;i--){

            for(int buy=0;buy<=1;buy++){

                if(buy){
                    dp[i][buy] = max(-arr[i] + dp[i+1][0],
                                       dp[i+1][1]);
                }
                else{
                    dp[i][buy] = max(arr[i] + dp[i+2][1],
                                       dp[i+1][0]);
                }

            }
        }

        return dp[0][1];
    }
};