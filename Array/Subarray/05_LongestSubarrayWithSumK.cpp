/*
Description:
    Find the length of the longest contiguous subarray whose sum is exactly k.

Intuition:
    Let prefSum[i] be the sum of elements from index 0 through i. The sum of
    a subarray from j + 1 through i is prefSum[i] - prefSum[j]. Therefore, for
    the current prefix sum prefSum, we need an earlier prefix sum equal to
    prefSum - k. To get the longest subarray, keep only the first index where
    each prefix sum appears.

Approach:
    1. Traverse the array while maintaining the running prefix sum.
    2. If prefSum == k, the subarray from index 0 has length i + 1.
    3. If prefSum - k was seen before at index j, update the answer with i - j.
    4. Store the current prefix sum only if it has not been seen before.

Example:
    arr = [1, 2, 3, 1, 1, 1], k = 6
    At index 2, prefSum = 6, so [1, 2, 3] has length 3.
    At index 5, prefSum = 9 and prefSum - k = 3. The prefix sum 3 was first
    seen at index 1, so the subarray from index 2 to 5 has sum 6 and length 4.
    Thus, the answer is 4.

Complexity:
    Time: O(n), Space: O(n)
*/
class Solution {
    public:
      int longestSubarray(vector<int>& arr, int k) {
          int n = arr.size();
          unordered_map<int, int> mp;
          int prefSum = 0;
          int ans = 0;

          for(int i = 0; i < n; i++) {
              prefSum += arr[i];

              if(prefSum == k) {
                  ans = i + 1;
              }
              else if(mp.find(prefSum - k) != mp.end()) {
                  ans = max(ans, i - mp[prefSum - k]);
              }

              if(mp.find(prefSum) == mp.end()) {
                  mp[prefSum] = i;
              }
          }

          return ans;
      }
  };