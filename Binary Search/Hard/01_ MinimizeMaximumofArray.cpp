/*
Problem Explanation:
We need to minimize the maximum value in the array by redistributing
excess value from left to right. In one operation, some value can be moved
from an element to its next element, so the total sum stays the same.

Intuition:
If we guess a maximum allowed value mid, then we try to check whether it is
possible to make every element <= mid. We process the array from left to right.
If an element is already greater than mid, the answer is impossible for this mid.
Otherwise, we pass any extra room to the next element by shifting the difference.

Approach:
Use binary search on the answer. For each mid, greedily validate whether the
array can be transformed so that every element is at most mid. If yes, try a
smaller mid; otherwise, move to a larger mid.

Example:
nums = [3, 7, 1, 6]
If we try mid = 5:
- At index 0, value 3 is already <= 5, so we pass the extra 2 to the next element.
- Now the next value becomes 7 - 2 = 5, which is okay.
- Then the next value becomes 1 + 0 = 1, and the last becomes 6.
- The last element can still be adjusted, and the final maximum becomes 5.
So 5 is feasible. We then try smaller values to see if we can do even better.
*/

class Solution {
public:
    bool isValid(vector<int> &nums, int mid) {
        int n = nums.size();

        vector<long long> arr(nums.begin(), nums.end());

        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > mid)
                return false;

            long long buffer = (long long)mid - arr[i];
            arr[i] += buffer;
            arr[i + 1] -= buffer;
        }

        return arr[n - 1] <= mid;
    }

    int minimizeArrayValue(vector<int>& nums) {
        int low = 0;
        int high = *max_element(nums.begin(), nums.end());
        int ans = high;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (isValid(nums, mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        return ans;
    }
};