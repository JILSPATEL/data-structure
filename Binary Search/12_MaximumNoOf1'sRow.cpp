/**
 * Problem Overview:
 * -----------------
 * Given a binary matrix `Mat` of size N x M (each row is sorted),
 * find the index of the row that contains the **maximum number of 1s**.
 *
 * Key Observations:
 * -----------------
 * - Each row is sorted (0s first, then 1s).
 * - Number of 1s in a row = M - index of first occurrence of 1.
 *
 * Approach:
 * ---------
 * 1. Use a custom `lowerBound` function to find the first index
 *    where value >= 1 in a row.
 * 2. For each row:
 *      - Compute number of 1s using: M - lowerBound(row, 1)
 *      - Track the row index having the maximum count.
 *
 * Why Binary Search?
 * ------------------
 * - Since each row is sorted, binary search helps find the first 1
 *   efficiently in O(log M) time.
 *
 * Time Complexity:
 * ----------------
 * O(N * log M)
 *
 * Space Complexity:
 * -----------------
 * O(1) extra space
 */

class Solution {
  public:
    // Finds the first index where arr[index] >= x
    int lowerBound(vector<int>& arr, int x) {
        int low = 0;
        int high = arr.size() - 1;
        int ans = arr.size();

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] >= x) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }

    int maxOnes(vector<vector<int>>& Mat, int N, int M) {
        int cntMax = -1;
        int idx = -1;

        for (int i = 0; i < N; i++) {
            int cntOnes = M - lowerBound(Mat[i], 1);

            if (cntOnes > cntMax) {
                cntMax = cntOnes;
                idx = i;
            }
        }
        return idx;
    }
};
