/**
 * Problem: Number of Enclaves
 *
 * Definition:
 * A land cell (1) is called an enclave if we cannot walk off the boundary
 * of the grid starting from that cell using only adjacent land cells.
 *
 * Idea:
 * Instead of finding enclave cells directly,
 * we find all land cells connected to the boundary.
 *
 * Any land cell connected to boundary:
 * -> Can escape the grid
 * -> Therefore NOT an enclave
 *
 * Remaining unvisited land cells are enclave cells.
 *
 * -------------------------------------------------------------------
 * APPROACH : Multi-Source BFS
 * -------------------------------------------------------------------
 *
 * STEP 1:
 * Push all boundary land cells into queue.
 *
 * Why?
 * Because these cells can already escape outside the grid.
 *
 * STEP 2:
 * Run BFS from all boundary land cells simultaneously.
 *
 * During BFS:
 * -> Mark every reachable land cell as visited.
 * -> These cells are also NOT enclaves because they can reach boundary.
 *
 * STEP 3:
 * Traverse entire grid.
 *
 * Count cells where:
 * -> grid[i][j] == 1
 * -> vis[i][j] == 0
 *
 * These are enclave cells.
 *
 * -------------------------------------------------------------------
 * WHY MULTI-SOURCE BFS?
 * -------------------------------------------------------------------
 *
 * Normally BFS starts from one source.
 *
 * Here we have multiple starting points:
 * -> all boundary land cells
 *
 * So we insert all of them initially into queue.
 *
 * -------------------------------------------------------------------
 * Example
 * -------------------------------------------------------------------
 *
 * Example 1:
 * Input:
 * 0 0 0 0
 * 1 0 1 0
 * 0 1 1 0
 * 0 0 0 0
 * Output: 3
 *
 * Example 2:
 * Input:
 * 0 0 0 1 1 1
 * 0 1 1 1 1 0
 * 0 1 0 1 0 0
 * Output: 1
 *
 * Example 3:
 * Input:
 * 0 0 0 0
 * 0 1 1 0
 * 0 1 1 0
 * 0 0 0 0
 * Output: 4
 * Explanation: All 4 cells in the middle are enclaves
 *
 * -------------------------------------------------------------------
 * TIME COMPLEXITY
 * -------------------------------------------------------------------
 *
 * Traversing boundary  -> O(N + M)
 * BFS traversal        -> O(N * M)
 * Counting answer      -> O(N * M)
 *
 * Total Complexity:
 * -> O(N * M)
 *
 * -------------------------------------------------------------------
 * SPACE COMPLEXITY
 * -------------------------------------------------------------------
 *
 * Visited matrix -> O(N * M)
 * Queue          -> O(N * M)
 *
 * Total:
 * -> O(N * M)
 */

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0));

        queue<pair<int, int>> q;

        for (int i = 0; i < m; i++) {

            if (grid[0][i] == 1) {
                q.push({0, i});
                vis[0][i] = 1;
            }

            if (grid[n - 1][i] == 1) {
                q.push({n - 1, i});
                vis[n - 1][i] = 1;
            }
        }

        for (int i = 0; i < n; i++) {

            if (grid[i][0] == 1) {
                q.push({i, 0});
                vis[i][0] = 1;
            }

            if (grid[i][m - 1] == 1) {
                q.push({i, m - 1});
                vis[i][m - 1] = 1;
            }
        }

        vector<pair<int, int>> dir = {
            {0, 1},
            {1, 0},
            {-1, 0},
            {0, -1}
        };

        while (!q.empty()) {

            auto [x, y] = q.front();
            q.pop();

            for (auto &d : dir) {

                int nx = x + d.first;
                int ny = y + d.second;

                if (nx >= 0 &&
                    ny >= 0 &&
                    nx < n &&
                    ny < m &&
                    grid[nx][ny] == 1 &&
                    !vis[nx][ny]) {

                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }

        int cnt = 0;

        for (int i = 0; i < n; i++) {

            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1 && !vis[i][j]) {
                    cnt++;
                }
            }
        }

        return cnt;
    }
};