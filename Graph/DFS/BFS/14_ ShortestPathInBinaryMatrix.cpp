/**
 * Problem: Shortest Path in Binary Matrix
 *
 * Description:
 * Given an n x n binary matrix grid, return the length of the
 * shortest clear path from top-left (0,0) to bottom-right (n-1,n-1).
 *
 * Conditions:
 * - 0 -> empty cell (can move)
 * - 1 -> blocked cell
 * - Movement allowed in 8 directions:
 *      up, down, left, right
 *      and all 4 diagonals
 * - Return -1 if no path exists.
 *
 * Possible Approaches:
 *
 * 1) BFS (Optimal)
 *    - Treat every cell as a graph node.
 *    - Since every movement cost is equal (=1),
 *      BFS guarantees shortest path.
 *    - Use queue for level-wise traversal.
 *    - Mark visited cells immediately.
 *
 *    Time Complexity: O(n²)
 *    Space Complexity: O(n²)
 *
 * 2) Dijkstra
 *    - Can also solve it using min heap.
 *    - Useful when movement costs differ.
 *
 *    Time Complexity: O(n² log(n²))
 *    Space Complexity: O(n²)
 *
 * Why BFS is preferred?
 * Since all edges have equal weight (=1),
 * BFS naturally gives shortest distance with
 * lower complexity than Dijkstra.
 */

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {

        int n = grid.size();

        // If start or destination is blocked
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;

        /*
            8 possible directions:
            ↖ ↑ ↗
            ←   →
            ↙ ↓ ↘
        */
        vector<pair<int,int>> dir = {
            {-1,-1}, {-1,0}, {-1,1},
            {0,-1},          {0,1},
            {1,-1},  {1,0},  {1,1}
        };

        /*
            Queue stores:
            {distance,{row,col}}

            distance = current path length
        */
        queue<pair<int,pair<int,int>>> q;

        // Start from (0,0)
        q.push({1,{0,0}});

        // Mark visited
        grid[0][0] = 1;

        while (!q.empty()) {

            auto curr = q.front();
            q.pop();

            int dist = curr.first;
            int row = curr.second.first;
            int col = curr.second.second;

            // Destination reached
            if (row == n - 1 && col == n - 1)
                return dist;

            // Explore all 8 directions
            for (auto &move : dir) {

                int x = row + move.first;
                int y = col + move.second;

                /*
                    Conditions:
                    1. Inside matrix
                    2. Cell not blocked
                    3. Cell not visited
                */
                if (x >= 0 && x < n &&
                    y >= 0 && y < n &&
                    grid[x][y] == 0) {

                    // Mark visited immediately
                    grid[x][y] = 1;

                    // Push with increased distance
                    q.push({dist + 1,{x,y}});
                }
            }
        }

        // No valid path exists
        return -1;
    }
};