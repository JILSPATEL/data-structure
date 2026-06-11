/**
 * Problem: Jump Game IV
 * -----------------------------------
 * Given an array of integers arr, you are initially positioned
 * at index 0.
 *
 * In one move you can jump to:
 * 1. i + 1
 * 2. i - 1
 * 3. any index j where arr[i] == arr[j] and i != j
 *
 * Return the minimum number of steps required to reach
 * the last index.
 *
 * Approach 1: BFS + HashMap (Optimal)
 * - Treat each index as a node.
 * - Use BFS because we need minimum steps.
 * - Store all indices of same values using unordered_map.
 * - Important optimization:
 *      After processing a value once,
 *      clear its vector to avoid TLE.
 *
 * Example 1:
 * Input: arr = [100,-23,-23,404,100,100,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23,23]
 * Output: 6
 * Explanation: Jump using values at same indices
 *
 * Example 2:
 * Input: arr = [7]
 * Output: 0
 * Explanation: Single element - already at end
 *
 * Example 3:
 * Input: arr = [7,6,9,6,9,6,9,7]
 * Output: 1
 * Explanation: Jump to index 7 (0→7) or use same values
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

class Solution {
public:
    int minJumps(vector<int>& arr) {

        int n = arr.size();

        if (n == 1)
            return 0;

        // value -> all indices having that value
        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }

        vector<int> vis(n, 0);

        queue<int> q;

        q.push(0);
        vis[0] = 1;

        int steps = 0;

        while (!q.empty()) {

            int sz = q.size();

            while (sz--) {

                int curr = q.front();
                q.pop();

                // reached last index
                if (curr == n - 1)
                    return steps;

                // move to curr - 1
                if (curr - 1 >= 0 && !vis[curr - 1]) {
                    vis[curr - 1] = 1;
                    q.push(curr - 1);
                }

                // move to curr + 1
                if (curr + 1 < n && !vis[curr + 1]) {
                    vis[curr + 1] = 1;
                    q.push(curr + 1);
                }

                // move to all same-value indices
                for (auto idx : mp[arr[curr]]) {

                    if (!vis[idx]) {
                        vis[idx] = 1;
                        q.push(idx);
                    }
                }

                // IMPORTANT:
                // prevent reprocessing same value again
                mp[arr[curr]].clear();
            }

            steps++;
        }

        return -1;
    }
};