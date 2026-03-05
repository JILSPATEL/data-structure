/*
Problem: Unbounded Knapsack

You are given two arrays:
val[] -> value of items
wt[]  -> weight of items
and an integer capacity representing the maximum weight the knapsack can hold.

In the Unbounded Knapsack problem, you can take an item multiple times.

Goal:
Maximize the total value such that the total weight does not exceed capacity.

-------------------------------------------------------------
Python Approach Explanation (Top Down / Memoization)

solve(idx, cap):
- idx represents the current item index.
- cap represents the remaining capacity.

Base Case:
If idx == 0:
    Since we can take item 0 multiple times,
    maximum value = (cap / wt[0]) * val[0]

Choices:
1. Skip the current item:
   solve(idx-1, cap)

2. Take the current item (only if wt[idx] <= cap):
   val[idx] + solve(idx, cap - wt[idx])
   (Note: idx remains same because items are unlimited)

Store result in dp[idx][cap] to avoid recomputation.

Time Complexity: O(N * Capacity)
Space Complexity: O(N * Capacity)

-------------------------------------------------------------
Below are two C++ approaches:
1. Memoization (Top Down)
2. Tabulation (Bottom Up)
*/

//Memorizaton

class Solution {
public:

    int solve(int idx, int cap, vector<int>& val, vector<int>& wt, vector<vector<int>>& dp){

        if(idx == 0)
            return (cap / wt[0]) * val[0];

        if(dp[idx][cap] != -1)
            return dp[idx][cap];

        int skip = solve(idx-1, cap, val, wt, dp);

        int take = INT_MIN;
        if(wt[idx] <= cap)
            take = val[idx] + solve(idx, cap - wt[idx], val, wt, dp);

        return dp[idx][cap] = max(skip, take);
    }

    int knapSack(vector<int>& val, vector<int>& wt, int capacity){
        int n = val.size();

        vector<vector<int>> dp(n, vector<int>(capacity+1, -1));

        return solve(n-1, capacity, val, wt, dp);
    }
};

//Tabulation

class Solution {
public:
    int knapSack(vector<int>& val, vector<int>& wt, int capacity){

        int n = val.size();

        vector<vector<int>> dp(n, vector<int>(capacity+1, 0));

        for(int cap = 0; cap <= capacity; cap++)
            dp[0][cap] = (cap / wt[0]) * val[0];

        for(int i = 1; i < n; i++){
            for(int cap = 0; cap <= capacity; cap++){

                int skip = dp[i-1][cap];

                int take = INT_MIN;
                if(wt[i] <= cap)
                    take = val[i] + dp[i][cap - wt[i]];

                dp[i][cap] = max(skip, take);
            }
        }

        return dp[n-1][capacity];
    }
};