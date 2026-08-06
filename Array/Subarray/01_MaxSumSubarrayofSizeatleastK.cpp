/*
Problem: Find the maximum sum of a subarray with length at least k.

Description:
We must choose a subarray whose size is at least k and whose sum is
as large as possible.

Intuition:
Take a fixed window of size k as the base. Then, if we find a positive
prefix sum ending just before the window, extending the window with that
prefix increases the total sum.

Approach:
1. Compute the sum of the first k elements.
2. Maintain a running sum for the current k-sized window.
3. Track the best prefix sum that can be attached before the window.
4. For each new position, slide the window by one step.
5. Update the answer using current window sum + best positive prefix.

Example:
arr = [1, 2, 3, -10, 4, 5], k = 3
Base windows of size 3:
[1, 2, 3] = 6
[2, 3, -10] = -5
[3, -10, 4] = -3
[-10, 4, 5] = -1
Best answer is [1, 2, 3] = 6, and if a positive prefix exists before a
later window, it can be added to improve the sum.
*/
class Solution {
public:
    int maxSumWithK(vector<int>& arr, int k) {
        int n = arr.size();
        
        int currWinSum=0;
        for(int i=0;i<k;i++){
            currWinSum+=arr[i];
        }
        
        int maxi=currWinSum;
        int prevSubSum=0;
        
        for(int i=k;i<n;i++){
            currWinSum=currWinSum+arr[i]-arr[i-k];
            prevSubSum+=arr[i-k];
            if(prevSubSum<0){
                prevSubSum=0;
            }
            maxi=max(maxi,currWinSum+prevSubSum);
        }

        return maxi;
    }
};