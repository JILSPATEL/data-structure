/**
 * Problem:
 * We need to connect all computers in a network.
 *
 * We can remove an existing cable and place it
 * between any two disconnected computers.
 *
 * Return minimum operations required.
 *
 * ---------------------------------------------------------
 * Key Observation:
 *
 * To connect n nodes, minimum edges required = n - 1
 *
 * If total edges < n-1:
 * impossible to connect all computers.
 *
 * ---------------------------------------------------------
 * Main Idea:
 *
 * Count number of connected components.
 *
 * If there are k components,
 * we need exactly k - 1 operations to connect them.
 *
 * Example 1:
 * Input: n = 4, connections = [[0,1],[0,2],[1,2]]
 * Output: 1
 * Explanation: 1 redundant cable, can connect all
 *
 * Example 2:
 * Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2],[1,3]]
 * Output: 2
 * Explanation: 3 components initially, need 2 operations
 *
 * Example 3:
 * Input: n = 6, connections = [[0,1],[0,2],[0,3],[1,2]]
 * Output: -1
 * Explanation: Not enough cables (need at least 5 for 6 nodes)
 *
 * ---------------------------------------------------------
 * Approach:
 *
 * 1. Check if enough edges exist.
 * 2. Create adjacency list.
 * 3. Run BFS/DFS for every unvisited node.
 * 4. Count connected components.
 * 5. Return components - 1.
 *
 * ---------------------------------------------------------
 * Time Complexity:
 * O(V + E)
 *
 * Space Complexity:
 * O(V + E)
 */

class Solution {
public:

    // -----------------------------------------------------
    // BFS Function
    // -----------------------------------------------------

    void bfs(int start,
             vector<vector<int>>& adj,
             vector<int>& vis) {

        queue<int> q;

        q.push(start);
        vis[start] = 1;

        while (!q.empty()) {

            int node = q.front();
            q.pop();

            for (auto &neb : adj[node]) {

                if (!vis[neb]) {

                    vis[neb] = 1;
                    q.push(neb);
                }
            }
        }
    }

    int makeConnected(int n, vector<vector<int>>& connections) {

        // -------------------------------------------------
        // Step 1:
        // Check if enough cables exist
        // -------------------------------------------------

        if (connections.size() < n - 1) {
            return -1;
        }

        // -------------------------------------------------
        // Step 2:
        // Create adjacency list
        // -------------------------------------------------

        vector<vector<int>> adj(n);

        for (auto &it : connections) {

            int u = it[0];
            int v = it[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // -------------------------------------------------
        // Step 3:
        // Visited array
        // -------------------------------------------------

        vector<int> vis(n, 0);

        // -------------------------------------------------
        // Step 4:
        // Count connected components
        // -------------------------------------------------

        int components = 0;

        for (int i = 0; i < n; i++) {

            if (!vis[i]) {

                components++;

                bfs(i, adj, vis);
            }
        }

        // -------------------------------------------------
        // Step 5:
        // To connect k components,
        // we need k - 1 cables
        // -------------------------------------------------

        return components - 1;
    }
};