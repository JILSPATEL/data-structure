/*
13. Given a sequence of n numbers, representing the stock prices of a stock on different days, design a linear time algorithm to compute the maximum profit that you can make by buying and selling a stock exactly once, you can sell a stock exactly k days after you bought it.
*/
#include <bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices, int k) {
    int n=prices.size();
    if(n<=k) return 0;

    int max_profit=INT_MIN;
    for (int i = 0; i < n-k+1; i++)
    {
        int profit=prices[i+k]-prices[i];
        max_profit=max(max_profit,profit);
    }
    return max_profit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int k = 2;
    
    int ans = maxProfit(prices, k);
    cout << "Maximum Profit = " << ans << endl;
    
    return 0;
}