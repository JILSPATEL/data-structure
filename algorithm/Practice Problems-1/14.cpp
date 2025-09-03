/*
Given a sequence of n numbers, representing the stock prices of a
stock on different days, design a linear time algorithm to compute
the maximum profit that you can make by buying and selling a stock
exactly once, you can sell a stock at least k days after you bought it.
*/

#include <bits/stdc++.h>
using namespace std;

int maxProfitWithCooldown(vector<int> &prices,int k){
    int n=prices.size();
    if(n<=k) return 0;
    int maxProfit=0;
    int minPrice=prices[0];

    for (int j=k; j < n; j++){
        minPrice=min(minPrice,prices[j-k]);
        maxProfit=max(maxProfit,prices[j]-minPrice);
    }
    return maxProfit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    int k = 2;
    
    int ans = maxProfitWithCooldown(prices, k);
    cout << "Maximum Profit = " << ans << endl;
    
    return 0;
}