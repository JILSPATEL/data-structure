/************************************************************
 Problem: Capacity To Ship Packages Within D Days

 Description:
 Given an array `weights` where weights[i] represents the weight
 of the i-th package and an integer `days`, find the minimum
 ship capacity required to ship all packages within the given
 number of days.

 Rules:
 - Packages must be shipped in the given order.
 - Each day, the ship can carry packages whose total weight
   does not exceed the ship's capacity.
 - Each package must be shipped entirely (no splitting).

 ------------------------------------------------------------
 Key Observations:
 1. If the ship capacity is very small, more days are required.
 2. If the ship capacity is large, fewer days are required.
 3. As capacity increases, required days never increase.
    (Monotonic behavior)

 This monotonic nature allows us to use Binary Search
 on the ship capacity.

 ------------------------------------------------------------
 Search Space:
 - Minimum capacity = maximum weight in the array
   (at least one package must fit)
 - Maximum capacity = sum of all weights
   (ship all packages in one day)

 ------------------------------------------------------------
 Helper Function:
 For a given capacity, simulate the shipping process
 and calculate how many days are required.

 ------------------------------------------------------------
 Binary Search Logic:
 - If a capacity can ship within the given number of days,
   try to minimize the capacity.
 - Otherwise, increase the capacity.

 ------------------------------------------------------------
 Time Complexity:
 - Checking capacity: O(n)
 - Binary search: O(log(sum(weights)))
 - Total complexity: O(n log n)

 Space Complexity:
 - O(1) extra space
************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int solve(vector<int> &weights, int cap) {
        int load = 0;
        int days = 1;

        for (int weight : weights) {
            if (load + weight <= cap) {
                load += weight;
            } else {
                days++;
                load = weight;
            }
        }
        return days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        int low = *max_element(weights.begin(), weights.end());
        int high = accumulate(weights.begin(), weights.end(), 0);

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (solve(weights, mid) <= days) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return low;
    }
};
