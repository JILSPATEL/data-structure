/**
 * Problem: Replace each element with its rank in the array
 * 
 * Description:
 * - The smallest element gets rank 1
 * - Equal elements must have the same rank
 * - Ranking should be based on sorted order
 * 
 * Approach 1 (Heap - User's Approach):
 * - Push all elements into a min heap
 * - Extract elements in sorted order
 * - Assign rank only when encountering a new value
 * - Store value → rank in map
 * - Replace original array using map
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 * 
 * Approach 2 (Sorting - Optimal & Cleaner):
 * - Copy array and sort it
 * - Assign ranks to unique elements
 * - Replace using map
 */

class Solution {
  public:

    vector<int> replaceWithRank(vector<int> &arr, int N) {
        priority_queue<int, vector<int>, greater<int>> minHeap;

        // Step 1: Push all elements into min heap
        for(int i = 0; i < N; i++){
            minHeap.push(arr[i]);
        }

        unordered_map<int,int> mp;
        int rank = 1;

        // Step 2: Assign ranks in sorted order
        while(!minHeap.empty()){
            int val = minHeap.top();
            minHeap.pop();

            // Assign rank only if value not seen before
            if(mp.find(val) == mp.end()){
                mp[val] = rank;
                rank++;
            }
        }

        // Step 3: Replace original array values with ranks
        for(int i = 0; i < N; i++){
            arr[i] = mp[arr[i]];
        }

        return arr;
    }
};