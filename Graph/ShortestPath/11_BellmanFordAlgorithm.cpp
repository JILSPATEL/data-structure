/**
 * Bellman-Ford Algorithm
 *
 * Description:
 * Finds shortest distance from a source node to all other nodes
 * in a weighted graph. Works for both positive and negative
 * edge weights and can also detect negative weight cycles.
 *
 * Approaches:
 * 1. Bellman-Ford (Relax all edges V-1 times)
 *    Time Complexity: O(V * E)
 *    Space Complexity: O(V)
 *
 * 2. Dijkstra (Only for non-negative weights)
 *    Time Complexity: O(E logV)
 */

class Solution {
public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {

        vector<int> dist(V, 1e8);
        dist[src] = 0;

        // Relax all edges V-1 times
        for(int i = 0; i < V - 1; i++) {

            for(auto edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int wt = edge[2];

                if(dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Check for negative cycle
        for(auto edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if(dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1}; // Negative cycle exists
            }
        }

        return dist;
    }
};