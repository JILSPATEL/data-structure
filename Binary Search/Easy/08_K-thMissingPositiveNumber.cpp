/************************************************************
 Problem: K-th Missing Positive Number

 Description:
 Given a sorted array `arr` of positive integers and an integer `k`,
 return the k-th missing positive number.

 Example:
 arr = [2, 3, 4, 7, 11], k = 5
 Missing numbers are: 1, 5, 6, 8, 9
 Answer = 9

 ------------------------------------------------------------
 Key Observation:
 At any index `i` (0-based), the number of missing positive
 integers before arr[i] is:

     missing = arr[i] - (i + 1)

 Explanation:
 - In an ideal array without missing numbers,
   the value at index i should be (i + 1).
 - The difference tells us how many numbers are missing.

 ------------------------------------------------------------
 Binary Search Logic:
 We search for the first index where:
     missing >= k

 - If missing < k, the k-th missing number lies to the right.
 - If missing >= k, the k-th missing number lies to the left.

 When the loop ends:
 - `high` points to the last index where missing < k.

 ------------------------------------------------------------
 Final Answer Logic:
 The k-th missing number is:

     k + high + 1

 This works because:
 - `high + 1` numbers exist in the array before that position.
 - Adding k shifts us to the correct missing number.

 ------------------------------------------------------------
 Time Complexity:
 - Binary Search: O(log n)

 Space Complexity:
 - O(1)

************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {

        int n = arr.size();
        int low = 0;
        int high = n - 1;

        while (low <= high) {

            int mid = low + (high - low) / 2;
            int missing = arr[mid] - (mid + 1);

            if (missing < k) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return k + high + 1;
    }
};
