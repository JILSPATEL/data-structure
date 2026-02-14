/**
 * Problem: Aggressive Cows
 * --------------------------------
 * You are given `n` stalls positioned at different locations along a line.
 * You need to place `k` cows in these stalls such that the minimum distance
 * between any two cows is as large as possible.
 *
 * Each stall can contain at most one cow.
 *
 * Task:
 *   Find the maximum possible minimum distance between any two cows.
 *
 * ----------------------------------------------------
 * Approach: Binary Search on Answer
 * ----------------------------------------------------
 *
 * Key Idea:
 * - Instead of trying all possible placements, we binary search on the
 *   minimum distance between cows.
 *
 * Steps:
 * 1. Sort the stall positions.
 *    This helps us place cows in increasing order of positions.
 *
 * 2. Define search space:
 *    - low  = 1  → minimum possible distance
 *    - high = stalls[n-1] - stalls[0] → maximum possible distance
 *
 * 3. Feasibility Check (Greedy):
 *    For a given distance `dist`, check if we can place `k` cows such that
 *    the distance between every pair of cows is at least `dist`.
 *
 *    Strategy:
 *    - Place the first cow in the first stall.
 *    - For each next stall, place a cow only if the distance from the last
 *      placed cow is ≥ dist.
 *
 * 4. Binary Search Logic:
 *    - If it is possible to place all cows with distance `mid`,
 *      then try for a larger distance.
 *    - Otherwise, reduce the distance.
 *
 * 5. The final answer is the maximum distance that is feasible.
 *
 * Time Complexity:
 *   - Sorting: O(n log n)
 *   - Binary search: O(log(max_distance))
 *   - Feasibility check: O(n)
 *   Overall: O(n log n)
 *
 * Space Complexity:
 *   O(1) (ignoring input storage)
 */

class Solution {
public:
    // Check if we can place k cows with at least 'dist' distance apart
    bool solve(vector<int> &stalls, int dist, int k) {
        int cntCows = 1;          // Place first cow in the first stall
        int last = stalls[0];

        for (int i = 1; i < stalls.size(); i++) {
            if ((stalls[i] - last) >= dist) {
                cntCows++;
                last = stalls[i];
            }
        }

        return cntCows >= k;
    }

    int aggressiveCows(vector<int> &stalls, int k) {
        sort(stalls.begin(), stalls.end());

        int n = stalls.size();
        int low = 1;
        int high = stalls[n - 1] - stalls[0];
        int ans = 0;

        while (low <= high) {
            int mid = (low + high) / 2;

            if (solve(stalls, mid, k)) {
                ans = mid;        // Valid distance, try bigger
                low = mid + 1;
            } else {
                high = mid - 1;   // Too large, reduce distance
            }
        }

        return ans;
    }
};
