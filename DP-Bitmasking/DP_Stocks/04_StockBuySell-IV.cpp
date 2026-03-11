/**
 * Problem: Best Time to Buy and Sell Stock IV
 *
 * We are given an array `prices` where prices[i] represents the price of a stock
 * on day i. We are also given an integer `k`, representing the maximum number of
 * transactions allowed. One transaction consists of:
 *
 *      1 Buy + 1 Sell
 *
 * The goal is to compute the maximum profit that can be achieved using at most
 * `k` transactions.
 *
 * ------------------------------------------------------------
 * Key Idea (Dynamic Programming)
 *
 * At every day we have two choices:
 *
 * 1. Buy the stock (if we are allowed to buy)
 * 2. Sell the stock (if we already bought)
 * 3. Skip the current day
 *
 * To model this, we maintain three states:
 *
 * State Definition:
 *
 * dp[i][buy][cap]
 *
 * i   → current day index
 * buy → whether we can buy (1) or must sell (0)
 * cap → remaining transactions
 *
 *
 * Meaning of states:
 *
 * buy = 1 → we are allowed to BUY
 * buy = 0 → we must SELL (because we already bought)
 *
 * cap = remaining number of transactions left.
 *
 *
 * ------------------------------------------------------------
 * Recurrence Relation
 *
 * Case 1: buy == 1 (we can buy stock)
 *
 * Option 1 → Buy stock
 *      profit = -prices[i] + dp[i+1][0][cap]
 *
 * Option 2 → Skip the day
 *      profit = dp[i+1][1][cap]
 *
 * dp[i][1][cap] = max(
 *                     -prices[i] + dp[i+1][0][cap],
 *                     dp[i+1][1][cap]
 *                    )
 *
 *
 * Case 2: buy == 0 (we must sell stock)
 *
 * Option 1 → Sell stock
 *      profit = prices[i] + dp[i+1][1][cap-1]
 *
 * Option 2 → Skip the day
 *      profit = dp[i+1][0][cap]
 *
 * dp[i][0][cap] = max(
 *                     prices[i] + dp[i+1][1][cap-1],
 *                     dp[i+1][0][cap]
 *                    )
 *
 *
 * ------------------------------------------------------------
 * Base Cases
 *
 * 1. If we reach the end of the array:
 *
 *        dp[n][*][*] = 0
 *
 *    because no days remain to trade.
 *
 * 2. If no transactions remain:
 *
 *        dp[*][*][0] = 0
 *
 *
 * ------------------------------------------------------------
 * Time Complexity
 *
 * O(n * 2 * k)
 *
 * because we compute states for:
 *    n days
 *    2 buy states
 *    k transaction capacities
 *
 *
 * Space Complexity
 *
 * Memoization: O(n * 2 * k) + recursion stack
 * Tabulation : O(n * 2 * k)
 *
 */


 // Memoization

 class Solution {
public:

    int solve(int i,int buy,int cap,vector<int>& prices,
              vector<vector<vector<int>>>& dp){

        if(i==prices.size() || cap==0) return 0;

        if(dp[i][buy][cap]!=-1) return dp[i][buy][cap];

        if(buy){
            return dp[i][buy][cap]=max(
                -prices[i]+solve(i+1,0,cap,prices,dp),
                solve(i+1,1,cap,prices,dp)
            );
        }
        else{
            return dp[i][buy][cap]=max(
                prices[i]+solve(i+1,1,cap-1,prices,dp),
                solve(i+1,0,cap,prices,dp)
            );
        }
    }

    int maxProfit(vector<int>& prices, int k) {

        int n=prices.size();

        vector<vector<vector<int>>> dp(n,
            vector<vector<int>>(2,vector<int>(k+1,-1)));

        return solve(0,1,k,prices,dp);
    }
};


//Tabulation

class Solution {
public:
    int maxProfit(vector<int>& prices, int k) {

        int n = prices.size();

        vector<vector<vector<int>>> dp(n + 1,
            vector<vector<int>>(2, vector<int>(k + 1, 0)));

        for(int i=n-1;i>=0;i--){
            for(int buy=0;buy<=1;buy++){
                for(int cap=1;cap<=k;cap++){

                    if(buy){
                        dp[i][buy][cap]=max(
                            -prices[i]+dp[i+1][0][cap],
                            dp[i+1][1][cap]
                        );
                    }
                    else{
                        dp[i][buy][cap]=max(
                            prices[i]+dp[i+1][1][cap-1],
                            dp[i+1][0][cap]
                        );
                    }

                }
            }
        }

        return dp[0][1][k];
    }
};