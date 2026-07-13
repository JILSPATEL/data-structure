/*
Problem Explanation:
We need to find the maximum possible value at a given index such that the
entire array can be formed with each element at least 1, the value at the
chosen index is as large as possible, and the total sum of the array does not
exceed maxSum.

Intuition:
If we guess a value mid for the target index, we can check whether it is
possible to build the array around it. The values on the left and right of the
index must decrease by 1 as we move away from the center, because the array is
bounded by the maximum value at the chosen index.

Approach:
Use binary search on the answer. For each mid, we compute the minimum sum
needed to create a valid array with the value at the target index equal to mid.
If that sum is <= maxSum, then mid is feasible and we try a larger value.
Otherwise, mid is too large and we move smaller.

Example:
n = 5, index = 2, maxSum = 10
If we try mid = 4:
- The value at index 2 is 4.
- The left side can be [3, 2, 1] and the right side can be [3, 2] in a valid shape.
- Total sum becomes 4 + 3 + 2 + 3 + 2 = 14, which is too large.
So mid = 4 is not feasible.
If we try mid = 3:
- The total sum becomes 3 + 2 + 1 + 2 + 1 = 9, which is feasible.
So the answer is 3.
*/

class Solution {
public:
    bool check(int n, int idx, int mid, int maxSum) {

        long long leftIdxDiff = idx;
        long long leftSum = 0;

        if (leftIdxDiff <= mid - 1) {
            leftSum = (long long)(mid - 1 + mid - leftIdxDiff) * leftIdxDiff / 2;
        } else {
            leftSum = (long long)(mid - 1) * mid / 2;
            leftSum += leftIdxDiff - (mid - 1);
        }

        long long rightIdxDiff = n - idx - 1;
        long long rightSum = 0;

        if (rightIdxDiff <= mid - 1) {
            rightSum = (long long)(mid - 1 + mid - rightIdxDiff) * rightIdxDiff / 2;
        } else {
            rightSum = (long long)(mid - 1) * mid / 2;
            rightSum += rightIdxDiff - (mid - 1);
        }

        long long sum = leftSum + rightSum + mid;

        return sum <= maxSum;
    }

    int maxValue(int n, int index, int maxSum) {
        int low = 1;
        int high = maxSum;
        int ans = 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (check(n, index, mid, maxSum)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};