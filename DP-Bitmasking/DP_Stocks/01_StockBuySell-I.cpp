/**
 * Problem: Best Time to Buy and Sell Stock
 *
 * Description:
 * Given an array `arr` where arr[i] represents the price of a stock on the i-th day,
 * find the maximum profit that can be achieved by buying one stock and selling it later.
 * Only one transaction (buy once and sell once) is allowed.
 *
 * Approaches:
 *
 * 1. Brute Force Approach
 *    - Try every pair (buy day, sell day).
 *    - Calculate profit for all i < j.
 *    - Take the maximum profit.
 *    - Time Complexity: O(n^2)
 *
 * 2. Optimal One-Pass Approach (Used Below)
 *    - Track the minimum price seen so far.
 *    - At each day compute profit = current price - minimum price.
 *    - Update maximum profit if larger profit is found.
 *    - Time Complexity: O(n)
 *    - Space Complexity: O(1)
 */

class Solution {
public:
    int stockBuySell(vector<int> &arr) {

        int mini = arr[0];     // Minimum price seen so far
        int profit = 0;        // Maximum profit
        int n = arr.size();

        for (int i = 1; i < n; i++) {

            int cost = arr[i] - mini;   // Profit if sold today

            profit = max(profit, cost); // Update max profit

            mini = min(mini, arr[i]);   // Update minimum price
        }

        return profit;
    }
};