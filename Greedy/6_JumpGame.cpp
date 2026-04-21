/**
 * Problem: Jump Game
 * 
 * Description:
 * Given an array nums where each element represents the maximum jump length
 * at that position, determine if you can reach the last index starting from index 0.
 * 
 * Approaches:
 * 
 * 1. Greedy (Optimal):
 *    - Maintain the farthest index you can reach (maxReach).
 *    - Traverse the array:
 *        • If current index > maxReach → you can't reach here → return false.
 *        • Update maxReach = max(maxReach, i + nums[i]).
 *    - If loop completes, return true.
 * 
 * 2. DP (Not Optimal):
 *    - Mark reachable indices using a boolean array.
 *    - Time complexity becomes O(n^2), which is inefficient.
 * 
 * Why Greedy Works:
 *    - You only care about the farthest reachable position at any step.
 *    - If you can always extend your reach, you’ll eventually reach the end.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int maxReach = 0;
        int n = nums.size();

        for(int i = 0; i < n; i++) {
            // If current index is unreachable
            if(i > maxReach) return false;

            // Update the farthest reachable index
            maxReach = max(maxReach, i + nums[i]);

            // Early exit if we can reach last index
            if(maxReach >= n - 1) return true;
        }

        return true;
    }
};
