/**
 * Problem: Shortest Path in Directed Acyclic Graph (DAG)
 *
 * Description:
 * Given a DAG with V vertices and E weighted directed edges,
 * find the shortest distance from source node 0 to all
 * other nodes.
 *
 * Example 1:
 * Input: V=6, edges=[[0,1,2],[0,4,1],[1,2,3],[4,2,2],[2,3,6],[4,5,4],[5,3,1]]
 * Output: [0,2,3,5,1,5]
 * Explanation: Shortest distances from node 0
 *
 * Example 2:
 * Input: V=3, edges=[[0,1,2],[0,2,4],[1,2,1]]
 * Output: [0,2,3]
 * Explanation: Path 0→1→2 is shorter than 0→2
 *
 * Example 3:
 * Input: V=4, edges=[[0,1,3],[1,2,2],[2,3,5]]
 * Output: [0,3,5,10]
 * Explanation: Linear path accumulates weights
 *
 * ---------------------------------------------------------
 * Approach: Topological Sort + Edge Relaxation
 * ---------------------------------------------------------
 *
 * Idea:
 * Since the graph is a DAG, we can process nodes in
 * Topological Order.
 *
 * Why Topological Order?
 * In a topological ordering, a node always appears before
 * all nodes reachable from it.
 *
 * This guarantees:
 * When processing a node, its shortest distance has already
 * been computed.
 *
 * Steps:
 * 1. Create adjacency list:
 *      adj[u] = {v, weight}
 *
 * 2. Perform DFS-based Topological Sort:
 *      - Visit nodes recursively
 *      - Push nodes into stack after exploring children
 *
 * 3. Initialize distances:
 *      dist[i] = INF
 *      dist[0] = 0
 *
 * 4. Process nodes in topological order:
 *      For each edge:
 *
 *      u ----wt----> v
 *
 *      Relax edge:
 *
 *      if(dist[u] + wt < dist[v])
 *          dist[v] = dist[u] + wt
 *
 * 5. Replace INF with -1
 *
 * ---------------------------------------------------------
 * Dry Run:
 * ---------------------------------------------------------
 *
 * Input:
 *
 * V = 6
 *
 * Edges:
 *
 * 0 → 1 (2)
 * 0 → 4 (1)
 * 1 → 2 (3)
 * 4 → 2 (2)
 * 2 → 3 (6)
 * 4 → 5 (4)
 * 5 → 3 (1)
 *
 * Topological Order:
 *
 * 0 → 4 → 5 → 1 → 2 → 3
 *
 * Initial:
 *
 * dist = [0, INF, INF, INF, INF, INF]
 *
 * Process node 0:
 *
 * dist[1] = 2
 * dist[4] = 1
 *
 * dist:
 * [0,2,INF,INF,1,INF]
 *
 * Process node 4:
 *
 * dist[2] = 3
 * dist[5] = 5
 *
 * dist:
 * [0,2,3,INF,1,5]
 *
 * Process node 5:
 *
 * dist[3] = 6
 *
 * Final:
 *
 * [0,2,3,6,1,5]
 *
 * ---------------------------------------------------------
 * Time Complexity:
 * ---------------------------------------------------------
 *
 * Building adjacency list : O(E)
 *
 * DFS Topological sort:
 * O(V + E)
 *
 * Relaxation:
 * O(E)
 *
 * Total:
 *
 * O(V + E)
 *
 * ---------------------------------------------------------
 * Space Complexity:
 * ---------------------------------------------------------
 *
 * Adjacency list : O(V + E)
 * Visited array  : O(V)
 * Stack          : O(V)
 * Distance array : O(V)
 *
 * Total:
 *
 * O(V + E)
 *
 * ---------------------------------------------------------
 * Alternative Approaches:
 * ---------------------------------------------------------
 *
 * 1. Dijkstra
 *      O((V+E)logV)
 *      Works for general positive weighted graphs
 *
 * 2. Bellman Ford
 *      O(V*E)
 *      Works with negative weights
 *
 * 3. Floyd Warshall
 *      O(V³)
 *      For all-pairs shortest paths
 *
 */

class Solution {
public:

    // DFS for topological sorting
    void topoSort(
        int node,
        vector<vector<pair<int, int>>>& adj,
        vector<int>& vis,
        stack<int>& st
    ) {
        vis[node] = 1;

        for (auto it : adj[node]) {
            int v = it.first;

            if (!vis[v]) {
                topoSort(v, adj, vis, st);
            }
        }

        // Push after visiting children
        st.push(node);
    }

    vector<int> shortestPath(
        int V,
        int E,
        vector<vector<int>>& edges
    ) {

        //-------------------------------------------------
        // Step 1: Build adjacency list
        //-------------------------------------------------

        vector<vector<pair<int, int>>> adj(V);

        for (int i = 0; i < E; i++) {

            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];

            adj[u].push_back({v, wt});
        }

        //-------------------------------------------------
        // Step 2: Topological Sort
        //-------------------------------------------------

        vector<int> vis(V, 0);
        stack<int> st;

        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                topoSort(i, adj, vis, st);
            }
        }

        //-------------------------------------------------
        // Step 3: Initialize distance array
        //-------------------------------------------------

        vector<int> dist(V, 1e9);

        // Source node = 0
        dist[0] = 0;

        //-------------------------------------------------
        // Step 4: Relax edges in topo order
        //-------------------------------------------------

        while (!st.empty()) {

            int node = st.top();
            st.pop();

            // Skip unreachable nodes
            if (dist[node] != 1e9) {

                for (auto it : adj[node]) {

                    int v = it.first;
                    int wt = it.second;

                    if (dist[node] + wt < dist[v]) {
                        dist[v] = dist[node] + wt;
                    }
                }
            }
        }

        //-------------------------------------------------
        // Step 5: Replace INF with -1
        //-------------------------------------------------

        for (int i = 0; i < V; i++) {
            if (dist[i] == 1e9) {
                dist[i] = -1;
            }
        }

        return dist;
    }
};