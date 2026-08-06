/**
 * Problem Overview:
 * -----------------
 * Given an array `arr` and an integer `k`, we want to split the array into
 * at most `k` continuous subarrays such that the **maximum subarray sum**
 * is minimized.
 *
 * Key Idea:
 * ---------
 * This problem is solved using **Binary Search on Answer**.
 *
 * - The minimum possible answer (`low`) is the maximum element in the array,
 *   because no subarray can have a sum smaller than the largest single element.
 * - The maximum possible answer (`high`) is the sum of all elements,
 *   when the array is taken as a single subarray.
 *
 * We binary search between `low` and `high` to find the smallest value
 * for which it is possible to split the array into at most `k` subarrays.
 *
 * Helper Function (`solve`):
 * -------------------------
 * - Checks if we can split the array into ≤ k subarrays
 *   such that no subarray has a sum greater than `mid`.
 *
 * Time Complexity:
 * ----------------
 * O(n log(sum - max))
 *
 * Space Complexity:
 * -----------------
 * O(1) (ignoring input storage)
 */

class Solution {
  public:
    // Helper function to check feasibility
    bool solve(vector<int>& arr, int mid, int k) {
        int cnt = 1;     // Number of subarrays
        int total = 0;   // Current subarray sum

        for (int num : arr) {
            if (total + num <= mid) {
                total += num;
            } else {
                cnt++;
                total = num;
            }
        }
        return cnt <= k;
    }

    int splitArray(vector<int>& arr, int k) {
        int low = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (solve(arr, mid, k)) {
                ans = mid;
                high = mid - 1;  // Try smaller maximum sum
            } else {
                low = mid + 1;   // Increase allowed sum
            }
        }
        return ans;
    }
};
