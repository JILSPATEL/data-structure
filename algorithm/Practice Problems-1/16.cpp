/*
Given a sequence of n numbers design a linear time algorithm to compute
the length of the maximum sum sub array. including negatives
*/

#include <bits/stdc++.h>
using namespace std;

int maxSubarrayLength(vector<int> &arr)
{
    int currSum=arr[0],currLen=1;
    int maxSum=arr[0],maxLen=1;
    for (int i = 0; i < arr.size(); i++)
    {
        if(currSum+arr[i]>=arr[i]){
            currSum+=arr[i];
            currLen++;
        }
        else{
            currSum=arr[i];
            currLen=1;
        }
        if(currSum>maxSum){
            maxSum=currSum;
            maxLen=currLen;
        }
        else if(currSum==maxSum){
            maxLen=currLen;
        }
    }
    return maxLen;
    
}

int main()
{
    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << maxSubarrayLength(arr) << endl; // Output: 4
    return 0;
}