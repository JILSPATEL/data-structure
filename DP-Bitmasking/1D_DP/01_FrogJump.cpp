/**
 * Problem: Frog Jump (Minimum Cost)
 * ----------------------------------
 * A frog is standing at index 0 and wants to reach index n-1.
 * Each element in the array `height` represents the height of a stone.
 * 
 * The frog can:
 *   1) Jump to the next stone (i -> i+1)
 *   2) Jump to the next-to-next stone (i -> i+2)
 * 
 * Cost of a jump:
 *   abs(height[current] - height[previous])
 * 
 * Goal:
 *   Find the minimum total cost required to reach the last stone.
 * 
 * ---------------------------------------------------------------
 * APPROACH (Dynamic Programming - Space Optimized)
 * ---------------------------------------------------------------
 * 
 * We solve this using DP because:
 * - The minimum cost to reach index i depends on previous positions.
 * 
 * Let:
 *   dp[i] = Minimum cost to reach index i
 * 
 * Recurrence relation:
 * 
 *   To reach index i:
 *     1) Jump from (i-1)
 *        cost = dp[i-1] + abs(height[i] - height[i-1])
 * 
 *     2) Jump from (i-2) (if possible)
 *        cost = dp[i-2] + abs(height[i] - height[i-2])
 * 
 *   dp[i] = min(jumpOne, jumpTwo)
 * 
 * Base Case:
 *   dp[0] = 0  (No cost to stay at starting stone)
 * 
 * ---------------------------------------------------------------
 * SPACE OPTIMIZATION
 * ---------------------------------------------------------------
 * Instead of using a full dp array,
 * we only need the last two values:
 * 
 *   prev1 = dp[i-1]
 *   prev2 = dp[i-2]
 * 
 * This reduces space complexity from O(n) to O(1).
 * 
 * ---------------------------------------------------------------
 * STEP-BY-STEP WORKING
 * ---------------------------------------------------------------
 * 1) Initialize:
 *      prev1 = 0  (dp[0])
 *      prev2 = 0
 * 
 * 2) Loop from i = 1 to n-1:
 * 
 *      jumpOne = prev1 + abs(height[i] - height[i-1])
 * 
 *      if (i > 1)
 *          jumpTwo = prev2 + abs(height[i] - height[i-2])
 *      else
 *          jumpTwo = INT_MAX (not possible)
 * 
 *      currMin = min(jumpOne, jumpTwo)
 * 
 *      Update:
 *          prev2 = prev1
 *          prev1 = currMin
 * 
 * 3) Finally, prev1 stores the minimum cost to reach last stone.
 * 
 * ---------------------------------------------------------------
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * ---------------------------------------------------------------
 */

class Solution {
  public:
    int minCost(vector<int>& height) {
        int n=height.size();
        int prev1=0;
        int prev2=0;
        for(int i=1;i<n;i++){
            int jumpTwo=INT_MAX;
            int jumpOne=prev1+abs(height[i]-height[i-1]);
            if(i>1){
                jumpTwo=prev2+abs(height[i]-height[i-2]);
            }
            int currMin=min(jumpOne,jumpTwo);
            prev2=prev1;
            prev1=currMin;
        }
        return prev1;
    }
};

/*
=================================================
Approach-2
=================================================
*/
class Solution {
  public:
    int minCost(vector<int>& height) {
        int n=height.size();
        vector<int> dp(n);
        dp[0]=0;
        for(int i=1;i<n;i++){
            int jumpTwo=INT_MAX;
            int jumpOne=dp[i-1]+abs(height[i]-height[i-1]);
            if(i>1){
                jumpTwo=dp[i-2]+abs(height[i]-height[i-2]);
            }
            dp[i]=min(jumpOne,jumpTwo);
        }
        return dp[n-1];
    }
};
