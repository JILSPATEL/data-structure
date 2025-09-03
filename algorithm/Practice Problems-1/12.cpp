/*
Given a sequence of n numbers, representing the stock prices of a stock on different days, design a linear time algorithm to compute the maximum profit that you can make by buying and selling a stock exactly once, you can sell a stock only after you buy it.
*/
#include <bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices) {
    int min_price=INT_MAX;
    int max_profit=0;

    for(int p:prices){
        if(p<min_price){
            min_price=p;
        }
        int profit=p-min_price;
        if(profit>max_profit){
            max_profit=profit;
        }
    }
    return max_profit;
}

int main() {
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << "Maximum Profit = " << maxProfit(prices) << endl;
    return 0;
}