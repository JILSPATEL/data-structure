/**
 * Problem Overview:
 * -----------------
 * Given a matrix where:
 * 1. Each row is sorted in ascending order (left → right)
 * 2. Each column is sorted in ascending order (top → bottom)
 *
 * Determine whether a given `target` exists in the matrix.
 *
 * Key Idea (Staircase Search):
 * ---------------------------
 * Start from the **top-right corner** of the matrix.
 *
 * - If the current element is equal to `target` → found.
 * - If the current element is greater than `target` →
 *   move LEFT (column--), because all elements below are larger.
 * - If the current element is smaller than `target` →
 *   move DOWN (row++), because all elements to the left are smaller.
 *
 * This step-by-step elimination reduces the search space efficiently.
 *
 * Why This Works:
 * ---------------
 * From the top-right:
 * - Left side contains smaller elements
 * - Downward direction contains larger elements
 *
 * Time Complexity:
 * ----------------
 * O(N + M)
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

        int row = 0;
        int col = m - 1;

        while (row < n && col >= 0) {
            if (matrix[row][col] == target) {
                return true;
            } else if (matrix[row][col] > target) {
                col--;     // Move left
            } else {
                row++;     // Move down
            }
        }
        return false;
    }
};
