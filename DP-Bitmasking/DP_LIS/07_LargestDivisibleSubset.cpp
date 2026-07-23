// Problem: Largest Divisible Subset
// Description:
//   Given a set of distinct positive integers, return the largest subset such that every pair
//   (Si, Sj) of elements in this subset satisfies either Si % Sj == 0 or Sj % Si == 0.
// Intuition:
//   Sorting the numbers allows the problem to be treated like a longest increasing subsequence
//   variant in which a number can extend a subset only if it is divisible by the previous number.
// Approach:
//   - Sort the array.
//   - Use dynamic programming to compute the longest divisible subset ending at each index.
//   - Track predecessor indices to rebuild the actual subset.
//   - Both memoization (top-down) and tabulation (bottom-up) versions are provided.
// Example:
//   Input: nums = {1, 2, 3, 8, 4, 12}
//   Sorted: {1, 2, 3, 4, 8, 12}
//   One valid largest divisible subset is {1, 2, 4, 8}.

//Memoization
class Solution {
public:
    vector<vector<vector<int>>> dp;

    vector<int> solve(int idx, int prevIdx, vector<int> &nums) {

        if (idx == nums.size())
            return {};

        if (prevIdx != -1 && !dp[idx][prevIdx].empty())
            return dp[idx][prevIdx];

        // Skip current element
        vector<int> skip = solve(idx + 1, prevIdx, nums);

        // Take current element
        vector<int> take;
        if (prevIdx == -1 || nums[idx] % nums[prevIdx] == 0) {
            take = solve(idx + 1, idx, nums);
            take.insert(take.begin(), nums[idx]);
        }

        vector<int> ans;

        if (take.size() > skip.size())
            ans = take;
        else
            ans = skip;

        if (prevIdx != -1)
            dp[idx][prevIdx] = ans;

        return ans;
    }

    vector<int> largestDivisibleSubset(vector<int>& nums) {

        sort(nums.begin(), nums.end());

        int n = nums.size();

        dp.assign(n, vector<vector<int>>(n));

        return solve(0, -1, nums);
    }
};

//Tabulation
class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(),nums.end());
        vector<int> dp(n, 1);
        vector<int> lastIdx(n, -1);
        int maxi = 1;
        int finalIndex = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    lastIdx[i] = j;
                }
            }
            if (dp[i] > maxi) {
                maxi = dp[i];
                finalIndex = i;
            }
        }

        vector<int> ans;

        while (finalIndex != -1) {
            ans.push_back(nums[finalIndex]);
            finalIndex = lastIdx[finalIndex];
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};