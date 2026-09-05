/*
Description:
    Find the contiguous subarray containing only non-negative numbers with
    the maximum sum. If multiple subarrays have the same sum, choose the
    longest one; if there is still a tie, choose the leftmost one. Return
    {-1} when the array contains no non-negative element.

Intuition:
    A negative number breaks a valid subarray, so every candidate belongs to
    one contiguous block of non-negative numbers. While scanning a block from
    left to right, the sum of the current prefix can only increase because
    every element is non-negative. Therefore, each prefix is a candidate and
    can be compared with the best candidate found so far.

Approach:
    1. Skip negative elements until the start of a non-negative block.
    2. Extend through the block while maintaining its running sum and length.
    3. Update the answer when the sum is larger, or when the sum ties but the
       candidate is longer or starts earlier.
    4. Copy the best subarray into the result. Return {-1} if none was found.

Example:
    arr = [1, 2, 5, -7, 2, 3]
    The non-negative blocks are [1, 2, 5] with sum 8 and [2, 3] with sum 5.
    Hence, the maximum-sum non-negative subarray is [1, 2, 5].

Complexity:
    Time: O(n), Space: O(1) auxiliary space (O(n) including the returned result)
*/
class Solution {
  public:
    vector<int> findSubarray(vector<int>& arr) {
        int n=arr.size();
        int sum=0,i=0,maxSum=-1;
        int start=0,bestStart=-1,bestLen=0;
        
        while(i<n){
            while(i<n && arr[i]<0){
                i++;
            }
            sum=0;
            start=i;
            while(i<n && arr[i]>=0){
                sum+=arr[i];
                int currLen=i-start+1;
                if(sum>maxSum || (sum==maxSum && currLen>bestLen)
                || (sum==maxSum && currLen==bestLen && start<bestStart)){
                    maxSum=sum;
                    bestLen=currLen;
                    bestStart=start;
                }
                i++;
            }
            sum=0;
        }
        if(bestStart==-1) return {-1};
        vector<int> res;
        for(int j=bestStart;j<bestStart+bestLen;j++){
            res.push_back(arr[j]);
        }
        return res;
    }
};