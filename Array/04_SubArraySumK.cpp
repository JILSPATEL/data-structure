#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixSumCount;
        prefixSumCount[0] = 1;  
        int currSum = 0;
        int count = 0;

        for (int num : nums) {
            currSum += num;
            int target = currSum - k;

            if (prefixSumCount.find(target) != prefixSumCount.end()) {
                count += prefixSumCount[target];
            }

            prefixSumCount[currSum]++;
        }

        return count;
    }
};