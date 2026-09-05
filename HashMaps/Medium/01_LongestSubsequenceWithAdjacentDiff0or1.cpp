/*
Description:
    Find the length of the longest subsequence whose adjacent elements differ
    by 0 or 1. The subsequence must preserve the original order, but its
    elements do not need to be contiguous.

Intuition:
    When processing a value x, it can be appended to any valid subsequence
    that ends in x - 1, x, or x + 1. Store the best length for each ending
    value in a hash map, so the best predecessor can be found in constant
    average time.

Approach:
    1. Traverse the array from left to right to preserve subsequence order.
    2. For the current value x, find the largest stored length for x - 1, x,
       and x + 1.
    3. Set the best length ending at x to that predecessor length plus one.
    4. Update the overall maximum length.

Example:
    arr = [2, 3, 5, 2, 3]
    The subsequence [2, 3, 2, 3] is valid because every adjacent difference
    is 1. Its length is 4, which is the longest valid subsequence.

Complexity:
    Time: O(n) average, Space: O(n)
*/
class Solution {
  public:
    int maxLenSub(vector<int> &arr) {
        unordered_map<int,int> mp;
        int n=arr.size();
        int maxLen=0;
        for(int i=0;i<n;i++){
            int len=0;
            if(mp.find(arr[i]-1)!=mp.end() && len<mp[arr[i]-1]){
                len=mp[arr[i]-1];
            }
            if(mp.find(arr[i])!=mp.end() && len<mp[arr[i]]){
                len=mp[arr[i]];
            }
            if(mp.find(arr[i]+1)!=mp.end() && len<mp[arr[i]+1]){
                len=mp[arr[i]+1];
            }
            
            mp[arr[i]]=len+1;
            maxLen=max(maxLen,len+1);
        }
        return maxLen;
    }
};