/**
 * Problem: Best Time to Buy and Sell Stock II
 *
 * Description:
 * Given an array `prices` where prices[i] represents the stock price on the i-th day,
 * you can perform as many buy and sell transactions as you want. However:
 *
 * 1. You cannot hold multiple stocks at the same time.
 * 2. You must sell the stock before buying again.
 *
 * Goal:
 * Find the maximum profit that can be achieved.
 *
 * --------------------------------------------------------------------
 * Idea:
 * At every day (index), we have two possible states:
 *
 * 1. buy = 1 → We are allowed to BUY the stock.
 * 2. buy = 0 → We currently HOLD a stock and can SELL it.
 *
 * We try both possibilities at every index and take the maximum profit.
 *
 * State Representation:
 * dp[idx][buy]
 *
 * idx → current day
 * buy → whether we are allowed to buy (1) or must sell (0)
 *
 * Transitions:
 *
 * If buy == 1:
 *   Option 1 → Buy stock today
 *               profit = -prices[idx] + dp[idx+1][0]
 *   Option 2 → Skip buying
 *               profit = dp[idx+1][1]
 *
 * If buy == 0:
 *   Option 1 → Sell stock today
 *               profit = prices[idx] + dp[idx+1][1]
 *   Option 2 → Skip selling
 *               profit = dp[idx+1][0]
 *
 * Base Case:
 * If idx == n (past last day), profit = 0.
 *
 * --------------------------------------------------------------------
 * Tabulation Approach (Bottom-Up DP)
 *
 * Time Complexity  : O(n * 2)
 * Space Complexity : O(n * 2)
 *
 * We fill the dp table from the last day backwards.
 */

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for (int idx = n - 1; idx >= 0; idx--) {
            for (int buy = 0; buy <= 1; buy++) {
                if (buy) {
                    dp[idx][buy] = max(-prices[idx] + dp[idx + 1][0],
                                       dp[idx + 1][1]);
                } else {
                    dp[idx][buy] = max(prices[idx] + dp[idx + 1][1],
                                       dp[idx + 1][0]);
                }
            }
        }

        return dp[0][1];
    }
};

//Memoization

class Solution {
public:
    int solve(int idx, int buy, vector<int>& prices, vector<vector<int>>& dp) {
        if (idx == prices.size()) return 0;

        if (dp[idx][buy] != -1) return dp[idx][buy];

        int profit = 0;

        if (buy) {
            profit = max(-prices[idx] + solve(idx + 1, 0, prices, dp),
                         solve(idx + 1, 1, prices, dp));
        } 
        else {
            profit = max(prices[idx] + solve(idx + 1, 1, prices, dp),
                         solve(idx + 1, 0, prices, dp));
        }

        return dp[idx][buy] = profit;
    }

    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solve(0, 1, prices, dp);
    }
};