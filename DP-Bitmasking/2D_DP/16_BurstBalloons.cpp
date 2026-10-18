/*
Problem:
Given an array of balloons, bursting balloon i earns
nums[left] * nums[i] * nums[right] coins, where left and right are the
nearest balloons that are still present. Find the maximum coins obtainable.
After all balloons are burst, the two outside balloons have value 1.

Intuition:
The neighbors of a balloon change when other balloons are burst, so choosing
the first balloon is difficult to model. Instead, choose the last balloon to
burst in a subarray. At that moment, every other balloon inside the subarray
has already disappeared, so its neighbors are fixed: the values just outside
the subarray. This splits the problem into two independent smaller ranges.

Approach:
1. Add a virtual balloon with value 1 at both ends.
2. Let solve(i, j) be the maximum coins from bursting balloons i through j.
3. Try every idx in [i, j] as the last balloon burst:
      nums[i - 1] * nums[idx] * nums[j + 1]
      + solve(i, idx - 1)
      + solve(idx + 1, j)
4. Take the maximum over all choices. The first implementation uses
   memoization; the second computes the same states using tabulation.

Example:
For nums = [3, 1, 5, 8], add boundary balloons to get [1, 3, 1, 5, 8, 1].
One possible order is:
  burst 1  -> 3 * 1 * 5 = 15
  burst 3  -> 1 * 3 * 5 = 15
  burst 5  -> 1 * 5 * 8 = 40
  burst 8  -> 1 * 8 * 1 = 8
The total is 78, but the optimal order is 1, 5, 3, 8, which gives 167.
The interval DP finds this maximum without enumerating every burst order.

Complexity:
Time: O(n^3), Space: O(n^2)
*/

//Memoization

class Solution {
public:
    vector<vector<int>> dp;

    int solve(int i, int j, vector<int>& nums) {
        if (i > j) return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        int maxi = 0;

        for (int idx = i; idx <= j; idx++) {
            int cost = nums[i - 1] * nums[idx] * nums[j + 1]
                     + solve(i, idx - 1, nums)
                     + solve(idx + 1, j, nums);

            maxi = max(maxi, cost);
        }

        return dp[i][j] = maxi;
    }

    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        int n = nums.size();

        dp.assign(n, vector<int>(n, -1));

        return solve(1, n - 2, nums);
    }
};

//tabulation
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for (int i = n; i >= 1; i--) {
            for (int j = i; j <= n; j++) {  
                for (int idx = i; idx <= j; idx++) {
                    int cost = nums[i - 1] * nums[idx] * nums[j + 1]
                             + dp[i][idx - 1]
                             + dp[idx + 1][j];

                    dp[i][j] = max(dp[i][j], cost);
                }
            }
        }

        return dp[1][n];
    }
};