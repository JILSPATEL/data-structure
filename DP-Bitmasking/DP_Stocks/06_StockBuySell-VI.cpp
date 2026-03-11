/**
 * Problem: Best Time to Buy and Sell Stock with Transaction Fee
 *
 * We are given an array prices where prices[i] represents the price of a stock
 * on day i. We are also given an integer k which represents the transaction fee.
 *
 * Each time we SELL a stock, we must pay the transaction fee k.
 *
 * We can perform unlimited transactions but:
 *    - We must SELL before we BUY again.
 *
 * ------------------------------------------------------------
 * Dynamic Programming Idea
 *
 * At each day we decide:
 *
 * 1. Buy the stock
 * 2. Sell the stock
 * 3. Skip the day
 *
 * We track two states:
 *
 * dp[i][buy]
 *
 * i   → current day
 * buy → whether we can buy (1) or we must sell (0)
 *
 *
 * State Meaning
 *
 * buy = 1 → we can BUY a stock
 * buy = 0 → we must SELL the stock
 *
 *
 * ------------------------------------------------------------
 * Recurrence Relation
 *
 * Case 1: buy == 1
 *
 * Option 1 → Buy stock
 *      profit = -prices[i] + dp[i+1][0]
 *
 * Option 2 → Skip
 *      profit = dp[i+1][1]
 *
 * dp[i][1] =
 *      max(-prices[i] + dp[i+1][0],
 *          dp[i+1][1])
 *
 *
 * Case 2: buy == 0
 *
 * Option 1 → Sell stock
 *      profit = prices[i] - fee + dp[i+1][1]
 *
 * Option 2 → Skip
 *      profit = dp[i+1][0]
 *
 * dp[i][0] =
 *      max(prices[i] - fee + dp[i+1][1],
 *          dp[i+1][0])
 *
 *
 * ------------------------------------------------------------
 * Base Case
 *
 * When we reach the end of the array:
 *
 *      dp[n][0] = dp[n][1] = 0
 *
 *
 * ------------------------------------------------------------
 * Time Complexity
 *
 * O(n * 2)
 *
 *
 * Space Complexity
 *
 * Memoization : O(n * 2)
 * Tabulation  : O(n * 2)
 */


 //Memoization

class Solution {
  public:

    int solve(int i,int buy,vector<int>& prices,int fee,
              vector<vector<int>>& dp){

        if(i==prices.size()) return 0;

        if(dp[i][buy]!=-1) return dp[i][buy];

        if(buy){
            return dp[i][buy]=max(
                -prices[i]+solve(i+1,0,prices,fee,dp),
                solve(i+1,1,prices,fee,dp)
            );
        }
        else{
            return dp[i][buy]=max(
                prices[i]-fee+solve(i+1,1,prices,fee,dp),
                solve(i+1,0,prices,fee,dp)
            );
        }
    }

    int maxProfit(vector<int>& prices, int fee) {

        int n=prices.size();

        vector<vector<int>> dp(n,vector<int>(2,-1));

        return solve(0,1,prices,fee,dp);
    }
};

 //Tabulation

class Solution {
  public:
    int maxProfit(vector<int>& prices, int fee) {

        int n = prices.size();

        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int idx = n - 1; idx >= 0; idx--) {
            for (int buy = 0; buy <= 1; buy++) {

                if (buy) {
                    dp[idx][buy] = max(
                        -prices[idx] + dp[idx + 1][0],
                        dp[idx + 1][1]
                    );
                } 
                else {
                    dp[idx][buy] = max(
                        prices[idx] - fee + dp[idx + 1][1],
                        dp[idx + 1][0]
                    );
                }

            }
        }

        return dp[0][1];
    }
};
