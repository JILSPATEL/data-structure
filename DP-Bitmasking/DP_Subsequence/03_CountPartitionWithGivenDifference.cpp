/**
 Problem: Count Partitions With Given Difference

 You are given an integer array `arr` and an integer `diff`. The task is to count
 the number of ways to partition the array into two subsets S1 and S2 such that:

            S1 - S2 = diff

 Explanation:

 Let:
        sum(S1) = s1
        sum(S2) = s2

 From the problem statement:
        s1 - s2 = diff

 Also, the sum of all elements in the array is:
        s1 + s2 = totalSum

 Adding the two equations:

        s1 - s2 = diff
        s1 + s2 = totalSum
        -----------------
        2*s1 = totalSum + diff

        s1 = (totalSum + diff) / 2

 Alternatively we can derive:

        s2 = (totalSum - diff) / 2

 So the problem reduces to counting the number of subsets whose sum equals:

        target = (totalSum - diff) / 2

 Edge Conditions:
 - If (totalSum - diff) < 0 → partition is impossible.
 - If (totalSum - diff) is odd → valid subset sum cannot exist.

 Therefore we return 0 in those cases.

 Approach (Memoization / Top-Down DP):

 We recursively decide for each element whether to:
        1. Take the element
        2. Skip the element

 State Definition:
        dp[idx][tar] = number of ways to form sum "tar"
                       using elements from index `idx` onward.

 Base Case:
 - If we reach the end of the array:
        If tar == 0 → one valid subset found.
        Otherwise → no valid subset.

 Transition:
        skip = solve(idx + 1, tar)
        take = solve(idx + 1, tar - arr[idx]) (only if arr[idx] ≤ tar)

        dp[idx][tar] = (take + skip) % mod

 Memoization avoids recomputation of overlapping subproblems.

 Final Answer:
        Count the number of subsets with sum = (totalSum - diff) / 2.

 Complexity:
        Time  : O(N × Target)
        Space : O(N × Target) + recursion stack
*/

class Solution {
public:
    int mod = 1e9 + 7;

    int solve(int idx, int n, int tar, vector<int> &arr, vector<vector<int>> &dp){

        if(idx == n){
            if(tar == 0) return 1;
            return 0;
        }

        if(dp[idx][tar] != -1) 
            return dp[idx][tar];

        int skip = solve(idx+1, n, tar, arr, dp);

        int take = 0;
        if(arr[idx] <= tar)
            take = solve(idx+1, n, tar-arr[idx], arr, dp);

        return dp[idx][tar] = (take + skip) % mod;
    }

    int findWays(vector<int> &arr, int tar){
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(tar+1, -1));
        return solve(0, n, tar, arr, dp);
    }

    int countPartitions(vector<int>& arr, int diff) {

        int total = accumulate(arr.begin(), arr.end(), 0);

        if(total - diff < 0 || (total - diff) % 2 != 0)
            return 0;

        return findWays(arr, (total - diff)/2);
    }
};