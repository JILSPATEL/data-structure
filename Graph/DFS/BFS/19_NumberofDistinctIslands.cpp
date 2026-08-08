/*
Problem: Count the number of distinct island shapes in a grid.

Intuition:
Two islands should be treated as the same only if they have the same shape,
not just the same size. So while traversing each island, record every cell as
its position relative to the island's starting cell. That relative pattern is
stable even when the island appears in a different place on the grid.

Approach:
1. Scan the grid cell by cell.
2. When an unvisited land cell is found, run DFS to explore the whole island.
3. Store each visited cell as (row - row0, col - col0), where (row0, col0) is
  the first cell of that island.
4. Insert the collected relative shape into a set.
5. The answer is the number of unique shapes in the set.

Example:
Grid:
L W W
L W L
W W L

The first island has relative cells [(0,0), (1,0)].
The second island also has relative cells [(0,0), (1,0)].
Since both shapes match, they count as one distinct island shape.
*/

class Solution {
public:
  int n, m;

  void dfs(int row, int col, vector<vector<char>> &grid,
           vector<vector<int>> &vis, vector<pair<int, int>> &shape, int row0,
           int col0) {

    vis[row][col] = 1;
    shape.push_back({row - row0, col - col0});

    vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    for (auto &d : dir) {
      int x = row + d.first;
      int y = col + d.second;

      if (x >= 0 && x < n && y >= 0 && y < m && !vis[x][y] &&
          grid[x][y] == 'L') {
        dfs(x, y, grid, vis, shape, row0, col0);
      }
    }
  }

  int countDistinctIslands(vector<vector<char>> &grid) {
    n = grid.size();
    m = grid[0].size();

    set<vector<pair<int, int>>> st;
    vector<vector<int>> vis(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (!vis[i][j] && grid[i][j] == 'L') {
          vector<pair<int, int>> shape;
          dfs(i, j, grid, vis, shape, i, j);
          st.insert(shape);
        }
      }
    }

    return st.size();
  }
};
