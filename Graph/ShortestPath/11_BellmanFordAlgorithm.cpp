/**
 * Bellman-Ford Algorithm
 *
 * Description:
 * Finds shortest distance from a source node to all other nodes
 * in a weighted graph. Works for both positive and negative
 * edge weights and can also detect negative weight cycles.
 *
 * Example 1:
 * Input: V=5, edges=[[0,1,4],[0,2,2],[1,2,1],[1,3,5],[2,3,8],[2,4,-3],[4,3,-5]], src=0
 * Output: [0,4,2,1,-1]
 * Explanation: Shortest distances from node 0
 *
 * Example 2:
 * Input: V=3, edges=[[1,2,-3],[2,0,4],[0,1,-2]], src=0
 * Output: [0,-2,-5]
 * Explanation: Negative weights handled correctly
 *
 * Example 3:
 * Input: V=3, edges=[[0,1,1],[1,2,-2],[2,1,1]], src=0
 * Output: [-1]
 * Explanation: Negative cycle detected
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