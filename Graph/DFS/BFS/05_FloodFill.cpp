/**
 * Problem: Flood Fill
 * Platform: LeetCode
 * Approach: Depth First Search (DFS)
 * 
 * Description:
 * 
 * We are given:
 * - A 2D image matrix
 * - Starting pixel (sr, sc)
 * - New color
 * 
 * Task:
 * Replace the starting pixel and all connected pixels
 * having the same initial color with the new color.
 * 
 * Connectivity:
 * - Up
 * - Down
 * - Left
 * - Right
 * 
 * ---------------------------------------------------------
 * Approaches:
 * 
 * 1. DFS Traversal (Used Here)
 *    - Start from source pixel.
 *    - Visit all connected pixels having same color.
 *    - Change their color recursively.
 * 
 * 2. BFS Traversal
 *    - Same logic using queue instead of recursion.
 * 
 * ---------------------------------------------------------
 * Example:
 * Input:
 * image = [[1,1,1],
 *          [1,1,0],
 *          [1,0,1]]
 * sr = 1, sc = 1, color = 2
 *
 * Output:
 * [[2,2,2],
 *  [2,2,0],
 *  [2,0,1]]
 *
 * ---------------------------------------------------------
 * Why DFS?
 *
 * DFS efficiently explores all connected cells
 * recursively in grid traversal problems.
 *
 * ---------------------------------------------------------
 * Time Complexity:
 * O(m * n)
 *
 * Every cell is visited at most once.
 *
 * ---------------------------------------------------------
 * Space Complexity:
 * O(m * n)
 *
 * Recursive stack in worst case.
 */

class Solution {
public:

    /**
     * DFS Function
     * ------------------------------------------------
     * Parameters:
     * 
     * sr, sc     -> Current cell coordinates
     * mat        -> Result matrix
     * image      -> Original image matrix
     * initColor  -> Original color to replace
     * color      -> New color
     */
    void dfs(int sr,
             int sc,
             vector<vector<int>>& mat,
             vector<vector<int>>& image,
             int initColor,
             int color) {

        // Change current pixel color
        mat[sr][sc] = color;

        /**
         * 4 Possible Directions
         * Down, Right, Up, Left
         */
        vector<pair<int, int>> dir = {
            {1, 0},
            {0, 1},
            {-1, 0},
            {0, -1}
        };

        /**
         * Explore all neighboring cells
         */
        for (auto& vec : dir) {

            int x = sr + vec.first;
            int y = sc + vec.second;

            /**
             * Conditions:
             * 
             * 1. Inside matrix boundary
             * 2. Same initial color
             * 3. Not already colored
             */
            if (x >= 0 &&
                x < mat.size() &&
                y >= 0 &&
                y < mat[0].size() &&
                image[x][y] == initColor &&
                mat[x][y] != color) {

                // Recursive DFS call
                dfs(x, y, mat, image, initColor, color);
            }
        }
    }

    vector<vector<int>> floodFill(vector<vector<int>>& image,
                                  int sr,
                                  int sc,
                                  int color) {

        /**
         * Create copy of original image
         * Result will be stored in mat
         */
        vector<vector<int>> mat = image;

        // Initial color of starting pixel
        int initColor = image[sr][sc];

        /**
         * Start DFS traversal
         */
        dfs(sr, sc, mat, image, initColor, color);

        return mat;
    }
};