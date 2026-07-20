/*
Problem Statement:
You are climbing a staircase with n steps.
In one move, you can take either 1 step or 2 steps.
Count the number of distinct ways to reach the top.

Approach:
Use dynamic programming.
Let dp[i] be the number of ways to reach step i.
Base cases: dp[0] = 1 and dp[1] = 1.
For i >= 2, dp[i] = dp[i-1] + dp[i-2].

Intuition:
To reach step i, the last move must come from either step i-1 or step i-2.
So the total number of ways to reach i is the sum of the ways to reach those two previous steps.

Example:
For n = 5, the number of ways is 8.
*/

//Memoization
class Solution {
public: 
    int solve(int i,vector<int> &dp){
        if(i==0) return 1;
        if(i==1) return 1;
        if(dp[i]!=-1) return dp[i];

        return dp[i]=solve(i-1,dp)+solve(i-2,dp);
    }
    int climbStairs(int n) {
        vector<int> dp(n+1,-1);
        return solve(n,dp);
    }
};

//Tabulation
class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1,0);
        dp[0]=1;
        dp[1]=1;

        for(int i=2;i<=n;i++){
            dp[i]=dp[i-1]+dp[i-2];
        }
        return dp[n];
    }
};