/**
 * Problem: Next Permutation
 * -----------------------------------
 * Given an array of integers, rearrange them into the next lexicographically greater permutation.
 * If such arrangement is not possible, rearrange it to the lowest possible order (ascending).
 *
 * Example:
 * Input:  [1,2,3]
 * Output: [1,3,2]
 *
 * Approaches:
 * -----------------------------------
 * 1. Brute Force:
 *    - Generate all permutations
 *    - Sort them and find the next one
 *    - Time Complexity: O(n! * n) → Not feasible
 *
 * 2. Optimal Approach (Used here):
 *    - Step 1: Find the breakpoint (first index from right where nums[i] < nums[i+1])
 *    - Step 2: If no breakpoint → reverse entire array
 *    - Step 3: Find next greater element from right and swap
 *    - Step 4: Reverse the suffix (i+1 to end)
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int idx = -1;

        // Step 1: Find breakpoint
        for(int i = n - 2; i >= 0; i--){
            if(nums[i] < nums[i + 1]){
                idx = i;
                break;
            }
        }

        // Step 2: If no breakpoint, reverse whole array
        if(idx == -1){
            reverse(nums.begin(), nums.end());
            return;
        }

        // Step 3: Find next greater element and swap
        for(int j = n - 1; j >= 0; j--){
            if(nums[j] > nums[idx]){
                swap(nums[j], nums[idx]);
                break;
            }
        }

        // Step 4: Reverse the suffix
        reverse(nums.begin() + idx + 1, nums.end());
    }
};
