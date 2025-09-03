/*
Given a sequence of n numbers design a linear time algorithm to compute
the length of the maximum sum sub array. including negatives
*/

#include <bits/stdc++.h>
using namespace std;

pair<int,int> maxSumSubarrayOfLengthK(vector<int>& arr, int k) {
    int n=arr.size();
    if(n<k) return {0,-1};
    int windowSum=0;
    for (int i = 0; i < k; i++){
        windowSum+=arr[i];
    }
    int maxSum=windowSum,baseIdx=0;

    for (int i = k; i < n; i++){
        windowSum+=arr[i]-arr[i-k];
        if(windowSum>maxSum){
            maxSum=windowSum;
            baseIdx=i-k+1;
        }
    }
    return {maxSum,baseIdx};
}

int main() {
    vector<int> arr = {2, 1, -3, 4, -1, 2, 1, -5, 4};
    int k = 3;
    auto ans = maxSumSubarrayOfLengthK(arr, k);
    cout << "Length: " << ans.first << ", Starting Index: " << ans.second << endl;
    return 0;
}