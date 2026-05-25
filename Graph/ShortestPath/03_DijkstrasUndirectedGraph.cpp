/**
 * Dijkstra's Algorithm (Shortest Path in Weighted Undirected Graph)
 *
 * Description:
 * Finds the shortest distance from source node `src`
 * to all other vertices in a weighted undirected graph.
 *
 * Approaches:
 * 1. Brute Force:
 *    - Pick minimum distance node linearly every time
 *    - Time: O(V²)
 *
 * 2. Dijkstra using Min Heap (Used here):
 *    - Use priority queue (min heap) to always process
 *      the node with minimum current distance.
 *    - Time: O((V + E) * logV)
 *    - Space: O(V + E)
 */

class Solution {
public:
    vector<int> dijkstra(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e9);

        // Adjacency List: {neighbor, weight}
        vector<vector<pair<int, int>>> adj(V);

        // Construct undirected graph
        for (auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
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