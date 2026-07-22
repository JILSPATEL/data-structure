
/*
Problem:
Print one Longest Increasing Subsequence (LIS) of an array.

Approach:
Use dynamic programming to compute the LIS length ending at each index and store the previous index that gives the best transition.
After filling the DP table, backtrack from the index with the maximum LIS length to reconstruct one valid LIS.

Intuition:
Every element can extend a smaller previous element. By storing the best predecessor for each position, we can recover a valid subsequence without recomputing it.

Example:
nums = [3, 1, 4, 2, 5]
One LIS is [1, 2, 5].
*/
class Solution {
public:
    vector<int> getLIS(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n, 1), hash(n);
        
        int maxi = 1;
        int lastIdx = 0;

        for (int i = 0; i < n; i++) {
            hash[i] = i;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    hash[i] = j; 
                }
            }
            if (dp[i] > maxi) {
                maxi = dp[i];
                lastIdx = i;
            }
        }
        vector<int> lis;
        lis.push_back(nums[lastIdx]);
        while (hash[lastIdx] != lastIdx) {
            lastIdx = hash[lastIdx];
            lis.push_back(nums[lastIdx]);
        }

        reverse(lis.begin(), lis.end());
        return lis;
    }
};