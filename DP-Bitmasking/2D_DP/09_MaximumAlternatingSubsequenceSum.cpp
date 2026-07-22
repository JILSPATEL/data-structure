//Memoization
class Solution {
public:
    long long solve(int idx,vector<int> &nums,bool flag,vector<vector<long long>> &dp){
        if(idx>=nums.size()) return 0;
        if(dp[idx][flag]!=-1) return dp[idx][flag];
        long long skip=solve(idx+1,nums,flag,dp);
        int val=nums[idx];
        if(flag!=true){
            val=-1LL*val;
        }
        long long take=solve(idx+1,nums,!flag,dp)+val;
        return dp[idx][flag]=max(take,skip);
    }
    long long maxAlternatingSum(vector<int>& nums) {
        bool flag=true;
        int n=nums.size();
        vector<vector<long long>> dp(n, vector<long long>(2, -1));
        return solve(0,nums,flag,dp);
    }
};
//Tabulation
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n=nums.size();
        vector<vector<long long>> dp(n+1, vector<long long>(2, 0));
        for(int i=n-1;i>=0;i--){
            dp[i][1]=max(
                dp[i+1][1],
                1LL*nums[i]+dp[i+1][0]
            );

            dp[i][0]=max(
                dp[i+1][0],
                -1LL*nums[i]+dp[i+1][1]
            );
        }
        return dp[0][1];
    }
};