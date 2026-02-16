/**
 * Problem: Find the Median of a Row-wise Sorted Matrix
 *
 * Given a matrix where:
 * - Each row is individually sorted in non-decreasing order
 * - The total number of elements (rows * cols) is odd
 *
 * The task is to find the median of the matrix.
 *
 * Key Insight:
 * - Since rows are sorted but the matrix as a whole is not,
 *   we cannot flatten and sort efficiently.
 * - Instead, we perform **binary search on the value range**
 *   (not on indices).
 *
 * Approach: Binary Search on Answer
 *
 * Steps:
 * 1. Define the search space:
 *    - `low` = minimum element among the first elements of all rows
 *    - `high` = maximum element among the last elements of all rows
 *
 * 2. For a guessed value `mid`, count how many elements in the matrix
 *    are less than or equal to `mid`.
 *    - Since each row is sorted, we can do this using `upper_bound`
 *      in O(log cols) time per row.
 *
 * 3. Compare this count with the required position of the median:
 *    - Median position = (rows * cols + 1) / 2
 *
 * 4. Adjust binary search:
 *    - If count < median position → median lies on the right
 *    - Else → median lies on the left (or could be mid itself)
 *
 * Helper Function:
 * - countLessEqual(): Returns count of elements ≤ mid in a sorted row
 *
 * Time Complexity:
 * - For each binary search step: O(rows * log(cols))
 * - Value-range binary search: O(log(maxValue - minValue))
 * - Overall: O(rows * log(cols) * log(range))
 *
 * Space Complexity:
 * - O(1) extra space
 *
 * This is an efficient solution compared to flattening and sorting
 * which would take O((rows * cols) log(rows * cols)).
 */

class Solution {
  public:
    int countLessEqual(vector<int>& row, int mid) {
        return upper_bound(row.begin(), row.end(), mid) - row.begin();
    }

    int median(vector<vector<int>> &matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        // Initial search range based on row-wise sorted property
        int low = matrix[0][0];
        int high = matrix[0][cols - 1];

        for (int i = 1; i < rows; i++) {
            low = min(low, matrix[i][0]);
            high = max(high, matrix[i][cols - 1]);
        }

        // Binary search on the value range
        while (low < high) {
            int mid = (low + high) / 2;
            int count = 0;

            // Count elements <= mid across all rows
            for (int i = 0; i < rows; i++) {
                count += countLessEqual(matrix[i], mid);
            }

            if (count < (rows * cols + 1) / 2)
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }
};
