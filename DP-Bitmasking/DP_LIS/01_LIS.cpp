```cpp
/**
 * Longest Increasing Subsequence (LIS)
 *
 * Problem:
 * Given an array of integers, find the length of the longest
 * strictly increasing subsequence.
 *
 * Example:
 * Input:  [10, 9, 2, 5, 3, 7, 101, 18]
 * Output: 4
 * Explanation: One LIS is [2, 3, 7, 101]
 *
 * ------------------------------------------------------------
 * APPROACH 1: Recursion + Memoization (DP)
 *
 * Idea:
 * At every index we have two choices:
 *   1. Take the current element (if it is greater than previous)
 *   2. Skip the current element
 *
 * State Definition:
 *   solve(idx, prev)
 *
 *   idx  -> current index in array
 *   prev -> index of previously selected element
 *
 * Why prev is needed:
 *   Because we must check whether
 *   arr[idx] > arr[prev]
 *
 * DP Table:
 *   dp[idx][prev]
 *
 * Time Complexity:
 *   O(N^2)
 *
 * Space Complexity:
 *   O(N^2)
 *
 * ------------------------------------------------------------
 * APPROACH 2: Binary Search Optimization (Patience Sorting)
 *
 * Idea:
 * Maintain an array called "tail".
 *
 * tail[i] = smallest possible ending value
 *           of an increasing subsequence of length (i+1)
 *
 * Steps:
 *   1. Traverse the array
 *   2. Use binary search to find the position of current element
 *   3. Replace or extend the tail array
 *
 * Important:
 *   tail array does NOT store the actual subsequence.
 *   It only helps compute the length efficiently.
 *
 * Example:
 *   arr = [10,9,2,5,3,7,101,18]
 *
 *   tail progression:
 *   [10]
 *   [9]
 *   [2]
 *   [2,5]
 *   [2,3]
 *   [2,3,7]
 *   [2,3,7,101]
 *   [2,3,7,18]
 *
 * Answer = size of tail = 4
 *
 * Time Complexity:
 *   O(N log N)
 *
 * Space Complexity:
 *   O(N)
 */

#include <bits/stdc++.h>
using namespace std;


/* -------------------- APPROACH 1 : DP -------------------- */

class SolutionDP {
public:

    int solve(int idx,int p,vector<int> &arr, vector<vector<int>> &dp){

        int n = arr.size();

        if(idx == n) return 0;

        int take = 0;
        int skip;

        if(p != -1 && dp[idx][p] != -1)
            return dp[idx][p];

        if(p == -1 || arr[idx] > arr[p]){
            take = 1 + solve(idx+1, idx, arr, dp);
        }

        skip = solve(idx+1, p, arr, dp);

        if(p != -1)
            dp[idx][p] = max(skip, take);

        return max(skip, take);
    }

    int lis(vector<int>& arr) {

        int n = arr.size();

        vector<vector<int>> dp(n, vector<int>(n, -1));

        return solve(0, -1, arr, dp);
    }
};

/* -------------------- APPROACH 2 : O(N^2) -------------------- */

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {

        int n = nums.size();

        vector<int> dp(n, 1);

        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++){

                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i], dp[j] + 1);
                }

            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};

/* -------------------- APPROACH 3 : O(N log N) -------------------- */

class SolutionBinarySearch {
public:

    int lis(vector<int>& arr) {

        vector<int> tail;

        for(int x : arr){

            auto it = lower_bound(tail.begin(), tail.end(), x);

            if(it == tail.end())
                tail.push_back(x);
            else
                *it = x;
        }

        return tail.size();
    }
};
```
