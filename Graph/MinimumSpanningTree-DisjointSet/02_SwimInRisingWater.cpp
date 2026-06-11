/**
 * Problem: Swim in Rising Water (LeetCode 778)
 *
 * Given an n x n grid where grid[i][j] represents the elevation of a cell,
 * rain starts falling and the water level rises over time.
 *
 * At time t, you can enter a cell only if grid[i][j] <= t.
 * Find the minimum time required to travel from (0,0) to (n-1,n-1).
 *
 * Example 1:
 * Input: grid = [[0,2],[1,3]]
 * Output: 3
 * Explanation: At time 3, water level reaches all cells
 *
 * Example 2:
 * Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
 * Output: 16
 * Explanation: Optimal path encounters maximum elevation of 16
 *
 * Example 3:
 * Input: grid = [[0,1],[2,3]]
 * Output: 3
 * Explanation: Must wait until water level reaches 3
 *
 * ---------------------------------------------------------
 * Possible Approaches:
 *
 * 1. Dijkstra's Algorithm (Optimal)
 *    - Treat each cell as a graph node.
 *    - Moving to a neighbor costs:
 *          max(current_path_elevation, neighbor_elevation)
 *    - Use a Min Heap to always process the cell with the
 *      minimum maximum elevation encountered so far.
 *    - Time Complexity: O(N^2 log(N^2))
 *    - Space Complexity: O(N^2)
 *
 * 2. Binary Search + BFS/DFS
 *    - Binary search on answer (time).
 *    - For a given time t, check if destination is reachable.
 *    - Time Complexity: O(N^2 log(maxElevation))
 *    - Space Complexity: O(N^2)
 *
 * ---------------------------------------------------------
 * Intuition:
 *
 * We want to minimize the maximum elevation encountered along
 * the path. Instead of minimizing distance, Dijkstra minimizes
 * the maximum cell value seen so far.
 *
 * The first time we reach the destination through the min heap,
 * we are guaranteed to have the minimum possible answer.
 */

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {

        int n = grid.size();

        // Directions: Right, Down, Up, Left
        vector<pair<int, int>> directions = {
            {0, 1},
            {1, 0},
            {-1, 0},
            {0, -1}
        };

        // Visited matrix
        vector<vector<int>> visited(n, vector<int>(n, 0));

        /**
         * Min Heap Format:
         * {currentMaximumElevation, row, col}
         */
        priority_queue<
            vector<int>,
            vector<vector<int>>,
            greater<vector<int>>
        > minHeap;

        // Start from top-left cell
        minHeap.push({grid[0][0], 0, 0});
        visited[0][0] = 1;

        while (!minHeap.empty()) {

            auto current = minHeap.top();
            minHeap.pop();

            int currentElevation = current[0];
            int row = current[1];
            int col = current[2];

            // Destination reached
            if (row == n - 1 && col == n - 1) {
                return currentElevation;
            }

            // Explore all 4 directions
            for (auto& dir : directions) {

                int newRow = row + dir.first;
                int newCol = col + dir.second;

                // Boundary and visited check
                if (newRow >= 0 &&
                    newCol >= 0 &&
                    newRow < n &&
                    newCol < n &&
                    !visited[newRow][newCol]) {

                    visited[newRow][newCol] = 1;

                    /**
                     * New path cost:
                     * Maximum elevation encountered so far.
                     */
                    int newElevation =
                        max(currentElevation,
                            grid[newRow][newCol]);

                    minHeap.push({
                        newElevation,
                        newRow,
                        newCol
                    });
                }
            }
        }

        return -1;
    }
};