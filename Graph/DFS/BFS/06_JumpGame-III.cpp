/**
 * Problem: Jump Game III
 * 
 * You are given an array arr and a starting index start.
 * From index i, you can jump either:
 *    i + arr[i]
 * or i - arr[i]
 * 
 * Return true if it is possible to reach any index
 * having value 0, otherwise return false.
 * 
 * Approach:
 * 1. Use DFS traversal.
 * 2. Maintain a visited array to avoid infinite loops.
 * 3. If index goes out of bounds or already visited -> return false.
 * 4. If current value becomes 0 -> return true.
 * 5. Recursively check both forward and backward jumps.
 * 
 * Example 1:
 * Input: arr = [4,2,3,0,3,1,2], start = 5
 * Output: true
 * Explanation: Path: 5 → 4 → 1 → 3 → 0
 * 
 * Example 2:
 * Input: arr = [4,2,3,0,3,1,2], start = 0
 * Output: true
 * Explanation: Path: 0 → 4 → 1 → 3 → 0
 * 
 * Example 3:
 * Input: arr = [3,0,2,6,2], start = 2
 * Output: false
 * Explanation: Can't reach index with value 0
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

class Solution {
public:

    bool dfs(vector<int>& arr, int i, vector<int>& vis) {

        // Out of bounds condition
        if (i < 0 || i >= arr.size()) {
            return false;
        }

        // Already visited
        if (vis[i]) {
            return false;
        }

        // Mark current index visited
        vis[i] = 1;

        // Reached index having value 0
        if (arr[i] == 0) {
            return true;
        }

        // Check forward and backward jump
        return (
            dfs(arr, i + arr[i], vis) ||
            dfs(arr, i - arr[i], vis)
        );
    }

    bool canReach(vector<int>& arr, int start) {

        vector<int> vis(arr.size(), 0);

        return dfs(arr, start, vis);
    }
};

/*
Example 1:

Input:
arr = [4,2,3,0,3,1,2]
start = 5

Output:
true

Explanation:
Start from index 5
5 -> 4 -> 1 -> 3
arr[3] = 0
Hence answer is true.


Example 2:

Input:
arr = [3,0,2,1,2]
start = 2

Output:
false

Explanation:
No possible path reaches index having value 0.
*/