class Solution {
public:
    typedef long long ll;
    bool isPossible(int len, vector<int>& nums, vector<ll>& prefix, ll k,
                    int n) {
        int i = 0;
        int j = len - 1;
        while (j < n) {
            ll targetIdx = (i + j) / 2;
            ll targetNum = nums[targetIdx];

            ll opLeft = 0;
            ll opRight = 0;
            if (targetIdx == 0) {
                opLeft = 0;
            } else {
                opLeft = abs((targetIdx - i) * targetNum) -
                         (prefix[targetIdx - 1] - (i > 0 ? prefix[i - 1] : 0));
            }
            if (targetIdx == n-1) {
                opRight = 0;
            } else {
                opRight = abs(((j-targetIdx) * targetNum) -(prefix[j] -prefix[targetIdx]));
            }
            if(opLeft+opRight<=k){
                return true;
            }
            i++;
            j++;
        }
        return false;
    }
    int maxFrequencyScore(vector<int>& nums, long long k) {
        int n = nums.size();
        sort(nums.begin(), nums.end());

        vector<ll> prefix(n);
        prefix[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + nums[i];
        }

        int minScore = 1;
        int maxScore = n;
        int res = 0;
        while (minScore <= maxScore) {
            int mid = (minScore + maxScore) / 2;
            if (isPossible(mid, nums, prefix, k, n)) {
                res = mid;
                minScore = mid + 1;
            } else {
                maxScore = mid - 1;
            }
        }
        return res;
    }
};