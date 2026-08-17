/*
Problem: Special Array II

Description:
A subarray is called special if no two adjacent elements in that subarray have
 the same parity. For each query [l, r], determine whether nums[l..r] is special.

Approach:
1. Build a prefix array where prefix[i] stores how many parity mismatches have
   been found up to index i.
2. For every adjacent pair, if both numbers have the same parity, count it as a
   "bad" transition.
3. For a query [l, r], the number of bad transitions in that range is:
      prefix[r] - prefix[l]
4. If this difference is 0, the range is special.

Example:
nums = [1, 2, 2, 3]
queries = [[0, 3], [1, 3], [2, 3]]
- [0, 3] -> 1, 2, 2, 3 contains a bad pair (2, 2) => false
- [1, 3] -> 2, 2, 3 contains a bad pair (2, 2) => false
- [2, 3] -> 2, 3 have different parity => true
Answer = [false, false, true]
*/

class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
        int n=nums.size();
        vector<int> prefix(n,0);

        for(int i=1;i<n;i++){
            prefix[i]=prefix[i-1];
            if((nums[i]%2)==(nums[i-1]%2)){
                prefix[i]++;
            }
        }
        vector<bool> ans;
        for(auto &q:queries){
            int l=q[0];
            int r=q[1];

            int bad=prefix[r]-prefix[l];
            ans.push_back(bad==0);
        }
        return ans;
    }
};