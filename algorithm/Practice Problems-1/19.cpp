/*
Given a sequence of n numbers and an integer k, design a linear time
algorithm to compute the length of the maximum sum sub array , whos
length is at most k.
*/

#include <bits/stdc++.h>
using namespace std;

int maxSumSubarrayOfLengthK(vector<int> &arr, int k)
{
    int n = arr.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        prefix[i] = prefix[i - 1] + arr[i - 1];
    }

    deque<int> dq;
    dq.push_back(0);

    long long maxSum=LLONG_MIN;
    int maxLen=0;

    for(int j=1;j<=n;j++){
        while (!dq.empty() && dq.front() < j - k) dq.pop_front();
        if(!dq.empty()){
            long long currSum=prefix[j]-prefix[dq.front()];
            int currLen=j-dq.front();

            if(currSum>maxSum){
                maxSum=currSum;
                maxLen=currLen;
            }else if(currSum==maxSum){
                maxLen=max(maxLen,currLen);
            }
        }

        while(!dq.empty() && prefix[dq.back()]>=prefix[j]) dq.pop_back();
        dq.push_back(j);
    }
    return maxLen;
}

int main()
{
    vector<int> arr = {2, 1, -3, 4, -1, 2, 1, -5, 4};
    int k = 3;
    int ans = maxSumSubarrayOfLengthK(arr, k);
    cout << "Length: " << ans << endl;
    return 0;
}