/**
 * Problem: Merge Intervals (Leetcode 56)
 * 
 * Approach:
 * 1. Sort Intervals:
 *    - Sort based on starting time.
 * 
 * 2. Traverse & Merge:
 *    - Maintain a result vector.
 *    - Compare current interval with last merged interval:
 *        -> If overlapping → merge them
 *        -> Else → add new interval
 * 
 * 3. Overlap Condition:
 *    - prev_end >= current_start
 * 
 * Time Complexity: O(n log n)  (sorting)
 * Space Complexity: O(n)
 */

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        if (n == 0) return {};

        // Step 1: Sort intervals by start time
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> res;
        res.push_back(intervals[0]);

        // Step 2: Traverse and merge
        for (int i = 1; i < n; i++) {
            vector<int>& prev = res.back();

            // If overlapping
            if (prev[1] >= intervals[i][0]) {
                prev[1] = max(prev[1], intervals[i][1]);
            } 
            else {
                res.push_back(intervals[i]);
            }
        }

        return res;
    }
};