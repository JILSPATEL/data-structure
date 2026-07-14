/*
Problem: Find the Number of Subsequences With Equal GCD

Description:
Given an array of positive integers `nums`, count the number of ordered pairs
of disjoint, non-empty subsequences (first, second) such that the greatest
common divisor (GCD) of the elements in `first` is equal to the GCD of the
elements in `second`. Each element in `nums` may be assigned to at most one
of the two subsequences or skipped.

Intuition:
At each index we have three choices for the current element: skip it, add it
to the first subsequence (updating the first subsequence's GCD), or add it to
the second subsequence (updating the second subsequence's GCD). We need to
track the index and the current GCD values of both subsequences. Because GCD
values are bounded by the maximum element in `nums`, we can use a 3D DP
state (idx, gcd1, gcd2) to count valid assignments.

Approach:
- Define DP state as `dp[idx][g1][g2]` = number of ways using elements from
    `idx`..end when current GCDs are `g1` and `g2` (0 represents "no elements
    chosen yet" for that subsequence).
- Base case: when `idx == n`, return 1 if both `g1` and `g2` are non-zero and
    equal, otherwise 0.
- Transition: for each element `x = nums[idx]`:
        - skip: keep `(g1, g2)`
        - add to first: `(gcd(g1, x), g2)`
        - add to second: `(g1, gcd(g2, x))`
- Use memoization (top-down) or bottom-up iteration over `idx` and all GCD
    values up to `max(nums)`.
- Take results modulo `1e9+7`.

Example:
Input: nums = [2, 2]
All 3^2 = 9 assignments of elements to {skip, first, second} lead to the
following valid ordered pairs where both subsequences are non-empty and have
equal GCD:
    - Assign element0->first, element1->second => gcd(first)=2, gcd(second)=2
    - Assign element0->second, element1->first => gcd(first)=2, gcd(second)=2
Answer = 2

Complexity:
- Time: O(n * M^2) where M = max(nums) (we iterate index and all gcd1,gcd2)
- Space: O(n * M^2) for DP (or O(M^2) per layer in bottom-up)

*/

#include <bits/stdc++.h>
using namespace std;

// Approach 1: Top-down recursion with memoization.
// - State: dp[idx][g1][g2] stores number of ways from index `idx` with
//   current GCDs `g1` and `g2`.
// - Use -1 for uncomputed states and compute via recursion (skip/take1/take2).
class Solution {
public:
    const int MOD = 1000000007;
    
    int solve(vector<int>& nums, int idx, int first, int second, vector<vector<vector<int>>>& dp) {
        if (idx == nums.size()) {
            if (first && second && first == second)
                return 1;
            else
                return 0;
        }
        
        if (dp[idx][first][second] != -1)
            return dp[idx][first][second];
            
        int skip = solve(nums, idx + 1, first, second, dp);
        int take1 = solve(nums, idx + 1, std::gcd(first, nums[idx]), second, dp);
        int take2 = solve(nums, idx + 1, first, std::gcd(second, nums[idx]), dp);
        
        dp[idx][first][second] = (0LL + skip + take1 + take2) % MOD;
        return dp[idx][first][second];
    }
    
    int subsequencePairCount(vector<int>& nums) {
        int maxVal=*max_element(nums.begin(),nums.end());
        vector<vector<vector<int>>> dp(nums.size()+1, vector<vector<int>>(maxVal+1, vector<int>(maxVal+1, -1)));
        return solve(nums, 0, 0, 0, dp);
    }
};



// Approach 2: Bottom-up iterative DP (tabulation).
// - Build dp from the end to the start. dp[n][g1][g2] is base case.
// - Iterate indices backwards and fill dp[i][g1][g2] using transitions.
class Solution {
public:
    const int MOD = 1000000007;
    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        int maxVal = *max_element(nums.begin(), nums.end());

        vector<vector<vector<int>>> dp(
            n + 1, vector<vector<int>>(maxVal + 1, vector<int>(maxVal + 1, 0)));
        for (int first = 0; first <= maxVal; first++) {
            for (int second = 0; second <= maxVal; second++) {
                dp[n][first][second] =
                    (first && second && first == second) ? 1 : 0;
            }
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int first = 0; first <= maxVal; first++) {
                for (int second = 0; second <= maxVal; second++) {
                    int skip = dp[i + 1][first][second];
                    int take1 = dp[i + 1][__gcd(first, nums[i])][second];
                    int take2 = dp[i + 1][first][__gcd(second, nums[i])];
                    dp[i][first][second] = (0LL + skip + take1 + take2) % MOD;
                }
            }
        }
        return dp[0][0][0];
    }
};

int main(){
    Solution sol;
    int n;
    cout<<"Enter the number of elements in the array: ";
    cin>>n;
    vector<int> nums(n);
    cout<<"Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin>>nums[i];
    }
    cout<<"Result: "<<sol.subsequencePairCount(nums)<<endl;
}