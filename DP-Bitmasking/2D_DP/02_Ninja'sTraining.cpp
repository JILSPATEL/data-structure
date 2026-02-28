/**
 * Problem:
 * A ninja trains for N days. Every day, he can choose one of 3 activities.
 * Each activity gives some points. The ninja cannot perform the same activity
 * on two consecutive days.
 * The task is to find the maximum total points the ninja can earn.
 *
 * Intuition:
 * For each day, we try all activities except the one done on the previous day.
 * For every valid choice today, we add today's points to the best possible
 * result from previous days.
 *
 * Approach:
 * We use Dynamic Programming with recursion + memoization.
 *
 * State:
 * solve(day, last) → maximum points till 'day' if the previous day's activity was 'last'
 *
 * Transition:
 * Try all activities (0,1,2) except 'last' and take the maximum.
 *
 * Base Case:
 * On day 0, choose the best activity different from 'last'.
 *
 * Time Complexity:
 * O(N * 4 * 3)
 *
 * Space Complexity:
 * O(N * 4)
 */

class Solution {
  public:
    int solve(int day, int last, vector<vector<int>> &mat, vector<vector<int>> &dp) {
        if (dp[day][last] != -1) return dp[day][last];

        if (day == 0) {
            int maxi = 0;
            for (int i = 0; i < 3; i++) {
                if (i != last) {
                    maxi = max(maxi, mat[0][i]);
                }
            }
            return dp[day][last] = maxi;
        }

        int maxi = 0;
        for (int i = 0; i < 3; i++) {
            if (i != last) {
                int val = mat[day][i] + solve(day - 1, i, mat, dp);
                maxi = max(maxi, val);
            }
        }

        return dp[day][last] = maxi;
    }

    int maximumPoints(vector<vector<int>>& mat) {
        int n = mat.size();
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solve(n - 1, 3, mat, dp);
    }
};