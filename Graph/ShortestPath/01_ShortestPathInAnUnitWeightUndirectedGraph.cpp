/**
 * Problem: Shortest Path in an Undirected Unweighted Graph
 *
 * Approach:
 * 1. Build an adjacency list from the given edges.
 * 2. Use BFS (Breadth First Search) starting from the source node.
 * 3. Since the graph is unweighted, BFS guarantees the shortest path.
 * 4. Update distance when a shorter path is found.
 * 5. Convert unreachable nodes (INF) to -1.
 *
 * Example 1:
 * Input: V=6, edges=[[0,1],[0,2],[2,3],[3,4],[3,5]], src=0
 * Output: [0,1,1,2,3,3]
 * Explanation: Distance from 0 to each node
 *
 * Example 2:
 * Input: V=4, edges=[[0,1],[1,2],[2,3]], src=0
 * Output: [0,1,2,3]
 * Explanation: Linear chain path
 *
 * Example 3:
 * Input: V=5, edges=[[0,1],[2,3]], src=0
 * Output: [0,1,-1,-1,-1]
 * Explanation: Disconnected components
 *
 * Possible Approaches:
 * 1. BFS (Used here) → O(V + E) for unweighted graphs.
 * 2. Dijkstra → Used for weighted graphs.
 * 3. Floyd-Warshall → All-pairs shortest path.
 */

class Solution {
public:
    vector<int> shortestPath(int V, vector<vector<int>>& edges, int src) {
        // Create adjacency list
        vector<vector<int>> adj(V);

        for (auto& edge : edges) {
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }

        // Initialize distance array
        vector<int> dist(V, 1e9);
        dist[src] = 0;

        // BFS queue
        queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto it : adj[node]) {
                if (dist[it] > dist[node] + 1) {
                    dist[it] = dist[node] + 1;
                    q.push(it);
                }
            }
        }

        // Replace unreachable nodes with -1
        vector<int> res(V, -1);

        for (int i = 0; i < V; i++) {
            if (dist[i] != 1e9) {
                res[i] = dist[i];
            }
        }

        return res;
    }
};