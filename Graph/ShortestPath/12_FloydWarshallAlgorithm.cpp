/**
 * Floyd–Warshall Algorithm
 *
 * Description:
 * Finds the shortest distance between every pair of vertices
 * in a weighted graph (All-Pairs Shortest Path).
 *
 * Example 1:
 * Input: V=4, edges=[[0,1,5],[0,3,9],[1,2,3],[3,2,2],[1,3,2]]
 * Output: All-pairs shortest distances
 * dist[0][2]=8, dist[1][2]=3, etc.
 *
 * Example 2:
 * Input: V=3, edges=[[0,1,3],[1,2,4],[0,2,5]]
 * Output: Direct paths and indirect paths compared
 * dist[0][2]=5 (direct) vs dist[0][1]+dist[1][2]=7
 *
 * Example 3:
 * Input: V=3, edges=[[0,1,1],[1,2,-1],[2,0,-2]]
 * Output: Detects negative cycle
 * dist[i][i] < 0 indicates negative cycle
 *
 * Works with:
 * - Directed graphs
 * - Undirected graphs
 * - Positive edge weights
 * - Negative edge weights
 * - Negative cycle detection
 *
 * Approaches:
 *
 * 1. Run Dijkstra from every node
 *    Time Complexity: O(V * ElogV)
 *    Space Complexity: O(V)
 *
 * 2. Floyd–Warshall Algorithm (Dynamic Programming)
 *    Time Complexity: O(V³)
 *    Space Complexity: O(V²)
 *
 * Core DP Relation:
 *
 * dist[i][j] =
 * min(dist[i][j], dist[i][k] + dist[k][j])
 *
 * Meaning:
 * Current shortest path from i → j
 * OR
 * Path from i → k → j
 *
 * Why k is the outer loop?
 *
 * k represents the intermediate node currently allowed
 * in the path.
 *
 * Step-by-step:
 *
 * k=0 → Allow node 0
 * k=1 → Allow nodes {0,1}
 * k=2 → Allow nodes {0,1,2}
 * ...
 *
 * We gradually build shortest paths using more nodes.
 *
 * Negative Cycle Detection:
 *
 * After completion:
 *
 * if(dist[i][i] < 0)
 *     Negative cycle exists
 *
 * Because distance from a node to itself
 * should always be 0.
 *
 * Time Complexity: O(V³)
 * Space Complexity: O(V²)
 */

class Solution {
public:
    void floydWarshall(vector<vector<int>>& dist) {

        int V = dist.size();

        // Convert diagonal elements to 0
        // Distance from a node to itself = 0

        for(int i = 0; i < V; i++) {
            dist[i][i] = 0;
        }

        /*
            k → intermediate node
            i → source node
            j → destination node
        */

        for(int k = 0; k < V; k++) {

            for(int i = 0; i < V; i++) {

                for(int j = 0; j < V; j++) {

                    // Skip if path doesn't exist
                    if(dist[i][k] != 1e8 &&
                       dist[k][j] != 1e8) {

                        dist[i][j] = min(
                            dist[i][j],
                            dist[i][k] + dist[k][j]
                        );
                    }
                }
            }
        }

        // Optional: Negative cycle detection

        for(int i = 0; i < V; i++) {
            if(dist[i][i] < 0) {
                // Negative cycle exists
            }
        }
    }
};