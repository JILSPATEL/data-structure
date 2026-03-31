/**
 * Problem: Maximum Points You Can Obtain from Cards
 * 
 * Description:
 * You are given an array `cardPoints` and an integer `k`.
 * You can take exactly `k` cards from either the beginning or the end.
 * Return the maximum score you can obtain.
 *
 * Approaches:
 * 1. Brute Force:
 *    - Try all combinations of taking cards from left and right.
 *    - Time Complexity: O(k^2)
 *
 * 2. Sliding Window (Optimal - Used here):
 *    - Take first k elements as initial sum.
 *    - Gradually remove elements from left and add from right.
 *    - Track maximum sum.
 *    - Time Complexity: O(k)
 *    - Space Complexity: O(1)
 */

class Solution {
public:
    int maxScore(vector<int>& cardPoints, int k) {
        int leftSum = 0;
        int rightSum = 0;
        int maxSum = 0;

        // Step 1: Take first k elements
        for (int i = 0; i <= k - 1; i++) {
            leftSum += cardPoints[i];
        }

        maxSum = leftSum;

        // Step 2: Slide window
        int rightIdx = cardPoints.size() - 1;

        for (int i = k - 1; i >= 0; i--) {
            leftSum -= cardPoints[i];          // remove from left
            rightSum += cardPoints[rightIdx];  // add from right
            rightIdx--;

            maxSum = max(maxSum, leftSum + rightSum);
        }

        return maxSum;
    }
};