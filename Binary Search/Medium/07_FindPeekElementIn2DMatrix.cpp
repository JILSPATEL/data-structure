/**
 * Problem: Find a Peak Element in a 2D Grid
 *
 * A peak element in a 2D matrix is an element that is strictly greater than
 * its left and right neighbors (horizontal neighbors). The matrix is assumed
 * to have valid boundaries, and out-of-bound neighbors are treated as -1.
 *
 * Approach Used: Binary Search on Columns (Optimized Approach)
 *
 * Idea:
 * - Instead of scanning the entire matrix, we apply binary search on columns.
 * - For a chosen column `mid`, we find the row index that contains the maximum
 *   element in that column.
 * - Once we have the maximum element in the column, we compare it with its
 *   immediate left and right neighbors.
 *
 * Key Observations:
 * - If the current element is greater than both left and right neighbors,
 *   then it is a peak → return its position.
 * - If the left neighbor is greater, then a peak must exist on the left side
 *   (move binary search to the left).
 * - Otherwise, a peak must exist on the right side
 *   (move binary search to the right).
 *
 * Helper Function:
 * - maxEle(): Finds the row index of the maximum element in a given column.
 *
 * Time Complexity:
 * - Finding max in one column: O(n)
 * - Binary search over columns: O(log m)
 * - Total Time: O(n log m)
 *
 * Space Complexity:
 * - O(1) extra space (ignoring input matrix)
 *
 * This approach is much more efficient than a brute-force O(n*m) scan.
 */

class Solution {
public:
    int maxEle(vector<vector<int>>& mat, int n, int m, int col) {
        int maxVal = -1;
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (mat[i][col] > maxVal) {
                maxVal = mat[i][col];
                idx = i;
            }
        }
        return idx;
    }

    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        int low = 0;
        int high = m - 1;

        while (low <= high) {
            int mid = (low + high) / 2;
            int row = maxEle(mat, n, m, mid);

            int left = mid - 1 >= 0 ? mat[row][mid - 1] : -1;
            int right = mid + 1 < m ? mat[row][mid + 1] : -1;

            if (mat[row][mid] > left && mat[row][mid] > right) {
                return {row, mid};
            } else if (mat[row][mid] < left) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return {-1, -1};
    }
};
