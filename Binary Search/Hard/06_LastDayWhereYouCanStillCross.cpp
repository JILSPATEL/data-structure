class Solution {
public:
    vector<pair<int, int>> dir = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    bool canCross(int day, int row, int col, vector<vector<int>>& cells) {
        vector<vector<int>> grid(row, vector<int>(col, 0));

        for (int i = 0; i < day; i++) {
            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;
            grid[r][c] = 1;
        }

        queue<pair<int, int>> q;
        vector<vector<int>> vis(row, vector<int>(col, 0));

        for (int j = 0; j < col; j++) {
            if (grid[0][j] == 0) {
                q.push({0, j});
                vis[0][j] = 1;
            }
        }

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == row - 1)
                return true;
            for (auto [dx, dy] : dir) {

                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < row && ny >= 0 && ny < col &&
                    !vis[nx][ny] && grid[nx][ny] == 0) {

                    vis[nx][ny] = 1;
                    q.push({nx, ny});
                }
            }
        }
        return false;
    }
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {

        int low = 0;
        int high = cells.size();
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canCross(mid, row, col, cells)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};