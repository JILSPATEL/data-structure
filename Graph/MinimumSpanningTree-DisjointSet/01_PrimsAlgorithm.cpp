/**
 * Prim's Algorithm (Minimum Spanning Tree)
 *
 * Problem:
 * Find the minimum total weight required to connect all vertices
 * of an undirected weighted graph.
 *
 * ---------------------------------------------------------------
 * What is MST?
 * MST (Minimum Spanning Tree) is a subset of edges:
 *
 * 1. Connects all vertices
 * 2. Contains exactly V-1 edges
 * 3. Has minimum possible total weight
 * 4. Does not contain cycles
 *
 * ---------------------------------------------------------------
 * Approach Used:
 * Prim's Algorithm using Min Heap (Priority Queue)
 *
 * Idea:
 * Start from any node (here node 0).
 * Always pick the minimum weight edge that connects
 * a visited node to an unvisited node.
 *
 * ---------------------------------------------------------------
 * Data Structures Used:
 *
 * 1. Adjacency List
 *    adj[u] = {v, wt}
 *
 * 2. Visited Array
 *    vis[i] = 1 means node already included in MST
 *
 * 3. Min Heap
 *    Stores: {edgeWeight, node}
 *
 * ---------------------------------------------------------------
 * Time Complexity:
 * O(E log V)
 *
 * Each edge can be pushed into heap
 * and heap operations take log(V)
 *
 * ---------------------------------------------------------------
 * Space Complexity:
 * O(V + E)
 *
 * Adjacency list + visited array + heap
 */

class Solution {
public:

    int spanningTree(int V, vector<vector<int>>& edges) {

        // --------------------------------------------------------
        // Step 1: Create adjacency list
        // --------------------------------------------------------

        vector<vector<pair<int, int>>> adj(V);

        for (auto &it : edges) {

            int u  = it[0];
            int v  = it[1];
            int wt = it[2];

            // Since graph is undirected
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }

        // --------------------------------------------------------
        // Step 2: Visited array
        // --------------------------------------------------------

        vector<int> vis(V, 0);

        // --------------------------------------------------------
        // Step 3: Min Heap
        //
        // Stores:
        // {weight, node}
        //
        // Smallest weight comes first
        // --------------------------------------------------------

        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > pq;

        // --------------------------------------------------------
        // Start from node 0 with weight 0
        // --------------------------------------------------------

        pq.push({0, 0});

        int mstWeight = 0;

        // --------------------------------------------------------
        // Step 4: Process heap
        // --------------------------------------------------------

        while (!pq.empty()) {

            // Get minimum weight edge
            auto curr = pq.top();
            pq.pop();

            int wt       = curr.first;
            int currNode = curr.second;

            // ----------------------------------------------------
            // If already visited, skip
            //
            // Important:
            // Same node may enter heap multiple times
            // through different edges.
            // We only process first minimum one.
            // ----------------------------------------------------

            if (vis[currNode])
                continue;

            // ----------------------------------------------------
            // Include node in MST
            // ----------------------------------------------------

            vis[currNode] = 1;

            // Add edge weight to final answer
            mstWeight += wt;

            // ----------------------------------------------------
            // Traverse neighbours
            // ----------------------------------------------------

            for (auto &neb : adj[currNode]) {

                int nextNode = neb.first;
                int nextWt   = neb.second;

                // If neighbour not included in MST
                if (!vis[nextNode]) {

                    // Push into min heap
                    pq.push({nextWt, nextNode});
                }
            }
        }

        return mstWeight;
    }
};