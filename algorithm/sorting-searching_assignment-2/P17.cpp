class Solution {
public:
    long long countBadPairs(vector<int>& nums) {
        unordered_map<long long, long long> freq;
        long long n = nums.size();

        for (int i = 0; i < n; i++) {
            freq[nums[i] - i]++;
        }

        long long totalPairs = (n * (n - 1)) / 2;
        long long goodPairs = 0;
        for (auto& [key, value] : freq) {
            if(value>1){
                goodPairs+=(value*(value-1))/2;
            }
        }

        return totalPairs - goodPairs;
    }
};
