/**
 * Problem: Non-overlapping Intervals (Leetcode 435)
 * 
 * Approach:
 * 1. Greedy Strategy:
 *    - Sort intervals based on ending time.
 *    - Always pick the interval with the smallest end time.
 *    - This ensures maximum space for upcoming intervals.
 * 
 * 2. Logic:
 *    - Take first interval as selected.
 *    - Traverse remaining intervals:
 *        -> If current start >= previous end → take it
 *        -> Otherwise skip (overlapping)
 * 
 * 3. Result:
 *    - cnt = maximum number of non-overlapping intervals
 *    - Answer = total intervals - cnt
 * 
 * Time Complexity: O(n log n)  (sorting)
 * Space Complexity: O(1)
 */

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n == 0) return 0;

        // Sort by end time
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        int prevLast = intervals[0][1];
        int cnt = 1;

        for (int i = 1; i < n; i++) {
            // Non-overlapping condition
            if (intervals[i][0] >= prevLast) {
                cnt++;
                prevLast = intervals[i][1];
            }
        }

        return n - cnt; // minimum removals
    }
};