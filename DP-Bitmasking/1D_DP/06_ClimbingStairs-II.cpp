/*
Problem Statement:
You are given n stairs and an array costs.
At each step, you may jump 1, 2, or 3 steps.
If you jump j steps from stair i-j to i, the cost added is costs[i-1] + j*j.
Find the minimum total cost to reach the top.

Approach:
Use dynamic programming.
Let dp[i] be the minimum cost to reach stair i.
For each i, try all possible previous steps i-1, i-2, and i-3.

Intuition:
To reach stair i, we should choose the previous stair that gives the smallest total cost.
The transition is:
    dp[i] = min(dp[i-j] + costs[i-1] + j*j)
for j = 1 to 3.

Example:
For n = 4 and costs = [1, 100, 1, 1], the minimum cost is 9.
*/

//Memoization
class Solution {
public:
    int solve(int i,vector<int> &costs,vector<int> &dp){
        if(i==0) return 0;
        if(dp[i]!=-1) return dp[i];

        int ans=INT_MAX;

        for(int j=1;j<=3;j++){
            int prev=i-j;
            if(prev>=0){
                ans=min(ans,solve(prev,costs,dp)+costs[i-1]+j*j);
            }
        }
        return dp[i]=ans;
    }
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n+1,-1);
        return solve(n,costs,dp);
    }
};

//Tabulation
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n + 1, INT_MAX);

        dp[0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= 3; j++) {
                int prev = i - j;

                if (prev >= 0) {
                    dp[i] = min(dp[i],
                                dp[prev] + costs[i - 1] + j * j);
                }
            }
        }

        return dp[n];
    }
};