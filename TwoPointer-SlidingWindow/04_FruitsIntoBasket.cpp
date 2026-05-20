/**
 * Problem: Fruit Into Baskets (LeetCode 904)
 * ------------------------------------------
 * You are given an array `fruits` where fruits[i] is the type of fruit.
 * You have two baskets, and each basket can only hold one type of fruit.
 * You want to collect the maximum number of fruits in a contiguous subarray
 * containing at most 2 distinct types.
 *
 * Approaches:
 * 1) Brute Force:
 *    - Generate all subarrays and check if they contain at most 2 distinct fruits.
 *    - Time Complexity: O(n^2)
 *
 * 2) Sliding Window (Optimal) ✅:
 *    - Use two pointers (i, j) and a hashmap to track frequency of fruits.
 *    - Expand window using j.
 *    - If distinct fruits > 2, shrink window from left (i).
 *    - Maintain maximum window size.
 *    - Time Complexity: O(n)
 *    - Space Complexity: O(1) (at most 3 keys in map)
 */

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();

        unordered_map<int, int> freq; // stores count of each fruit type

        int i = 0, j = 0;  // sliding window pointers
        int maxLen = 0;    // result

        while (j < n) {
            // Add current fruit to window
            freq[fruits[j]]++;

            // If more than 2 distinct fruits, shrink window
            while (freq.size() > 2) {
                freq[fruits[i]]--;

                if (freq[fruits[i]] == 0) {
                    freq.erase(fruits[i]);
                }

                i++;
            }

            // Update max length of valid window
            maxLen = max(maxLen, j - i + 1);

            j++;
        }

        return maxLen;
    }
};