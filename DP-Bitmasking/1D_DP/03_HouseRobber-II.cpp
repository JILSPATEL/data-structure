/**

* Problem: House Robber II (Circular Houses)
*
* You are given a circular array of houses where:
* * You cannot rob two adjacent houses
* * First and last house are also adjacent (circular constraint)
*
* Goal:
* Maximize the amount of money you can rob.
*
* ---
* APPROACHES:
*
* 1. Brute Force (Recursion)
* * Try all combinations
* * Time Complexity: O(2^n)
* * Not efficient
*
* 2. Memoization (Top-Down DP)  ✅ (Used here)
* * Store results in dp[]
* * Time: O(n)
* * Space: O(n)
*
* 3. Tabulation (Bottom-Up DP)
* * Iterative solution
* * Time: O(n), Space: O(n)
*
* 4. Space Optimized DP ⭐ (Best)
* * Use only 2 variables
* * Time: O(n), Space: O(1)
*
* ---
* KEY IDEA (IMPORTANT):
*
* Since array is circular:
* → You cannot take both first and last element
*
* So divide into 2 cases:
*
* Case 1: Exclude first house → consider [1 ... n-1]
* Case 2: Exclude last house  → consider [0 ... n-2]
*
* Solve both using normal House Robber DP
* Return max of both
*
* ---

*/

class Solution {
public:

/**
 * Function: solve
 * -----------------------------------------
 * Recursively computes max money from index i
 *
 * Choices:
 * - Take current house → move to i+2
 * - Skip current house → move to i+1
 *
 * DP Memoization used to avoid recomputation
 */
    int solve(int i, vector<int>& nums, vector<int>& dp) {
        int n = nums.size();
        if (i >= n)
            return 0;

        if (dp[i] != -1)
            return dp[i];

        int take = nums[i] + solve(i + 2, nums, dp);

        int skip = solve(i + 1, nums, dp);

        return dp[i] = max(take, skip);
    }

    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        vector<int> temp1, temp2;

        for (int i = 1; i < n; i++)
            temp1.push_back(nums[i]);

        for (int i = 0; i < n - 1; i++)
            temp2.push_back(nums[i]);

        vector<int> dp1(temp1.size(), -1);
        vector<int> dp2(temp2.size(), -1);

        int case1 = solve(0, temp1, dp1);
        int case2 = solve(0, temp2, dp2);

        return max(case1, case2);
    }
};

/**

* ---
* DRY RUN EXAMPLE:
*
* nums = [2, 3, 2]
*
* Case 1 (exclude first): [3, 2]
* → max = 3
*
* Case 2 (exclude last): [2, 3]
* → max = 3
*
* Answer = max(3, 3) = 3
*
* ---
* TIME COMPLEXITY:
* O(n) → each state computed once
*
* SPACE COMPLEXITY:
* O(n) → dp array + recursion stack
*
* ---

*/
