/**
 * Problem: Subarrays With Sum in Range
 * ------------------------------------
 * Count the number of subarrays whose sum lies in the inclusive range [l, r].
 *
 * Intuition:
 * If we can count how many subarrays have sum <= x, then the answer for [l, r]
 * becomes:
 *   count(sum <= r) - count(sum <= l - 1)
 *
 * This works because the first count includes every valid subarray with sum up
 * to r, and the second count removes all subarrays with sum smaller than l.
 *
 * Approach:
 * 1. Use a sliding window to count subarrays with sum <= x.
 * 2. Expand the right pointer and keep adding elements to the window sum.
 * 3. While the sum becomes greater than x, shrink the window from the left.
 * 4. For every right index, all subarrays ending at that index and starting
 *    between start and end are valid, so add (end - start + 1) to the count.
 * 5. Compute count(sum <= r) and count(sum <= l - 1), then subtract them.
 *
 * Why sliding window works here:
 * This method assumes all array elements are non-negative. If negative numbers
 * are allowed, shrinking the window would not always guarantee a smaller sum.
 *
 * Example:
 * arr = [1, 2, 3], l = 2, r = 3
 *
 * Subarrays are:
 * [1] = 1, [1,2] = 3, [1,2,3] = 6, [2] = 2, [2,3] = 5, [3] = 3
 * Valid subarrays in [2, 3] are [1,2], [2], and [3]
 * Answer = 3
 *
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 */

class Solution {
  public:
    int countSubArr(vector<int> &arr, int x){
        int n=arr.size();
        int start=0;
        int end=0;
        int sum=0;
        int cnt=0;
        
        while(end<n){
            sum+=arr[end];
            while (start <= end && sum > x){
                sum-=arr[start];
                start++;
            }
            cnt+=(end-start+1);
            end++;
        }
        return cnt;
    }
    int countSubarray(vector<int>& arr, int l, int r) {
        int n=arr.size();
        int lessL=countSubArr(arr,l-1);
        int lessR=countSubArr(arr,r);
        return lessR-lessL;
    }
};