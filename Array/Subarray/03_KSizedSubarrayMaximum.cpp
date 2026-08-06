/*
Problem: For every subarray of size k, return the maximum element.

Description:
We slide a window of size k across the array and keep track of the
maximum element in the current window.

Intuition:
A priority queue lets us quickly get the largest element in the current
window. Each element is stored with its index so we can ignore values
that have moved out of the window.

Approach:
1. Insert the first k elements into a max heap.
2. The top of the heap is the answer for the first window.
3. For each new index i, insert arr[i] into the heap.
4. Remove elements whose index is outside the current window.
5. Record the heap top for every window.

Example:
arr = [1, 3, -1, -3, 5, 3, 6, 7], k = 3
Windows and maximums:
[1, 3, -1] -> 3
[3, -1, -3] -> 3
[-1, -3, 5] -> 5
[-3, 5, 3] -> 5
[5, 3, 6] -> 6
[3, 6, 7] -> 7
*/
class Solution {
  public:
    vector<int> maxOfSubarrays(vector<int>& arr, int k) {
        int n=arr.size();
        vector<int> res;
        priority_queue<pair<int,int>>pq;
        for(int i=0;i<k;i++){
            pq.push({arr[i],i});
        }
        res.push_back(pq.top().first);
        for(int i=k;i<n;i++){
            pq.push({arr[i],i});
            while(pq.top().second<=i-k){
                pq.pop();
            }
            res.push_back(pq.top().first);
        }
        return res;
    }
};