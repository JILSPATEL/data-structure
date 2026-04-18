/**
 * Problem: Top K Frequent Elements
 * --------------------------------
 * Given an integer array nums and an integer k,
 * return the k most frequent elements.
 *
 * Approach 1: Max Heap (Priority Queue) ✅
 * --------------------------------------
 * - Count frequency using unordered_map
 * - Push (frequency, element) into max heap
 * - Extract top k elements
 *
 * Why Max Heap?
 * - Highest frequency element comes first
 *
 * Time Complexity:
 * - Frequency map: O(n)
 * - Heap build: O(n log n)
 * - Extract k: O(k log n)
 *
 * Approach 2: Min Heap (Better for large n)
 * ----------------------------------------
 * - Maintain size k min heap
 * - Pop smallest freq when size exceeds k
 * - Complexity: O(n log k)
 *
 * Approach 3: Bucket Sort (Optimal)
 * --------------------------------
 * - Frequency range: 1 → n
 * - Place elements in buckets
 * - Traverse from high freq to low
 * - Complexity: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        priority_queue<pair<int, int>> pq; // {frequency, element}

        // Step 1: Count frequency
        for (int num : nums) {
            mp[num]++;
        }

        // Edge case
        if (mp.size() < k) {
            return {};
        }

        // Step 2: Push into max heap
        for (auto& it : mp) {
            pq.push({it.second, it.first});
        }

        // Step 3: Extract top k elements
        vector<int> res;
        while (k > 0 && !pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
            k--;
        }

        // Optional: sort result
        sort(res.begin(), res.end());

        return res;
    }
};