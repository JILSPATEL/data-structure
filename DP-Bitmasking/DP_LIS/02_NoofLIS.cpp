#include <bits/stdc++.h>
using namespace std;

/*
Problem:
Count the number of distinct Longest Increasing Subsequences (LIS) in an array.

Approach:
Use dynamic programming with two arrays:
- len[i] = length of the LIS ending at index i
- cnt[i] = number of LISs ending at index i

For every j < i:
- If nums[j] < nums[i], we can extend the LIS ending at j.
- If len[j] + 1 is greater than len[i], we start a new best LIS and reset the count.
- If len[j] + 1 is equal to len[i], we add the number of ways from j.

Intuition:
Each element can be the end of many increasing subsequences. We track both the best length and how many ways achieve it.

Example:
nums = [1, 2, 2, 3]
The LIS length is 3, and the number of LISs is 2:
[1, 2, 3] can be formed by using either 2 at index 1 or index 2.
*/
long long lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();
    if(n==0) return 0;

    vector<int> len(n, 1);
    vector<long long> cnt(n, 1);
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[j] < nums[i])
            {
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                } else if (len[j] + 1 == len[i]) {
                    cnt[i] += cnt[j];
                }
            }
        }
    }
    int max_len = *max_element(len.begin(), len.end());
    long long total = 0;
    for (int i = 0; i < n; i++) {
        if (len[i] == max_len) total += cnt[i];
    }
    return total;
}

int main()
{
    int n;
    cin>> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin>> arr[i];
    }
    cout<<"No of possible LIS Is: " << lengthOfLIS(arr) << endl;
    return 0;
}