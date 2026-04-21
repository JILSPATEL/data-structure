/**
 * Problem: Minimum Platforms Required
 * 
 * Description:
 * Given arrival and departure times of trains, find the minimum number
 * of platforms required so that no train waits.
 * 
 * Approach (Greedy + Two Pointers):
 * 1. Sort arrival and departure arrays.
 * 2. Use two pointers:
 *    - If next train arrives before current departs → need extra platform.
 *    - Else → free a platform.
 * 3. Track maximum platforms needed at any time.
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(1)
 */

class Solution {
public:
    int minPlatform(vector<int>& arr, vector<int>& dep) {
        sort(arr.begin(), arr.end());
        sort(dep.begin(), dep.end());  // ✅ FIXED

        int i = 0, j = 0;
        int n = arr.size();

        int platform = 0;
        int maxPlatform = 0;

        while(i < n && j < n) {
            if(arr[i] <= dep[j]) {
                platform++;
                i++;
            } else {
                platform--;
                j++;
            }

            maxPlatform = max(maxPlatform, platform);
        }

        return maxPlatform;
    }
};
