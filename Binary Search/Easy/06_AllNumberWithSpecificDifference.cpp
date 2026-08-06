#include <bits/stdc++.h>
using namespace std;

/**
 * Class Solution
 * ----------------
 * Problem:
 * Given a positive number n and a number d,
 * count how many numbers x (1 ≤ x ≤ n) satisfy:
 *
 *      x - sum_of_digits(x) >= d
 *
 * Constraints:
 * 1 ≤ n ≤ 10^9
 * 1 ≤ d ≤ 10^9
 *
 * Approach Used:
 * Binary Search on the answer
 *
 * Reasoning:
 * The function f(x) = x - sum_of_digits(x) generally increases as x increases.
 * Once f(x) becomes >= d, it will remain >= d for all larger x.
 *
 * So valid numbers form a continuous range:
 *      [firstValid, n]
 *
 * We use binary search to find the smallest such number.
 */

class Solution {
public:

    /**
     * digitSum(n)
     * ------------
     * Returns the sum of digits of number n.
     *
     * Example:
     * n = 123 → sum = 1 + 2 + 3 = 6
     *
     * Time Complexity: O(log n)
     */
    int digitSum(int n) {
        int sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }

    /**
     * getCount(n, d)
     * --------------
     * Finds the count of numbers x such that:
     *
     *      1 ≤ x ≤ n
     *      x - sum_of_digits(x) >= d
     *
     * Steps:
     * 1. Binary search for the first valid number
     * 2. Count numbers from firstValid to n
     *
     * Time Complexity:
     * Binary search: O(log n)
     * digitSum per check: O(log n)
     * Total: O(log^2 n)
     */
    int getCount(int n, int d) {

        int low = 1;
        int high = n;
        int firstValid = n + 1;

        /**
         * Binary Search
         * -------------
         * We search for the smallest x such that:
         *      x - digitSum(x) >= d
         */
        while (low <= high) {

            int mid = low + (high - low) / 2;

            if ((mid - digitSum(mid)) >= d) {
                firstValid = mid;     // mid is valid, try smaller
                high = mid - 1;
            } else {
                low = mid + 1;        // mid is invalid, go right
            }
        }

        /**
         * If no valid number exists
         */
        if (firstValid == n + 1)
            return 0;

        /**
         * Count of valid numbers
         * All numbers from firstValid to n are valid
         */
        return n - firstValid + 1;
    }
};
