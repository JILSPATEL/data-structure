/*
Problem:
Given integers N, M, and K, count how many arrays of length N exist where each element is between 1 and M,
and the array's search cost equals exactly K. The search cost is the number of times a new maximum appears
when traversing the array from left to right.

Approach:
Use dynamic programming to build the array one element at a time, tracking:
- idx: how many positions have been filled,
- searchCost: how many times the maximum has increased so far,
- maxSoFar: the current maximum value in the array.

For each next value i in [1, M]:
- if i > maxSoFar, the search cost increases by 1 and the new maximum becomes i.
- otherwise, the search cost remains unchanged and the maximum stays maxSoFar.

Two DP variants are shown:
1) Memoization (top-down recursion with memo cache).
2) Tabulation (bottom-up iteration with 3D DP table).

Example:
N = 3, M = 3, K = 2
Valid arrays include [1, 3, 2] and [2, 1, 3].
Each array is counted only if exactly two new maximums are observed while scanning left to right.
*/

// Memoization
class Solution {
public:
    int n,m,k;
    int dp[51][51][101];
    const int MOD=1000000007;
    int solve(int idx,int searchCost,int maxSoFar){
        if(idx==n){
            if(searchCost==k) return 1;
            return 0;
        }
        if(dp[idx][searchCost][maxSoFar]!=-1) return dp[idx][searchCost][maxSoFar];
        int res=0;
        for(int i=1;i<=m;i++){
            if(i>maxSoFar){
                res=(res+solve(idx+1,searchCost+1,i))%MOD;
            }else{
                res=(res+solve(idx+1,searchCost,maxSoFar))%MOD;
            }
        }
        return dp[idx][searchCost][maxSoFar]=res%MOD;
    }
    int numOfArrays(int N, int M, int K) {
        n=N;
        m=M;
        k=K;
        memset(dp,-1,sizeof(dp));
        return solve(0,0,0);
    }
};


// Tabulation
class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        const int MOD = 1000000007;
        long long dp[51][51][101] = {0};
        dp[0][0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= k; j++) {
                for (int l = 1; l <= m; l++) {
                    for (int prev = 0; prev < l; prev++) {
                        dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j - 1][prev]) % MOD;
                    }
                    for (int prev = l; prev <= m; prev++) {
                        dp[i][j][l] = (dp[i][j][l] + dp[i - 1][j][prev]) % MOD;
                    }
                }
            }
        }
        long long result = 0;
        for (int i = 1; i <= m; i++) {
            result = (result + dp[n][k][i]) % MOD;
        }
        return result;
    }
};
