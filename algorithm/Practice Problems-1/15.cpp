/*
Given a sequence of n numbers, representing the stock prices of a
stock on different days, design a linear time algorithm to compute
the maximum profit that you can make by buying and selling a stock
exactly once, you can sell a stock at most k days after you bought it.
*/

#include <bits/stdc++.h>
using namespace std;

int maxProfitWithCooldown(vector<int> &prices,int k){
    int n=prices.size();
    if(n<2) return 0;
    deque<int>dq;
    int maxProfit=0;

    for (int j=0; j < n; j++){
        while(!dq.empty() && dq.front()<j-k){
            dq.pop_front();
        }
        if(!dq.empty() && dq.front()<j){
            maxProfit=max(maxProfit,prices[j]-prices[dq.front()]);
        }
        while (!dq.empty() && prices[dq.back()] >= prices[j])
            dq.pop_back();

        dq.push_back(j);
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