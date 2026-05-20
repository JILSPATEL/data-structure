/**
 * Problem: Number of Islands
 *
 * Approach:
 * ----------
 * We traverse every cell in the grid.
 *
 * If we find:
 *      grid[i][j] == '1'
 * AND
 *      not visited
 *
 * then:
 *      -> We discovered a new island
 *      -> Start BFS traversal
 *      -> Mark all connected land cells visited
 *
 * Finally return total island count.
 *
 * ---------------------------------------------------
 * Time Complexity:
 *      O(N * M)
 *
 * Every cell is visited at most once.
 *
 * ---------------------------------------------------
 * Space Complexity:
 *      O(N * M)
 *
 * For:
 *      1. Visited matrix
 *      2. BFS queue in worst case
 */

class Solution {
public:

    int numIslands(vector<vector<char>>& grid) {

        // Number of rows
        int n = grid.size();

        // Number of columns
        int m = grid[0].size();

        // Stores total islands
        int cnt = 0;

        // Visited matrix
        vector<vector<int>> vis(n, vector<int>(m, 0));

        /**
         * 4-direction movement
         *
         * Right  -> (0, 1)
         * Down   -> (1, 0)
         * Up     -> (-1, 0)
         * Left   -> (0, -1)
         */
        vector<pair<int, int>> dir = {
            {0, 1},
            {1, 0},
            {-1, 0},
            {0, -1}
        };

        // Traverse complete grid
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < m; j++) {

                /**
                 * If current cell is land
                 * and not visited
                 */
                if (grid[i][j] == '1' && !vis[i][j]) {

                    // New island found
                    cnt++;

                    // BFS Queue
                    queue<pair<int, int>> q;

                    // Push current cell
                    q.push({i, j});

                    // Mark visited
                    vis[i][j] = 1;

                    /**
                     * Standard BFS
                     */
                    while (!q.empty()) {

                        // Get front node
                        auto [a, b] = q.front();
                        q.pop();

                        /**
                         * Explore all 4 directions
                         */
                        for (auto& vec : dir) {

                            int x = a + vec.first;
                            int y = b + vec.second;

                            /**
                             * Conditions:
                             * 1. Inside grid
                             * 2. Land cell
                             * 3. Not visited
                             */
                            if (x >= 0 && y >= 0 &&
                                x < n && y < m &&
                                grid[x][y] == '1' &&
                                !vis[x][y]) {

                                // Mark visited
                                vis[x][y] = 1;

                                // Push into queue
                                q.push({x, y});
                            }
                        }
                    }
                }
            }
        }

        return cnt;
    }
};