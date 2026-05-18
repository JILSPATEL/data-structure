/**
 * Problem: Rotting Oranges
 * Platform: LeetCode
 * Approach: Multi-Source Breadth First Search (BFS)
 * 
 * Description:
 * 
 * Grid Values:
 * 0 -> Empty cell
 * 1 -> Fresh orange
 * 2 -> Rotten orange
 * 
 * Rule:
 * Every minute, all fresh oranges adjacent
 * (up, down, left, right) to a rotten orange
 * become rotten.
 * 
 * We need to find:
 * -> Minimum time required to rot all oranges.
 * -> Return -1 if impossible.
 * 
 * ---------------------------------------------------------
 * Approaches:
 * 
 * 1. Multi-Source BFS (Used Here)
 *    - Put all rotten oranges into queue initially.
 *    - Spread rotting level by level.
 *    - Each BFS level = 1 minute.
 * 
 * 2. DFS Simulation
 *    - Possible but inefficient and complex.
 * 
 * ---------------------------------------------------------
 * Example:
 * Input:
 * [[2,1,1],
 *  [1,1,0],
 *  [0,1,1]]
 *
 * Output:
 * 4
 *
 * ---------------------------------------------------------
 * Why Multi-Source BFS?
 *
 * Because all rotten oranges spread infection
 * simultaneously at the same time.
 *
 * BFS naturally handles:
 * -> Level order traversal
 * -> Minimum time propagation
 *
 * ---------------------------------------------------------
 * Time Complexity:
 * O(rows * cols)
 *
 * Each cell is processed once.
 *
 * Space Complexity:
 * O(rows * cols)
 *
 * Queue may contain all cells in worst case.
 */

class Solution {
public:

    int orangesRotting(vector<vector<int>>& grid) {

        // Total rows and columns
        int rows = grid.size();
        int cols = grid[0].size();

        // Count fresh oranges
        int freshOranges = 0;

        /**
         * Queue stores all rotten oranges initially.
         * 
         * This is called Multi-Source BFS because
         * BFS starts from multiple sources together.
         */
        queue<pair<int, int>> q;

        /**
         * Step 1:
         * Traverse grid and:
         * - Add rotten oranges into queue
         * - Count fresh oranges
         */
        for (int i = 0; i < rows; i++) {

            for (int j = 0; j < cols; j++) {

                // Rotten orange found
                if (grid[i][j] == 2) {
                    q.push({i, j});
                }

                // Fresh orange found
                if (grid[i][j] == 1) {
                    freshOranges++;
                }
            }
        }

        // Stores total time required
        int minutePassed = 0;

        /**
         * 4 Possible Directions
         * Right, Down, Up, Left
         */
        vector<pair<int, int>> dir = {
            {0, 1},
            {1, 0},
            {-1, 0},
            {0, -1}
        };

        /**
         * BFS Traversal
         * 
         * Continue until:
         * - Queue becomes empty
         * - OR all fresh oranges become rotten
         */
        while (!q.empty() && freshOranges) {

            // One BFS level = One minute
            minutePassed++;

            // Current level size
            int size = q.size();

            /**
             * Process all rotten oranges
             * present in current minute
             */
            for (int i = 0; i < size; i++) {

                // Current rotten orange
                auto [a, b] = q.front();
                q.pop();

                /**
                 * Try all 4 directions
                 */
                for (auto& vec : dir) {

                    int x = a + vec.first;
                    int y = b + vec.second;

                    /**
                     * Valid fresh orange check
                     */
                    if (x >= 0 && x < rows &&
                        y >= 0 && y < cols &&
                        grid[x][y] == 1) {

                        // Rot the orange
                        grid[x][y] = 2;

                        // Add newly rotten orange to queue
                        q.push({x, y});

                        // Reduce fresh orange count
                        freshOranges--;
                    }
                }
            }
        }

        /**
         * If all oranges became rotten
         * return total minutes
         * 
         * Else return -1
         */
        return (freshOranges == 0)
               ? minutePassed
               : -1;
    }
};