/**
 * Dijkstra's Algorithm (Shortest Path in Weighted Directed Graph)
 *
 * Description:
 * Finds the shortest distance from source node `src`
 * to all other vertices in a weighted directed graph.
 *
 * Example 1:
 * Input: V=5, edges=[[0,1,4],[0,2,1],[2,1,2],[1,3,1],[2,3,5],[3,4,3]], src=0
 * Output: [0,3,1,4,7]
 * Explanation: Shortest distances from node 0
 *
 * Example 2:
 * Input: V=3, edges=[[0,1,2],[1,2,3],[0,2,6]], src=0
 * Output: [0,2,5]
 * Explanation: Path 0→1→2 is shorter than 0→2
 *
 * Example 3:
 * Input: V=4, edges=[[0,1,1],[1,2,2],[2,3,1]], src=0
 * Output: [0,1,3,4]
 * Explanation: Linear weighted path
 *
 * Approaches:
 * 1. Brute Force:
 *    - Time: O(V²)
 *
 * 2. Dijkstra using Min Heap (Used here):
 *    - Time: O((V + E) * logV)
 *    - Space: O(V + E)
 *
 * Note:
 * Works only for graphs with non-negative edge weights.
 */

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e9);

        // Adjacency list: {neighbor, weight}
        vector<vector<pair<int, int>>> adj(V);

        // Construct directed graph
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            adj[u].push_back({v, wt});
        }

        // Min Heap: {distance, node}
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int wt = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Skip outdated entries
            if (wt > dist[node])
                continue;

            for (auto neb : adj[node]) {
                int next = neb.first;
                int nextWt = neb.second;

                if (dist[node] + nextWt < dist[next]) {
                    dist[next] = dist[node] + nextWt;
                    pq.push({dist[next], next});
                }
            }
        }

        return dist;
    }
};