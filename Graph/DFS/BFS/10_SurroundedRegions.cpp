#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: Surrounded Regions
 * LeetCode: 130
 *
 * ---------------------------------------------------
 * Intuition
 * ---------------------------------------------------
 *
 * Any 'O' completely surrounded by 'X' should be converted
 * into 'X'.
 *
 * Important Observation:
 *
 * If an 'O' is connected to the boundary,
 * then it can NEVER be surrounded.
 *
 * So instead of finding surrounded regions,
 * we find SAFE regions.
 *
 * SAFE REGION:
 * Any 'O' connected to boundary 'O'.
 *
 * ---------------------------------------------------
 * Final Strategy
 * ---------------------------------------------------
 *
 * 1. Traverse all boundary cells.
 *
 * 2. If boundary cell contains 'O':
 *      -> start BFS/DFS
 *      -> mark all connected 'O' as visited
 *
 * 3. After traversal:
 *      -> visited 'O' are SAFE
 *      -> unvisited 'O' are surrounded
 *
 * 4. Convert:
 *      -> unvisited 'O' -> 'X'
 *      -> visited cells remain 'O'
 *
 * ---------------------------------------------------
 * Example
 * ---------------------------------------------------
 *
 * Input:
 *
 * X X X X
 * X O O X
 * X O O X
 * X O X X
 *
 * Boundary 'O':
 * Only (3,1)
 *
 * BFS/DFS traversal:
 *
 * X X X X
 * X . . X
 * X . . X
 * X O X X
 *
 * Reachable safe cells:
 *
 * X X X X
 * X O O X
 * X O O X
 * X O X X
 *
 * All visited remain 'O'
 *
 * Final Output:
 *
 * X X X X
 * X O O X
 * X O O X
 * X O X X
 *
 * ---------------------------------------------------
 * WHY MULTI-SOURCE BFS?
 * ---------------------------------------------------
 *
 * We start BFS from ALL boundary 'O' simultaneously.
 *
 * So all boundary 'O' act as source nodes.
 *
 * ---------------------------------------------------
 * Time Complexity
 * ---------------------------------------------------
 *
 * O(n * m)
 *
 * Every cell visited once.
 *
 * ---------------------------------------------------
 * Space Complexity
 * ---------------------------------------------------
 *
 * O(n * m)
 *
 * visited matrix + queue/recursion stack
 */

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        queue<pair<int, int>> q;
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // Step 1: Push all boundary 'O' cells into queue
        for (int j = 0; j < m; j++) {
            if (board[0][j] == 'O') {
                q.push({0, j});
                vis[0][j] = 1;
            }
            if (board[n - 1][j] == 'O') {
                q.push({n - 1, j});
                vis[n - 1][j] = 1;
            }
        }

        for (int i = 1; i < n - 1; i++) {
            if (board[i][0] == 'O') {
                q.push({i, 0});
                vis[i][0] = 1;
            }
            if (board[i][m - 1] == 'O') {
                q.push({i, m - 1});
                vis[i][m - 1] = 1;
            }
        }

        vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        // Step 2: BFS traversal from all boundary 'O'
        while (!q.empty()) {
            auto [row, col] = q.front();
            q.pop();

            for (auto &d : dir) {
                int newRow = row + d.first;
                int newCol = col + d.second;

                if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m &&
                    board[newRow][newCol] == 'O' && !vis[newRow][newCol]) {
                    vis[newRow][newCol] = 1;
                    q.push({newRow, newCol});
                }
            }
        }

        // Step 3: Convert surrounded regions
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

/**
 * DFS Approach
 *
 * Same intuition as BFS.
 *
 * Difference:
 * Instead of queue, recursion stack is used.
 */

class Solution {
public:
    vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    void dfs(int row,
             int col,
             vector<vector<char>>& board,
             vector<vector<int>>& vis) {
        int n = board.size();
        int m = board[0].size();

        vis[row][col] = 1;
        for (auto &d : dir) {
            int newRow = row + d.first;
            int newCol = col + d.second;

            if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < m &&
                board[newRow][newCol] == 'O' && !vis[newRow][newCol]) {
                dfs(newRow, newCol, board, vis);
            }
        }
    }

    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));

        for (int j = 0; j < m; j++) {
            if (board[0][j] == 'O' && !vis[0][j]) {
                dfs(0, j, board, vis);
            }
            if (board[n - 1][j] == 'O' && !vis[n - 1][j]) {
                dfs(n - 1, j, board, vis);
            }
        }

        for (int i = 1; i < n - 1; i++) {
            if (board[i][0] == 'O' && !vis[i][0]) {
                dfs(i, 0, board, vis);
            }
            if (board[i][m - 1] == 'O' && !vis[i][m - 1]) {
                dfs(i, m - 1, board, vis);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
};