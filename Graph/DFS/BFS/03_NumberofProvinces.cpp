/**
 * Problem: Number of Provinces
 * Platform: LeetCode
 * Approach: Depth First Search (DFS)
 * 
 * Description:
 * We are given an adjacency matrix `isConnected` where:
 * 
 * isConnected[i][j] = 1
 * -> city i and city j are directly connected.
 * 
 * A province means a group of directly or indirectly connected cities.
 * 
 * We need to count total disconnected groups (connected components).
 * 
 * --------------------------------------------------------
 * Approaches:
 * 
 * 1. DFS Traversal (Used Here)
 *    - Start DFS from every unvisited city.
 *    - Mark all reachable cities as visited.
 *    - Every new DFS call represents one province.
 * 
 * 2. BFS Traversal
 *    - Same logic using queue instead of recursion.
 * 
 * 3. Disjoint Set Union (DSU / Union Find)
 *    - Union all connected cities.
 *    - Count unique parents.
 *
 * --------------------------------------------------------
 * Example:
 * Input:
 * [[1,1,0],
 *  [1,1,0],
 *  [0,0,1]]
 *
 * Output:
 * 2
 *
 * --------------------------------------------------------
 * Time Complexity:
 * O(n^2)
 *
 * Because we traverse the adjacency matrix.
 *
 * Space Complexity:
 * O(n)
 *
 * For visited array + recursion stack.
 */

class Solution {
public:

    /**
     * DFS Function
     * -------------------------
     * Marks all connected cities as visited.
     * 
     * Parameters:
     * - isConnected : adjacency matrix
     * - idx         : current city
     * - vis         : visited array
     */
    void dfs(vector<vector<int>>& isConnected,
             int idx,
             vector<int>& vis) {

        // Mark current city as visited
        vis[idx] = 1;

        // Traverse all possible neighboring cities
        for (int i = 0; i < isConnected.size(); i++) {

            // If city is connected and not visited
            if (!vis[i] && isConnected[idx][i] == 1) {

                // Visit neighbor city
                dfs(isConnected, i, vis);
            }
        }
    }

    int findCircleNum(vector<vector<int>>& isConnected) {

        // Total number of cities
        int n = isConnected.size();

        // Visited array
        vector<int> vis(n, 0);

        // Province counter
        int cnt = 0;

        /**
         * Traverse every city
         * 
         * If city is unvisited:
         * -> Start DFS
         * -> Entire connected component gets visited
         * -> Increase province count
         */
        for (int i = 0; i < n; i++) {

            if (!vis[i]) {

                dfs(isConnected, i, vis);

                // One complete province found
                cnt++;
            }
        }

        return cnt;
    }
};