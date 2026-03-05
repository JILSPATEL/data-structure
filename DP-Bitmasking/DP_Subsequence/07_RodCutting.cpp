/*
Problem: Rod Cutting Problem

You are given:
price[] -> price[i] represents the value of a rod piece of length (i+1)

A rod of total length n is given. You can cut the rod into pieces of different
lengths and sell them.

Goal:
Maximize the total value obtained by cutting the rod.

Important:
You can use the same rod length multiple times (similar to Unbounded Knapsack).

-------------------------------------------------------------
Python Approach Explanation (Tabulation)

State:
dp[i][j]

i -> index of rod length (0 to n-1)
j -> current rod length we want to achieve

Meaning:
Maximum value obtainable using rod lengths [0..i] to form rod length j.

-------------------------------------------------------------
Base Case:

For i = 0 (rod length = 1)

We can cut the rod only into pieces of length 1.

dp[0][length] = length * price[0]

-------------------------------------------------------------
Transition:

For each rod length index i:

Choice 1: Skip current rod length
skip = dp[i-1][j]

Choice 2: Take current rod length
rodLen = i + 1

If rodLen <= j:
take = price[i] + dp[i][j - rodLen]

(Notice i stays same because we can reuse the same rod length)

dp[i][j] = max(skip, take)

-------------------------------------------------------------
Final Answer:

dp[n-1][n]

-------------------------------------------------------------
Time Complexity:  O(n²)
Space Complexity: O(n²)

Below are two C++ approaches:
1. Memoization (Top Down)
2. Tabulation (Bottom Up)
*/

// Approach 1: Memoization (Top Down)

class Solution {
public:

    int solve(int idx, int len, vector<int>& price, vector<vector<int>>& dp){

        if(idx == 0)
            return len * price[0];

        if(dp[idx][len] != -1)
            return dp[idx][len];

        int skip = solve(idx-1, len, price, dp);

        int take = INT_MIN;
        int rodLen = idx + 1;

        if(rodLen <= len)
            take = price[idx] + solve(idx, len - rodLen, price, dp);

        return dp[idx][len] = max(skip, take);
    }

    int cutRod(vector<int>& price) {
        int n = price.size();

        vector<vector<int>> dp(n, vector<int>(n+1, -1));

        return solve(n-1, n, price, dp);
    }
};

// Approach 2: Tabulation (Bottom Up)

class Solution {
public:

    int cutRod(vector<int>& price) {

        int n = price.size();

        vector<vector<int>> dp(n, vector<int>(n+1, 0));

        for(int len = 0; len <= n; len++)
            dp[0][len] = len * price[0];

        for(int i = 1; i < n; i++){
            for(int len = 0; len <= n; len++){

                int skip = dp[i-1][len];

                int take = 0;
                int rodLen = i + 1;

                if(rodLen <= len)
                    take = price[i] + dp[i][len - rodLen];

                dp[i][len] = max(skip, take);
            }
        }

        return dp[n-1][n];
    }
};