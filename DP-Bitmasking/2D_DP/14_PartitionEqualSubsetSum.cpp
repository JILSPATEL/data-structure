/*
Problem: Partition Equal Subset Sum

Description:
Given an array, determine whether it can be split into two subsets with equal
sum.

Intuition:
If the total sum is odd, the array can never be split into two equal parts.
If the total sum is even, the problem becomes: can we find a subset whose sum
is exactly totalSum / 2?

Approach:
1. Compute the total sum.
2. If it is odd, return false.
3. Otherwise, solve a subset-sum problem for target = sum / 2.
4. Use DP to check whether the target can be formed using the given elements.

Example:
arr = [1, 5, 11, 5]
Total sum = 22, so target = 11.
One subset is [11] and the other is [1, 5, 5], so the answer is true.
*/

// Memoization

class Solution {
  public:
    int sum=0,n;
    vector<vector<int>> dp;
    bool solve(int idx, vector<int> &arr, int tar) {
		if (idx == n) {
			if (tar == 0)
				return true;
			return false;
		}
		if (dp[idx][tar] != -1)
			return dp[idx][tar];
		int take = 0;
		if (arr[idx] <= tar) {
			take = solve(idx + 1, arr, tar - arr[idx]);
		}
		int skip = solve(idx + 1, arr, tar);
		return dp[idx][tar] = (take || skip);
		
	}
    bool equalPartition(vector<int>& arr) {
        // code here
        sum=accumulate(begin(arr),end(arr),0);
        n=arr.size();
        if(sum%2!=0) return false;
        int tar=sum/2;
        dp.assign(n,vector<int>(tar+1,-1));
        return solve(0,arr,tar);
    }
};


// Tabulation

class Solution {
  public:
    int sum=0,n;
    vector<vector<int>> dp;
    bool equalPartition(vector<int>& arr) {
        // code here
        sum=accumulate(begin(arr),end(arr),0);
        n=arr.size();
        if(sum%2!=0) return false;
        int tar=sum/2;
        dp.assign(n,vector<int>(tar+1,0));
        
        for(int idx=0;idx<n;idx++){
            dp[idx][0]=1;
        }
        
        if(arr[0]<=tar)
            dp[0][arr[0]]=1;
        
        for(int idx=1;idx<n;idx++){
            for(int t=1;t<=tar;t++){
                int take=0;
                if(arr[idx]<=t){
                    take=dp[idx-1][t-arr[idx]];
                }
                int skip=dp[idx-1][t];
                dp[idx][t]=(take||skip);
            }
        }
        
        return dp[n-1][tar];
    }
};