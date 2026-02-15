/**
 * Problem Overview:
 * -----------------
 * Given a 2D matrix where:
 * 1. Each row is sorted in ascending order.
 * 2. The first element of each row is greater than
 *    the last element of the previous row.
 *
 * Determine whether a given `target` exists in the matrix.
 *
 * Key Idea:
 * ---------
 * Treat the 2D matrix as a **flattened 1D sorted array**.
 *
 * Index Mapping:
 * --------------
 * If `mid` is the index in the imaginary 1D array:
 *   - row = mid / m
 *   - col = mid % m
 *
 * This mapping allows us to apply binary search directly
 * on the matrix without extra space.
 *
 * Why Binary Search?
 * ------------------
 * Because the entire matrix follows sorted order when read row-wise.
 *
 * Time Complexity:
 * ----------------
 * O(log(n * m))
 *
 * Space Complexity:
 * -----------------
 * O(1)
 */

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int n = matrix.size();
        int m = matrix[0].size();

        int low = 0;
        int high = n * m - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            int row = mid / m;
            int col = mid % m;

            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return false;
    }
};
