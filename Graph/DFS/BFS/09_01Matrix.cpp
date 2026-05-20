#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: 01 Matrix
 * Approach: Multi-Source BFS
 *
 * Idea:
 * Push all cells containing 0 into the queue initially.
 * Then perform BFS simultaneously from all 0s.
 *
 * The first time a cell is reached gives the shortest
 * distance from that cell to the nearest 0.
 *
 * Example:
 * mat =
 * [
 *   [0,0,0],
 *   [0,1,0],
 *   [1,1,1]
 * ]
 *
 * Output:
 *   [
 *     [0, 0, 0],
 *     [0, 1, 0],
 *     [1, 2, 1]
 *   ]
 *
 * Time Complexity : O(n * m)
 * Space Complexity: O(n * m)
 */

class Solution {
public:

    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {

        int n = mat.size();
        int m = mat[0].size();

        queue<pair<int, int>> q;

        // Distance matrix
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

        // Step 1:
        // Push all 0 cells into queue
        for (int i = 0; i < n; i++) {

            for (int j = 0; j < m; j++) {

                if (mat[i][j] == 0) {

                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        vector<pair<int, int>> dir = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

        while (!q.empty()) {

            auto [row, col] = q.front();
            q.pop();

            for (auto &d : dir) {

                int newRow = row + d.first;
                int newCol = col + d.second;

                // Check boundary
                if (newRow >= 0 && newRow < n &&
                    newCol >= 0 && newCol < m) {

                    // Relaxation step
                    if (dist[newRow][newCol] > dist[row][col] + 1) {

                        dist[newRow][newCol] =
                            dist[row][col] + 1;

                        q.push({newRow, newCol});
                    }
                }
            }
        }

        return dist;
    }
};