/*
Problem: Maximum Beauty of an Array After Applying Operation

Description:
For each value nums[i], we can transform it to any integer in the range
[nums[i] - k, nums[i] + k]. We want to find the maximum number of transformed
values that can all be made equal to the same target value.

Approach:
1. Convert each number into an interval [nums[i] - k, nums[i] + k].
2. Sort the intervals by start value.
3. Maintain a queue of active interval ends.
4. Remove intervals whose end is before the current start.
5. The size of the active set at any point gives the maximum overlap.

Example:
nums = [4, 6, 1, 2], k = 2
Intervals are:
- [2, 6]
- [4, 8]
- [-1, 3]
- [0, 4]
The maximum overlap is 3, because values near 4 can be reached by three numbers.
Answer = 3
*/

class Solution {
public:
    int maximumBeauty(vector<int>& nums, int k) {
        int n=nums.size();
        vector<pair<int,int>> interval;
        for(int i=0;i<n;i++){
            interval.push_back({nums[i]-k,nums[i]+k});
        }
        sort(interval.begin(),interval.end());

        queue<int> deq;
        int maxi=INT_MIN;
        for(auto &it:interval){
            int start=it.first;
            int end=it.second;

            while(!deq.empty() && deq.front()<start){
                deq.pop();
            }
            deq.push(end);
            maxi=max(maxi,(int)deq.size());
        }
        return maxi;
    }
};