#include <bits/stdc++.h>
using namespace std;

int maxSumSubarrayOfLengthK(vector<int>& arr, int k) {
    int n = arr.size();
    if (n < k) return 0;

    vector<long long> prefix(n+1, 0);
    for (int i = 0; i < n; i++) prefix[i+1] = prefix[i] + arr[i];

    long long maxSum = LLONG_MIN;
    int maxLen = k;

    long long minPrefix = prefix[0];
    int minIndex = 0;

    for (int j = k; j <= n; j++) {
        // ✅ update minPrefix first (so it's valid for this j)
        if (prefix[j-k] < minPrefix) {
            minPrefix = prefix[j-k];
            minIndex = j-k;
        }

        // now compute candidate subarray ending at j-1
        long long currSum = prefix[j] - minPrefix;
        int currLen = j - minIndex;

        if (currSum > maxSum) {
            maxSum = currSum;
            maxLen = currLen;
        } else if (currSum == maxSum) {
            maxLen = max(maxLen, currLen);
        }
    }

    return maxLen;
}

int main() {
    vector<int> arr = {2, 1, -3, 4, -1, 2, 1, -5, 4};
    int k = 3;
    int ans = maxSumSubarrayOfLengthK(arr, k);
    cout << "Length: " << ans << endl; // ✅ Expected: 4
    return 0;
}
