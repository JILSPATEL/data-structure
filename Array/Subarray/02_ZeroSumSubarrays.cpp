/*
Problem: Count the number of subarrays whose sum is zero.

Description:
We need to count every contiguous subarray whose total sum becomes 0.

Intuition:
If two prefix sums are equal, the elements between those positions must
sum to 0. So we can use a hash map to count how many times each prefix
sum has appeared so far.

Approach:
1. Keep a running prefix sum while traversing the array.
2. If the prefix sum becomes 0, that subarray itself is valid.
3. If the same prefix sum has been seen before, every previous
     occurrence forms a zero-sum subarray with the current index.
4. Add the frequency of the current prefix sum to the answer.
5. Increment the frequency of the current prefix sum in the map.

Example:
arr = [6, -1, -3, 4, -2, 2, 4, 6, -12, -7]
Prefix sums:
6, 5, 2, 6, 4, 6, 10, 16, 4, -3
Repeated prefix sums at 6 and 4 indicate multiple zero-sum subarrays.
*/
class Solution {
  public:
    int findSubarray(vector<int> &arr) {
        unordered_map<long long,int> freq;
        long long prefixSum=0,cnt=0;
        
        for(int x:arr){
            prefixSum += x;
            if(prefixSum==0){
                cnt+=1;
            }
            // If the same prefix sum was seen before, the subarray between
            // the previous occurrence and the current index sums to 0.
            // Each earlier occurrence gives one valid zero-sum subarray, so
            // we add its frequency to the answer.
            if(freq.find(prefixSum)!=freq.end()){
                cnt+=freq[prefixSum];
            }
            freq[prefixSum]++;
        }
        return cnt;
    }
};